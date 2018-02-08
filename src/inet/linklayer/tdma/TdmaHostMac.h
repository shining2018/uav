/*
 * TdmaHostMac.h
 *
 *  Created on: 2018Äê1ÔÂ25ÈÕ
 *      Author: NETLAB
 */

#ifndef INET_LINKLAYER_TDMA_TDMAHOSTMAC_H_
#define INET_LINKLAYER_TDMA_TDMAHOSTMAC_H_

#include "inet/common/INETDefs.h"
#include "inet/linklayer/base/HostMacBase.h"
#include "inet/linklayer/tdma/TdmaReq_m.h"
#include "inet/linklayer/tdma/TdmaAck_m.h"

namespace inet
{
class INET_API TdmaHostMac:public HostMacBase,public cListener
{
private:

    //parameters
    int m_ReqSlotNum;
    int m_AckSlotNum;

    cMessage *m_SelfMsgReq;
    cMessage *m_SelfMsgData;

    int m_DataSlotIndex;
    int m_DataSlotNum;

protected:
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void handleMessage(cMessage *msg) override;
    void handleSelfMsg(cMessage *msg);
    void handleNonSelfMsg(cMessage *msg);
    void sendReq();
    void sendData();
    virtual void receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj, cObject *details) override;

public:
    TdmaHostMac();
    ~TdmaHostMac();
};
}




#endif /* INET_LINKLAYER_TDMA_TDMAHOSTMAC_H_ */
