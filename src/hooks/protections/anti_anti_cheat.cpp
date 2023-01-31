#include "hooking.hpp"
#include "util/notify.hpp"

namespace big
{
	int64_t hooks::anti_anti_cheat()
	{
		LOG(INFO) << "RAC Crash detected and blocked.";
		return 0;
	}
}