/*
 * DaraMac.h
 *
 *  Created on: 2018Äê1ÔÂ22ÈÕ
 *      Author: NETLAB
 */

#ifndef INET_LINKLAYER_DARA_DARAMAC_H_
#define INET_LINKLAYER_DARA_DARAMAC_H_

#include "inet/common/INETDefs.h"
#include "inet/linklayer/base/HostMacBase.h"
#include "inet/linklayer/dara/DaraReq_m.h"
#include <set>
using namespace std;

namespace inet
{
class INET_API DaraMac: public HostMacBase
{
private:
    int m_ReplicasRate;
    int m_AckSlotNum;

    cMessage *m_SelfMsg;

protected:
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void handleMessage(cMessage *msg) override;
    void handleSelfMsg(cMessage *msg);
    void handleNonSelfMsg(cMessage *msg);
    int getReplicasNum();
    //void sendReplicas();
    void selectSlotIndex(set<int> &indexSet);
    void fetchRequst();

public:
    DaraMac();
    ~DaraMac();
};
}



#endif /* INET_LINKLAYER_DARA_DARAMAC_H_ */
