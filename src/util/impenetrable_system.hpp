#pragma once
#include <Windows.h>
#include <winternl.h>
#pragma comment (linker, "/defaultlib:ntdll.lib")

namespace big::misc
{

	typedef NTSTATUS(NTAPI* TNtQueryInformationProcess)(
		IN HANDLE           ProcessHandle,
		IN PROCESSINFOCLASS ProcessInformationClass,
		OUT PVOID           ProcessInformation,
		IN ULONG            ProcessInformationLength,
		OUT PULONG          ReturnLength
		);

	enum { SystemKernelDebuggerInformation = 0x23 };

	typedef struct _SYSTEM_KERNEL_DEBUGGER_INFORMATION {
		BOOLEAN DebuggerEnabled;
		BOOLEAN DebuggerNotPresent;
	} SYSTEM_KERNEL_DEBUGGER_INFORMATION, * PSYSTEM_KERNEL_DEBUGGER_INFORMATION;

	struct GodmodeCheck
	{
	public:
		char pad000[137];
		bool detected;
		char pad001[112];
	};

	template <typename T>
	inline void godmode_check(T disable, T...)
	{
		GodmodeCheck result;

		HMODULE hNtdll = GetModuleHandle("ntdll.dll");

		if (IsDebuggerPresent())
			result.detected = true;

		BOOL bDebuggerPresent;
		if (TRUE == CheckRemoteDebuggerPresent(GetCurrentProcess(), &bDebuggerPresent) &&
			TRUE == bDebuggerPresent)
			result.detected = true;

		NTSTATUS status;
		SYSTEM_KERNEL_DEBUGGER_INFORMATION SystemInfo;

		status = NtQuerySystemInformation(
			(SYSTEM_INFORMATION_CLASS)SystemKernelDebuggerInformation,
			&SystemInfo,
			sizeof(SystemInfo),
			NULL);

		result.detected = SUCCEEDED(status) ? (SystemInfo.DebuggerEnabled && !SystemInfo.DebuggerNotPresent) : false;

		if (result.detected)
		{
			__debugbreak();
		}
	}
}