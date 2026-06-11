#include "common/macros.h"
#include "common/nndef.h"
#include "gameroot.h"
#include "context/context.h"
#include "Comm/ITableGame.h"
#include "config/gameconfig.h"
#include "utils/tarslog.h"
#include "process/process.h"
#include "logic/clientlogic/core/someact.h"
#include "context/context.h"
#include "message/sendclientmessage.h"
#include "cowboy.pb.h"

using namespace nndef;

namespace game
{
    namespace logic
    {
        namespace roomlogic
        {
            int SitDown(void const *p, GameRoot *root)
            {
                PERFSTATS_ENTRY();
                __TRY__

                using namespace RoomSo;
                using namespace config;
                using namespace process;
                using namespace clientlogic;
                using namespace context;
                using namespace message;

                TGAME_SitDown const *nnrs = static_cast<TGAME_SitDown const *>(p);
                if(!nnrs)
                {
                    return -1;
                }

                DLOG_TRACE("roomid:" << root->roomid() << ", nnrs: "<< printTars(*nnrs));

                int iRet = nnrs->ret;
                long lPlayerID = nnrs->lPlayerID;
                long lCoin     = nnrs->iChairID;
                if (iRet == 0)
                {
                    User* user = root->con->getUserByUid(lPlayerID);
                    if (!user)
                    {
                        root->con->addUser(lPlayerID, -1, false);
                        user = root->con->getUserByUid(lPlayerID);
                        if (user)
                        {
                            user->setCoin(lCoin);
                        }
                    }
                }

                //通知客户端
                XGameCBProto::CB_msg2cSit nncm;
                nncm.set_iresultid(nnrs->ret);
                nncm.set_ltakein(nnrs->iChairID);
                
                sendClientMessage<XGameCBProto::CB_msg2cSit>(nnrs->lPlayerID, XGameCBProto::E_CB_msg2csSit_E, nncm, root);

                __CATCH__
                PERFSTATS_EXIT();
                return 0;
            }
        }
    }
}
