#include "x64.hpp"

#define COUNT(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

namespace g3
{
	static const char* reg_names[] = {
		"a",
		"c",
		"d",
		"b",
		"sp",
		"bp",
		"si",
		"di",
		"8",
		"9",
		"10",
		"11",
		"12",
		"13",
		"14",
		"15",
		"ip",
	};

	template <typename T>
	[[nodiscard]] static constexpr bool isNumberChar(const T c) noexcept
	{
		return c >= '0' && c <= '9';
	}

	void x64Operand::decode(bool rex, uint8_t size, uint8_t reg, bool x) noexcept
	{
		reg |= (x << 3);

		this->reg = (x64Register)reg;
		access_type = (x64RegisterAccessType)size;

		if (reg >= SP && reg <= DI
			&& !rex
			&& size == 8
			)
		{
			this->reg = (x64Register)(this->reg - 4);
			access_type = ACCESS_8_H;
		}
	}

	static void decodeAccessType(x64RegisterAccessType& typ, const char*& str)
	{
		++str; // skip last char of register name

		if (typ == ACCESS_64 || typ == ACCESS_32)
		{
			++str; // skip 'x'
		}
		else if (*str == 'x')
		{
			typ = ACCESS_16;
			++str;
		}
		else if (*str == 'l')
		{
			typ = ACCESS_8;
			++str;
		}
		else if (*str == 'h')
		{
			typ = ACCESS_8_H;
			++str;
		}
	}

	void x64Operand::fromString(const char* str)
	{
		access_type = ACCESS_16;

		while (*str == ' ')
		{
			++str;
		}

		if (*str == '[')
		{
			deref_size = 32;
			++str;
		}

		if (*str == 'r')
		{
			access_type = ACCESS_64;
			++str;
		}
		else if (*str == 'e')
		{
			access_type = ACCESS_32;
			++str;
		}

		if (*str == 'a')
		{
			reg = RA;
			decodeAccessType(access_type, str);
		}
		else if (*str == 'c')
		{
			reg = RC;
			decodeAccessType(access_type, str);
		}
		else if (*str == 'b')
		{
			reg = RB;
			decodeAccessType(access_type, str);
		}
		else if (*str == 'd')
		{
			if (str[1] == 'i')
			{
				reg = DI;
				str += 2;
			}
			else
			{
				reg = RD;
				decodeAccessType(access_type, str);
				++str;
			}
		}
		else if (*str == 's' && *++str == 'i')
		{
			reg = SI;
			++str;
		}

		if (*str == '+')
		{
			deref_offset = 0;
			while (isNumberChar(*++str))
			{
				deref_offset *= 10;
				deref_offset += ((*str) - '0');
			}
		}

		if (*str != '\0')
		{
			throw 0;
		}
	}

	void x64Instruction::reset() noexcept
	{
		operation = nullptr;
		for (auto& opr : operands)
		{
			opr.reset();
		}
	}

	template <typename T = uint64_t>
	static void getImmediate(T& val, const uint8_t*& code, const uint8_t imm_bytes)
	{
		++code;
		val = 0;
		for (uint8_t i = imm_bytes; i-- != 0; )
		{
			val <<= 8;
			val |= code[i];
		}
		code += (imm_bytes - 1);
	}

	x64Instruction x64Disasm(const uint8_t*& code)
	{
		bool operand_size_override = false;
		bool address_size_override = false;
		bool rex = false;
		bool default_operand_size = true;
		bool reg_x = false;
		bool rm_x = false;

		// "Mandatory" prefix
		if (*code == 0x67)
		{
			address_size_override = true;
			++code;
		}
		if (*code == 0x66)
		{
			operand_size_override = true;
			++code;
		}

		// REX prefix
		if ((*code >> 4) == 0b0100)
		{
			rex = true;
			if ((*code >> 3) & 1)
			{
				default_operand_size = false;
			}
			reg_x = ((*code >> 2) & 1);
			rm_x = (*code & 1);
			++code;
		}

		// Opcode
		x64Instruction res{};
		for (const auto& op : operations)
		{
			if (op.matches(code))
			{
				if (*code == 0x0F)
				{
					++code;
				}
				res.operation = &op;
				if (op.operand_encoding != ZO)
				{
					uint8_t operand_size;
					uint8_t immediate_size;
					if (operand_size_override)
					{
						operand_size = immediate_size = 16;
					}
					else if (op.operand_size == 0)
					{
						operand_size = immediate_size = (default_operand_size ? 32 : 64);
					}
					else if (default_operand_size)
					{
						operand_size = immediate_size = op.operand_size;
					}
					else
					{
						operand_size = 64;
						immediate_size = op.operand_size;
					}

					uint8_t opcode = *code;
					uint8_t opr_i = 0;
					uint8_t num_modrm_oprs = op.getNumModrmOperands();
					bool modrm_read = false;
					uint8_t modrm;
					uint8_t sib;

					for (uint8_t opr_enc; opr_enc = ((op.operand_encoding >> (opr_i * BITS_PER_OPERAND)) & OPERAND_MASK), opr_enc != ZO; )
					{
						x64Operand& opr = res.operands[opr_i];
						if (opr_enc == O)
						{
							opr.decode(rex, operand_size, opcode & 0b111, rm_x);
						}
						else if (opr_enc == M || opr_enc == R)
						{
							const bool left = !modrm_read;
							if (left)
							{
								modrm_read = true;
								modrm = *++code;
							}
							const bool direct = ((modrm >> 6) == 0b11);
							if (opr_enc == M)
							{
								opr.decode(rex || !direct, operand_size, modrm & 0b111, rm_x);
								if (!direct)
								{
									opr.access_type = (address_size_override ? ACCESS_32 : ACCESS_64);
									opr.deref_size = ((num_modrm_oprs == 2) ? 1 : operand_size); // Hiding pointer type when other operand makes it apparent
									if (opr.reg == SP)
									{
										sib = *++code;
									}
									if ((modrm >> 6) == 0b01)
									{
										opr.deref_offset = (int8_t) * ++code;
									}
									else if ((modrm >> 6) == 0b10)
									{
										getImmediate(opr.deref_offset, code, 4);
									}
									else if ((modrm >> 6) == 0b00)
									{
										if (opr.reg == SP)
										{
											if (sib == 0x25)
											{
												// Absolute address
												opr.reg = IMM;
												getImmediate(opr.val, code, 4);
											}
										}
										else if (opr.reg == BP)
										{
											// RIP-relative
											opr.reg = IP;
											getImmediate(opr.deref_offset, code, 4);
										}
									}
								}
							}
							else if (opr_enc == R)
							{
								opr.decode(rex, operand_size, (modrm >> 3) & 0b111, reg_x);
							}
						}
						else if (opr_enc == I)
						{
							opr.reg = IMM;
							getImmediate(opr.val, code, immediate_size / 8);
						}
						else if (opr_enc == D)
						{
							opr.reg = DIS;
							getImmediate(opr.val, code, immediate_size / 8);
							if (immediate_size == 32)
							{
								opr.displacement = (int64_t)(int32_t)(uint32_t)opr.val;
							}
							else if (immediate_size == 8)
							{
								opr.displacement = (int64_t)(int8_t)(uint8_t)opr.val;
							}
						}
						else if (opr_enc == A)
						{
							opr.decode(rex, operand_size, RA, reg_x);
						}

						if (++opr_i == COUNT(res.operands))
						{
							break;
						}
					}
				}
				++code;
				break;
			}
		}
		return res;
	}

	uint8_t x64GetLength(const uint8_t* code)
	{
		auto start = code;
		return x64Disasm(code).isValid()
			? (uint8_t)(code - start)
			: 0;
	}

	const uint8_t* x64GetPrev(const uint8_t* code)
	{
		const auto present = code;
		for (uint8_t i = 0; i != 100; ++i)
		{
			--code;
			auto start = code;
			if (x64IsStartByte(code)
				&& x64GetNext(code) == present
				)
			{
				return start;
			}
		}
		return nullptr;
	}

	const uint8_t* x64GetNext(const uint8_t* code)
	{
		return x64Disasm(code).isValid()
			? code
			: nullptr
			;
	}

	bool x64IsStartByte(const uint8_t* code)
	{
		return *code == 0x0F // 2-byte opcode
			|| (*code & 0xF0) == 0x40 // REX
			|| (
				(((*code & 0xF0) == 0x50) // push or pop
					|| *code == 0x33 // or xor
					)
				&& ((*(code - 1) & 0xF0) != 0x40) // and no REX before
				)
			;
	}
}
