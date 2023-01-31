#include "hooking.hpp"
#include "util/notify.hpp"

namespace big
{
    void hooks::send_clone_sync(CNetworkObjectMgr* mgr, CNetGamePlayer* src, rage::netObject* netObject, rage::datBitBuffer* buffer, uint16_t* object_id, bool a6)
    {
        if (g.self.sync_fuzzer)
        {
            buffer->WriteInt64(0x94828921, 64);
            buffer->WriteInt64(0x784, 1);
            buffer->WriteArray(nullptr, 0);
        }
        return g_hooking->get_original<hooks::send_clone_sync>()(mgr, src, netObject, buffer, object_id, a6);
    }
}