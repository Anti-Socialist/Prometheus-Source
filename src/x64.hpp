#pragma once

#include <cstdint>
#include <string>

namespace g3
{
	enum x64Register : uint8_t
	{
		RA = 0,
		RC,
		RD,
		RB,
		SP,
		BP,
		SI,
		DI,
		R8,
		R9,
		R10,
		R11,
		R12,
		R13,
		R14,
		R15,
		IP,

		IMM,
		DIS,
	};

	enum x64RegisterAccessType : uint8_t
	{
		ACCESS_64 = 64,
		ACCESS_32 = 32,
		ACCESS_16 = 16,
		ACCESS_8 = 8,
		ACCESS_8_H = 0,
	};

#pragma pack(push, 1)
	struct x64Operand
	{
		x64Register reg;
		union
		{
			struct // register
			{
				/* 0 */ x64RegisterAccessType access_type;
				/* 1 */ uint8_t deref_size;
				/* 2 */ int32_t deref_offset;
				/* 6 */
			};
			struct // immediate
			{
				/* 0 */ uint64_t val;
				/* 8 */
			};
			struct // displacement
			{
				/* 0 */ int64_t displacement;
				/* 8 */
			};
		};

		void reset() noexcept
		{
			val = 0;
		}

		void decode(bool rex, uint8_t size, uint8_t reg, bool x) noexcept;
		void fromString(const char* str);

		[[nodiscard]] std::string toString() const;
	};
#pragma pack(pop)

	enum x64OperandEncoding : uint16_t
	{
		ZO = 0,

		O = 0b001,
		M = 0b010,
		R = 0b011,
		I = 0b100,
		D = 0b101,
		A = 0b111,

		OPERAND_MASK = 0b111,
		BITS_PER_OPERAND = 3,

		MR = M | (R << BITS_PER_OPERAND),
		RM = R | (M << BITS_PER_OPERAND),
		OI = O | (I << BITS_PER_OPERAND),
		MI = M | (I << BITS_PER_OPERAND),
		AI = A | (I << BITS_PER_OPERAND),

		RMI = R | (M << BITS_PER_OPERAND) | (I << (BITS_PER_OPERAND * 2)),
	};

	struct x64Operation
	{
		const char* const name;
		const uint16_t opcode;
		const x64OperandEncoding operand_encoding;
		const uint8_t operand_size;
		const uint8_t distinguish;

		static constexpr uint8_t MAX_OPERANDS = 3;

		x64Operation(const char* name, uint16_t opcode, x64OperandEncoding operand_encoding)
			: x64Operation(name, opcode, operand_encoding, 0, 8)
		{
		}

		x64Operation(const char* name, uint16_t opcode, x64OperandEncoding operand_encoding, uint8_t operand_size)
			: x64Operation(name, opcode, operand_encoding, operand_size, 8)
		{
		}

		x64Operation(const char* name, uint16_t opcode, x64OperandEncoding operand_encoding, uint8_t operand_size, uint8_t distinguish)
			: name(name), opcode(opcode), operand_encoding(operand_encoding), operand_size(operand_size), distinguish(distinguish)
		{
		}

		[[nodiscard]] uint16_t getUniqueId() const noexcept
		{
			return distinguish == 8
				? opcode
				: (opcode << 3) | distinguish
				;
		}

		[[nodiscard]] bool matches(const uint8_t* code) const noexcept
		{
			uint16_t b = *code;
			if (b == 0x0F)
			{
				++code;
				b <<= 8;
				b |= *code;
			}
			if (getOprEncoding(0) == O)
			{
				b &= ~0b111;
			}
			return opcode == b
				&& (distinguish == 8
					|| ((code[1] >> 3) & 0b111) == distinguish
					)
				;
		}

		[[nodiscard]] x64OperandEncoding getOprEncoding(uint8_t i) const noexcept
		{
			return (x64OperandEncoding)((operand_encoding >> (BITS_PER_OPERAND * i)) & OPERAND_MASK);
		}

		[[nodiscard]] uint8_t getNumOperands() const noexcept
		{
			uint8_t i = 0;
			while (i != MAX_OPERANDS)
			{
				if (getOprEncoding(i) == ZO)
				{
					break;
				}
				++i;
			}
			return i;
		}

		[[nodiscard]] uint8_t getNumModrmOperands() const noexcept
		{
			uint8_t count = 0;
			for (uint8_t i = 0; i != MAX_OPERANDS; ++i)
			{
				const auto enc = getOprEncoding(i);
				if (enc == M || enc == R)
				{
					++count;
				}
			}
			return count;
		}
	};

	inline static x64Operation operations[] = {
		{ "mov", 0x88, MR, 8 },
		{ "mov", 0x89, MR },
		{ "mov", 0x8A, RM, 8 },
		{ "mov", 0x8B, RM },
		{ "mov", 0xB0, OI, 8 },
		{ "mov", 0xB8, OI },
		{ "mov", 0xC6, MI, 8 },
		{ "mov", 0xC7, MI, 32 },
		{ "ret", 0xC3, ZO },
		{ "push", 0x50, O, 64 },
		{ "pop", 0x58, O, 64 },
		{ "push", 0xFF, M, 64, 6},
		{ "add", 0x81, MI, 32, 0 },
		{ "add", 0x83, MI, 8, 0 },
		{ "sub", 0x81, MI, 32, 5 },
		{ "sub", 0x83, MI, 8, 5 },
		{ "cmp", 0x80, MI, 8, 7 },
		{ "cmp", 0x83, MI, 8, 7 },
		{ "cmp", 0x3C, AI, 8 },
		{ "cmp", 0x3D, AI, 32 },
		{ "cmp", 0x38, MR, 8 },
		{ "cmp", 0x39, MR },
		{ "lea", 0x8D, RM },
		{ "jz", 0x74, D, 8 },
		{ "jnz", 0x75, D, 8 },
		{ "call", 0xE8, D, 32 },
		{ "call", 0xFF, M, 32, 2 },
		{ "call", 0xFF, M, 32, 3 },
		{ "jmp", 0xEB, D, 8 },
		{ "jmp", 0xE9, D, 32 },
		{ "test", 0x84, MR, 8 },
		{ "test", 0x85, MR },
		{ "test", 0xF6, MI, 8, 0 },
		{ "test", 0xF7, MI, 32, 0 },
		{ "xor", 0x33, RM },
		{ "movzx", 0x0FB6, RM, 8 },
		{ "movzx", 0x0FB7, RM, 16 }, // TODO: Account for operands having different sizes
		{ "imul", 0x69, RMI, 32 },
		{ "nop", 0x90, ZO },
		{ "cpuid", 0x0FA2, ZO },
		{ "div", 0xF7, M, 32, 6 },
	};

	struct x64Instruction
	{
		const x64Operation* operation = nullptr;
		x64Operand operands[x64Operation::MAX_OPERANDS];

		[[nodiscard]] bool isValid() const noexcept
		{
			return operation != nullptr;
		}

		void reset() noexcept;

		void fromString(const std::string& str);

		[[nodiscard]] std::string toString() const;
		[[nodiscard]] std::string toBytecode() const;
	};

	[[nodiscard]] extern std::string x64Asm(const std::string& code);
	extern x64Instruction x64Disasm(const uint8_t*& code);

	[[nodiscard]] extern uint8_t x64GetLength(const uint8_t* code);
	[[nodiscard]] extern const uint8_t* x64GetPrev(const uint8_t* code);
	[[nodiscard]] extern const uint8_t* x64GetNext(const uint8_t* code);
	[[nodiscard]] extern bool x64IsStartByte(const uint8_t* code);
}