#include "common/macros.h"
#include "gameroot.h"
#include "context/context.h"
#include "Comm/ITableGame.h"
#include "utils/tarslog.h"
#include "message/sendclientmessage.h"
#include "logic/gamelogic/core/checkbegin.h"
#include "process/process.h"
#include "message/sendroommessage.h"

namespace game
{
    namespace logic
    {
        namespace roomlogic
        {
            void SetWinCard(void const *p, GameRoot *root)
            {
                PERFSTATS_ENTRY();
                __TRY__

                using namespace RoomSo;
                using namespace context;
                using namespace message;
                using namespace gamelogic;
                using namespace process;

                TGAME_SetWinCard const *nnrs = static_cast<TGAME_SetWinCard const *>(p);
                DLOG_TRACE("roomid:"<<root->roomid()<<", "<<"TGAME_SetWinCard_E player_type:" << nnrs->player_type << ", profit: "<< nnrs->preWinNum);

                root->con->setControlLineType(nnrs->player_type);
                root->con->setControlProfit(nnrs->preWinNum);
                __CATCH__
                PERFSTATS_EXIT();
            }
        }
    }
}
