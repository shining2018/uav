/*
 * LdMac.h
 *
 *  Created on: 2018Äê1ÔÂ22ÈÕ
 *      Author: NETLAB
 */

#ifndef INET_LINKLAYER_LD_LDMAC_H_
#define INET_LINKLAYER_LD_LDMAC_H_

#include "inet/common/INETDefs.h"
#include "inet/linklayer/base/HostMacBase.h"

namespace inet
{
class INET_API LdMac:public HostMacBase
{
protected:
    int m_AckSlotNum;
    int m_ReqSlotNum;

    cMessage *m_ReqSelfMsg;

protected:
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *msg) override;
    void handleSelfMsg(cMessage *msg);
    void handleNonSelfMsg(cMessage *msg);

public:
    LdMac();
    ~LdMac();
};
}



#endif /* INET_LINKLAYER_LD_LDMAC_H_ */
