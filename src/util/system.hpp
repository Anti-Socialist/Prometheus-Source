#pragma once
#include "crossmap.hpp"
#include "file_manager.hpp"
#include "pointers.hpp"
#include "memory/module.hpp"
#include "x64.hpp"	
#include <TlHelp32.h>
#include <windows.h>
#include <psapi.h>
#include <dbghelp.h>

namespace big::system
{
	inline void dump_entry_points()
	{
		DWORD64 base_address = memory::module("GTA5.exe").begin().as<DWORD64>();

		const auto file_path = g_file_manager->get_project_file("./entrypoints.txt");
		auto file = std::ofstream(file_path.get_path(), std::ios::out | std::ios::trunc);

		for (auto &map : g_crossmap)
		{
			auto address = g_pointers->m_get_native_handler(g_pointers->m_native_registration_table, map.second);

			file << std::hex << std::uppercase << "0x" << map.first << " : GTA5.exe + 0x" << (DWORD64)address - base_address << std::endl;
		}

		file.close();
	}

	// Converts a pointer address to its hexadecimal representation as a std::string
	inline std::string addressToHex(uint64_t addr) {
		if (!addr)
			return "0x0";

		std::ostringstream stream;
		stream << "0x" << std::hex << std::uppercase << addr;
		return stream.str();
	}

	inline std::string getRegisterInformation(CONTEXT* context) {
		std::string dump;

		dump += "\n";
		dump += "\n";
		dump += "Dumping registers:";
		dump += "\n";
		dump += "\n";
		dump += "RAX: ";
		dump += addressToHex(context->Rax);
		dump += "\n";
		dump += "RCX: ";
		dump += addressToHex(context->Rcx);
		dump += "\n";
		dump += "RDX: ";
		dump += addressToHex(context->Rdx);
		dump += "\n";
		dump += "RBX: ";
		dump += addressToHex(context->Rbx);
		dump += "\n";
		dump += "RSI: ";
		dump += addressToHex(context->Rsi);
		dump += "\n";
		dump += "RDI: ";
		dump += addressToHex(context->Rdi);
		dump += "\n";
		dump += "RSP: ";
		dump += addressToHex(context->Rsp);
		dump += "\n";
		dump += "RBP: ";
		dump += addressToHex(context->Rbp);
		dump += "\n";
		dump += "R8:  ";
		dump += addressToHex(context->R8);
		dump += "\n";
		dump += "R9:  ";
		dump += addressToHex(context->R9);
		dump += "\n";
		dump += "R10: ";
		dump += addressToHex(context->R10);
		dump += "\n";
		dump += "R11: ";
		dump += addressToHex(context->R11);
		dump += "\n";
		dump += "R12: ";
		dump += addressToHex(context->R12);
		dump += "\n";
		dump += "R13: ";
		dump += addressToHex(context->R13);
		dump += "\n";
		dump += "R14: ";
		dump += addressToHex(context->R14);
		dump += "\n";
		dump += "R15: ";
		dump += addressToHex(context->R15);
		dump += "\n";
		return dump;
	}

	// Gets module name as a std::string from an address
	inline void getAllModuleInfos(std::map<std::string, std::pair<uint64_t, uint64_t>>* map) {
		HMODULE hMods[1024];
		HANDLE hProcess = GetCurrentProcess();
		DWORD cbNeeded;
		if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded)) {
			for (int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++) {
				// Get the full path to the module's file.
				char modNameCharArray[MAX_PATH];
				if (GetModuleFileNameExA(hProcess, hMods[i], modNameCharArray, sizeof(modNameCharArray) / sizeof(char))) {
					std::string modName(modNameCharArray);
					MODULEINFO info;
					if (GetModuleInformation(hProcess, hMods[i], &info, sizeof(MODULEINFO))) {
						std::map<uint64_t, uint64_t> modInfo;
						map->emplace(modName, std::make_pair((uint64_t)info.lpBaseOfDll, (uint64_t)info.SizeOfImage));
					}
				}
			}
		}
	}

	// Gets module name and offset from address
	inline std::string getModuleNameFromAddress(uint64_t address) {
		std::map<std::string, std::pair<uint64_t, uint64_t>> map;
		getAllModuleInfos(&map);
		for (auto const& [key, val] : map) {
			if (address > val.first && address < (val.first + val.second)) {
				std::string retn = key + "+" + addressToHex(address - val.first);
				return retn;
			}
		}
		return "";
	}

	// extract readable text from a given stack frame. All thanks to
	// using SymFromAddr and SymGetLineFromAddr64 with the stack pointer
	inline std::string getSymbolInformation(const size_t index, const std::vector<uint64_t>& frame_pointers) {
		auto addr = frame_pointers[index];
		std::string frame_dump = "stack dump [" + std::to_string(index) + "]\t";

		DWORD64 displacement64;
		DWORD displacement;
		char symbol_buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME];
		SYMBOL_INFO* symbol = reinterpret_cast<SYMBOL_INFO*>(symbol_buffer);
		symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
		symbol->MaxNameLen = MAX_SYM_NAME;

		IMAGEHLP_LINE64 line;
		line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
		std::string lineInformation;
		std::string callInformation;
		if (SymFromAddr(GetCurrentProcess(), addr, &displacement64, symbol)) {
			callInformation.append(" ").append(std::string(symbol->Name, symbol->NameLen));
			if (SymGetLineFromAddr64(GetCurrentProcess(), addr, &displacement, &line)) {
				lineInformation.append(" ").append(line.FileName).append(" L: ");
				lineInformation.append(std::to_string(line.LineNumber));
			}
			else {
				std::string moduleName = getModuleNameFromAddress(addr);
				if (moduleName != "") {
					lineInformation.append(" ").append(moduleName);
				}
			}
		}
		else {
			std::string moduleName = getModuleNameFromAddress(addr);
			if (moduleName != "") {
				lineInformation.append(" ").append(moduleName);
			}
			lineInformation.append(" ").append(addressToHex(addr));
		}
		frame_dump.append(lineInformation).append(callInformation);
		return frame_dump;
	}

	inline std::string convertFramesToText(std::vector<uint64_t>& frame_pointers) {
		std::string dump; // slightly more efficient than ostringstream
		const size_t kSize = frame_pointers.size();
		for (size_t index = 0; index < kSize && frame_pointers[index]; ++index) {
			dump += getSymbolInformation(index, frame_pointers);
			dump += "\n";
		}
		return dump;
	}

	// Using the given context, fill in all the stack frames.
   // Which then later can be interpreted to human readable text
	inline void captureStackTrace(CONTEXT* context, std::vector<uint64_t>& frame_pointers) {
		DWORD machine_type = 0;
		STACKFRAME64 frame = {}; // force zeroing
		frame.AddrPC.Mode = AddrModeFlat;
		frame.AddrFrame.Mode = AddrModeFlat;
		frame.AddrStack.Mode = AddrModeFlat;
#if defined(_M_ARM64)
		frame.AddrPC.Offset = context->Pc;
		frame.AddrFrame.Offset = context->Fp;
		frame.AddrStack.Offset = context->Sp;
		machine_type = IMAGE_FILE_MACHINE_ARM64;
#elif defined(_M_ARM)
		frame.AddrPC.Offset = context->Pc;
		frame.AddrFrame.Offset = context->R11;
		frame.AddrStack.Offset = context->Sp;
		machine_type = IMAGE_FILE_MACHINE_ARM;
#elif defined(_M_X64)
		frame.AddrPC.Offset = context->Rip;
		frame.AddrFrame.Offset = context->Rbp;
		frame.AddrStack.Offset = context->Rsp;
		machine_type = IMAGE_FILE_MACHINE_AMD64;
#else
		frame.AddrPC.Offset = context->Eip;
		frame.AddrPC.Offset = context->Ebp;
		frame.AddrPC.Offset = context->Esp;
		machine_type = IMAGE_FILE_MACHINE_I386;
#endif
		for (size_t index = 0; index < frame_pointers.size(); ++index)
		{
			if (StackWalk64(machine_type,
				GetCurrentProcess(),
				GetCurrentThread(),
				&frame,
				context,
				NULL,
				SymFunctionTableAccess64,
				SymGetModuleBase64,
				NULL)) {
				frame_pointers[index] = frame.AddrPC.Offset;
			}
			else {
				break;
			}
		}
	}

	inline LONG WINAPI TopLevelExceptionHandler(PEXCEPTION_POINTERS ExceptionInfo)
	{
		if (uint8_t length = g3::x64GetLength((uint8_t*)ExceptionInfo->ContextRecord->Rip); length)
		{
			LOG(WARNING) << "Menu Caught Exception! Recovering...";
			LOG(WARNING) << getRegisterInformation(ExceptionInfo->ContextRecord);

			SymInitialize(GetCurrentProcess(), NULL, 1);
			void* ip = reinterpret_cast<void*>(ExceptionInfo->ContextRecord->Rip);
			HMODULE hModule = GetModuleHandle(NULL);
			char moduleName[MAX_PATH] = { 0 };
			GetModuleFileNameA(hModule, moduleName, MAX_PATH);
			DWORD64 offset = 0;
			IMAGEHLP_MODULE64 moduleInfo;
			memset(&moduleInfo, 0, sizeof(moduleInfo));
			moduleInfo.SizeOfStruct = sizeof(moduleInfo);
			if (SymGetModuleInfo64(GetCurrentProcess(), (DWORD64)ip, &moduleInfo))
				offset = (DWORD64)ip - moduleInfo.BaseOfImage;

			LOG(WARNING) << "Caught exception at " << moduleName << "+" << HEX_TO_UPPER(offset);

			ExceptionInfo->ContextRecord->Rip += length;
			return EXCEPTION_CONTINUE_EXECUTION;
		}
		return false;
	}

	inline uintptr_t get_relative_address(void* ptr)
	{
		uintptr_t base_address = memory::module("GTA5.exe").begin().as<uintptr_t>();

		return (uintptr_t)ptr - base_address;
	}
}