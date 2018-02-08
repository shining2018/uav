/*
 * TdmaApMac.h
 *
 *  Created on: 2018Äê1ÔÂ25ÈÕ
 *      Author: NETLAB
 */

#ifndef INET_LINKLAYER_TDMA_TDMAAPMAC_H_
#define INET_LINKLAYER_TDMA_TDMAAPMAC_H_

#include "inet/linklayer/base/ApMacBase.h"
#include "inet/linklayer/tdma/TdmaReq_m.h"
#include "inet/linklayer/tdma/TdmaAck_m.h"

namespace inet
{
class INET_API TdmaApMac:public ApMacBase
{
private:
    int m_ReqSlotNum;
    int m_AckSlotNum;

    cMessage *m_SelfMsgAck;

    cQueue m_ReqQueue;

protected:
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void handleMessage(cMessage *msg) override;
    void handleSelfMsg(cMessage *msg);
    void handleNonSelfMsg(cMessage *msg);
    void sendAck();

public:
    TdmaApMac();
    ~TdmaApMac();

};
}



#endif /* INET_LINKLAYER_TDMA_TDMAAPMAC_H_ */
