#include "common/macros.h"
#include "common/nndef.h"
#include "gameroot.h"
#include "context/context.h"
#include "Comm/ITableGame.h"
#include "config/gameconfig.h"
#include "utils/tarslog.h"
#include "process/process.h"
#include "logic/clientlogic/core/tokenbet.h"
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
            int RobotBet(void const *p, GameRoot *root)
            {
                int iRet = 0;
/*                PERFSTATS_ENTRY();*/
                __TRY__

                using namespace RoomSo;
                using namespace config;
                using namespace process;
                using namespace clientlogic;
                using namespace context;
                using namespace message;

                TGAME_RobotBet const *nnrs = static_cast<TGAME_RobotBet const *>(p);
                if(!nnrs)
                {
                    return -1;
                }

                //DLOG_TRACE("roomid:" << root->roomid() << ", nnrs: "<< printTars(*nnrs));

               /* srand(TNOW);
                for(auto user_item : root->con->getUserMap())
                {
                    User* tuser = root->con->getUserByUid(user_item.first);
                    if(!tuser->isRobot() || tuser->getWealth() < 10000)
                    {
                        continue;
                    }
                    if(rand() % 100 < 20)
                    {
                        int bet_index = rand() % root->cfg->getVecGuessNum().size();
                        long bet_num = root->cfg->getVecGuessNum()[bet_index];
                        if(tuser->getWealth() < bet_num)
                        {
                            continue;
                        }

                        XGameHDProto::HD_msg2csTokenBet cm;
                        cm.set_lplayerid(user_item.first);
                        cm.set_ibettype(0);
                        cm.set_idlerid(rand() % 4 + NN_AREAID_IDLER * 1000);
                        cm.set_lbetnum(bet_num);

                        vector<char> vecOutBuffer;
                        pbTobuffer(cm, vecOutBuffer);
                        clientlogic::TokenBet(user_item.first, vecOutBuffer, root);
                    }
                }*/

                User* user = root->con->getUserByUid(nnrs->lPlayerID);
                if(!user || !user->isRobot() || user->getWealth() < nnrs->lBetNum)
                {
                    return 0;
                }

                XGameHDProto::HD_msg2csTokenBet cm;
                cm.set_lplayerid(nnrs->lPlayerID);
                cm.set_ibettype(0);
                cm.set_idlerid(nnrs->iAreaID + NN_AREAID_IDLER * 1000);
                cm.set_lbetnum(nnrs->lBetNum);

                vector<char> vecOutBuffer;
                pbTobuffer(cm, vecOutBuffer);
                iRet = clientlogic::TokenBet(nnrs->lPlayerID, vecOutBuffer, root);
                __CATCH__
/*                PERFSTATS_EXIT();*/
                return iRet;
            }
        }
    }
}
