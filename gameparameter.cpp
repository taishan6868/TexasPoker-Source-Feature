#include "common/macros.h"
#include "gameroot.h"
#include "context/context.h"
#include "Comm/ITableGame.h"
#include "utils/tarslog.h"
#include "message/sendclientmessage.h"
#include "logic/gamelogic/core/checkbegin.h"
#include "process/process.h"
#include "config/gameconfig.h"

namespace game
{
    namespace logic
    {
        namespace roomlogic
        {
            void GameParameter(void const *p, GameRoot *root)
            {
                PERFSTATS_ENTRY();
                __TRY__

                using namespace RoomSo;
                using namespace context;
                using namespace message;
                using namespace gamelogic;
                using namespace process;
                using namespace config;

                TGAME_CB_GameParameter const *nnrs = static_cast<TGAME_CB_GameParameter const *>(p);
                DLOG_TRACE("roomid:" << root->roomid() << ", "<< "TGAME_GameParameter_E" << ", roomKey:" << nnrs->sRoomKey << ", roomName:" << nnrs->sRoomName);

                root->cfg->setRoomKey(nnrs->sRoomKey);
                root->cfg->setRoomName(nnrs->sRoomName);
                root->cfg->setCreateTime(nnrs->lCreateTime);
                root->cfg->setLimitPeople(nnrs->iLimitPeople);
                root->cfg->setMinTableBet(nnrs->lMinTableBet);
                root->cfg->setMaxTableBet(nnrs->lMaxTableBet);
                root->cfg->setMinBet(nnrs->lMinBet);
                root->cfg->setMaxBet(nnrs->lMaxBet);
                root->cfg->setFee(nnrs->lFee);

                root->cfg->clearBet();
                root->cfg->clearAreaOdds();
                root->cfg->clearAreaLimit();
                root->cfg->clearAreaPlayerLimit();
                for (auto item : nnrs->vBet)
                {
                    root->cfg->pushBet(item);
                }
                for (auto item : nnrs->mAreaOdds)
                {
                    root->cfg->insertAreaOdds(item.first%1000, item.second);
                }
                for (auto item : nnrs->mAreaLimit)
                {
                    root->cfg->insertAreaLimit(item.first%1000, item.second);
                }
                for (auto item : nnrs->mAreaPlayerLimit)
                {
                    root->cfg->insertAreaPlayerLimit(item.first%1000, item.second);
                }

                // 上庄额度(因为放在con所以特殊提出来)
                root->con->setCreateID(nnrs->lCreateID);
                root->con->setBalance(nnrs->lBalance);
            
                //check game begin
                CheckBegin(root);
                
                __CATCH__
                PERFSTATS_EXIT();
            }
        }
    }
}
