#include "hooking.hpp"
#include "util/notify.hpp"

namespace big
{
    //int64_t hooks::boat_crash(uintptr_t a1)
    //{
    //    if (auto ptr = *reinterpret_cast<uintptr_t*>(a1 + 0x10); ptr)
    //        if (auto ptr2 = *reinterpret_cast<uintptr_t*>(ptr + 0xBB0); ptr2)
    //            if (auto ptr3 = *reinterpret_cast<uintptr_t*>(ptr2 + 0x710); ptr3)
    //                if (auto ptr4 = *reinterpret_cast<uintptr_t*>(ptr3 + 0x5C); !ptr4)
    //                    return 0;


    //    return g_hooking->get_original<hooks::boat_crash>()(a1);
    //}
}