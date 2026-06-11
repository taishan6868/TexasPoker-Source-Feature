#include "common/macros.h"
#include "common/nndef.h"
#include "gameroot.h"
#include "context/context.h"
#include "Comm/ITableGame.h"
#include "utils/tarslog.h"
#include "context/context.h"

using namespace nndef;

namespace game
{
    namespace logic
    {
        namespace roomlogic
        {
            int Pause(void const *p, GameRoot *root)
            {
                PERFSTATS_ENTRY();
                __TRY__

                using namespace RoomSo;
                using namespace config;
                using namespace process;
                using namespace context;

                TGAME_Pause const *nnrs = static_cast<TGAME_Pause const *>(p);
                DLOG_TRACE("roomid:" << root->roomid() << ", " << "TGAME_Pause_E dismiss:" << nnrs->iDismiss);

                root->con->setDismiss(nnrs->iDismiss);

                __CATCH__
                PERFSTATS_EXIT();
                return 0;
            }
        }
    }
}
