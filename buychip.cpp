#include "common/macros.h"
#include "common/nndef.h"
#include "gameroot.h"
#include "context/context.h"
#include "cowboy.pb.h"
#include "Comm/ITableGame.h"
#include "config/gameconfig.h"
#include "utils/tarslog.h"
#include "process/process.h"
#include "context/context.h"
#include "message/sendroommessage.h"
#include "message/sendclientmessage.h"
#include "logic/clientlogic/core/testbegin.h"
#include "CommonCode.pb.h"

using namespace nndef;

namespace game
{
    namespace logic
    {
        namespace roomlogic
        {
            int BuyChip(void const *p, GameRoot *root)
            {
                PERFSTATS_ENTRY();
                __TRY__

                using namespace RoomSo;
                using namespace config;
                using namespace process;
                using namespace context;
                using namespace message;
                using namespace clientlogic;
                using namespace XGameDZProto;

                TGAME_RoomBuyChip const *nnrs = static_cast<TGAME_RoomBuyChip const *>(p);

                DLOG_TRACE("BuyChip roomid:" << root->roomid() << ", uid:" << nnrs->lPlayerID << ", buynum:" << nnrs->lBuyNum);

                long lPlayerID = nnrs->lPlayerID;
                long lBuyNum = nnrs->lBuyNum;

                //玩家
                User *user = root->con->getUserByUid(lPlayerID);
                if (user == NULL)
                {
                    DLOG_TRACE( "user not exist, uid: " << nnrs->lPlayerID);
                }

                // 如果是货币不足
                if (nnrs->lBuyNum == 0)
                {
                    XGameCBProto::CB_msg2cBuyChip cm;
                    cm.set_iresultid(XGameRetCode::GAME_GOLD_LACK);
                    sendClientMessage<XGameCBProto::CB_msg2cBuyChip>(lPlayerID, XGameCBProto::E_CB_msg2csBuyChip_E, cm, root);
                    return 0;
                }

                if (user)
                {
                    user->setCoin(user->getCoin() + lBuyNum);
                    XGameCBProto::CB_msg2cBuyChip cm;
                    cm.set_iresultid(0);
                    cm.set_ltakein(lBuyNum);
                    sendClientMessage<XGameCBProto::CB_msg2cBuyChip>(lPlayerID, XGameCBProto::E_CB_msg2csBuyChip_E, cm, root);
                    return 0;
                }


                // 这是错误
                XGameCBProto::CB_msg2cBuyChip cm;
                cm.set_iresultid(XGameRetCode::PACKAGE_ERROR);
                sendClientMessage<XGameCBProto::CB_msg2cBuyChip>(lPlayerID, XGameCBProto::E_CB_msg2csBuyChip_E, cm, root);

                __CATCH__
                PERFSTATS_EXIT();
                return 0;
            }
        }
    }
}
