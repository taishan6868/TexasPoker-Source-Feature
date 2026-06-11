#include "common/macros.h"
#include "common/nndef.h"
#include "gameroot.h"
#include "context/context.h"
#include "Comm/ITableGame.h"
#include "config/gameconfig.h"
#include "utils/tarslog.h"
#include "process/process.h"
#include "logic/gamelogic/core/checkbegin.h"
#include "logic/clientlogic/core/someact.h"
#include "context/context.h"
#include "message/sendclientmessage.h"
#include "hd.pb.h"

using namespace nndef;

namespace game
{
    namespace logic
    {
        namespace roomlogic
        {
            int StandUp(void const *p, GameRoot *root)
            {
                PERFSTATS_ENTRY();
                __TRY__

                using namespace RoomSo;
                using namespace config;
                using namespace process;
                using namespace clientlogic;
                using namespace context;
                using namespace message;

                TGAME_StandUp const *nnrs = static_cast<TGAME_StandUp const *>(p);
                if(!nnrs)
                {
                    return -1;
                }

                DLOG_TRACE("roomid:" << root->roomid() << ", nnrs: "<< printTars(*nnrs));
                
                long lPlayerID = nnrs->lPlayerID;
                User* user = root->con->getUserByUid(lPlayerID);
                if (user)
                {
                    user->setLeft(true);
                }

                __CATCH__
                PERFSTATS_EXIT();
                return 0;
            }
        }
    }
}
