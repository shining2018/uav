/*
 * DaraMac.cc
 *
 *  Created on: 2018Äê1ÔÂ22ÈÕ
 *      Author: NETLAB
 */
#include "inet/linklayer/dara/DaraMac.h"
#include "inet/common/PacketKinds.h"

namespace inet
{
Define_Module(DaraMac);

DaraMac::DaraMac()
{
    m_SelfMsg = nullptr;
}

DaraMac::~DaraMac()
{
    cancelAndDelete(m_SelfMsg);
}

void DaraMac::initialize(int stage)
{
    HostMacBase::initialize(stage);

    if(stage == INITSTAGE_LINK_LAYER)
    {
        m_AckSlotNum = par("ackSlotNum");
        m_ReplicasRate =par("replicasRate");
        m_SelfMsg = new cMessage("selfmsg");
        scheduleAt(simTime(),m_SelfMsg);
        EV_INFO<<"m_SelfMsg will schedule at "<<simTime()<<endl;
    }
}

void DaraMac::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage())
    {
        handleSelfMsg(msg);
    }
    else
    {
        handleNonSelfMsg(msg);
    }
}

void DaraMac::handleSelfMsg(cMessage *msg)
{
    if(msg == m_SelfMsg)
    {
        if(simTime() != 0)
        {
            scheduleAt(simTime()+m_SlotNum*m_SlotLength,m_SelfMsg);
            EV_INFO<<"m_SelfMsg will schedule at "<<(simTime()+m_SlotNum*m_SlotLength)<<endl;

            fetchRequst();
        }
        else
        {
            scheduleAt(simTime()+m_SlotLength*(m_SlotNum-m_AckSlotNum),m_SelfMsg);
            EV_INFO<<"m_SelfMsg will schedule at "<<(simTime()+(m_SlotNum-m_AckSlotNum)*m_SlotLength)<<endl;
        }
    }
    else
    {
        if(msg->getKind() == DARA_SELF_REPLICAS)
        {
            msg->setKind(HOST_REQUEST);
            send(msg,"radioInOut");
        }
        else
        {

        }
    }
}

void DaraMac::handleNonSelfMsg(cMessage *msg)
{

    //msg from PkQueue or ReTransQueue
    if(msg->getArrivalGateId() == findGate("upperLayerInPkQueue")
            || msg->getArrivalGateId() == findGate("upperLayerInReTransQueue"))
    {
        set<int> slotIndexSet;
        selectSlotIndex(slotIndexSet);
        EV_INFO<<"Slot indexes:";
        for(set<int>::iterator it=slotIndexSet.begin();it!=slotIndexSet.end();it++)
        {
            EV_INFO<<*it<<" ";
        }
        EV_INFO<<endl;


        DaraReq *req = new DaraReq();
        req->setReqId(msg->getId());
        req->setHostId(m_Parent->getId());
        req->setHostPath(m_Parent->getFullPath().c_str());
        req->setReplicasNum(slotIndexSet.size());
        req->setIndexes(slotIndexSet);
        req->setIsRecovery(false);

        for(set<int>::iterator it = slotIndexSet.begin(); it != slotIndexSet.end(); ++it)
        {
            DaraReq *dup = req->dup();
            dup->setSlotIndex(*it);
            dup->setKind(DARA_SELF_REPLICAS);
            //TODO:propagation delay is not considered
            scheduleAt(simTime()+m_SlotLength*((*it)+m_AckSlotNum),dup);
        }

        delete req;

        send(msg,"upperLayerOutPkBufQueue");

    }
    else
    {

    }


}

void DaraMac::fetchRequst()
{
    if(m_ReTransQueue->getLength())
    {
        EV_INFO<<"m_ReTransQueue's size: "<<m_ReTransQueue->getLength()<<endl;
        m_ReTransQueue->requestPacket();
    }
    else
    {
        if(m_PkQueue->getLength())
        {
            EV_INFO<<"m_PkQueue's size: "<<m_PkQueue->getLength()<<endl;
            m_PkQueue->requestPacket();
        }
        else
        {
            EV_INFO<<"Queue is empty!"<<endl;
        }
    }
}

int DaraMac::getReplicasNum()
{
    int replicasNum = 0;
    double rd=dblrand();

    switch(m_ReplicasRate)
    {
    case 1://0.5102x2+0.4898x4
    {
        if(rd < 0.5102)
        {
            replicasNum = 2;
        }
        else
        {
            replicasNum = 4;
        }
        break;
    }
    case 2://0.5631x3+0.0436x3+0.3933x5
    {
        if(rd<0.5631)
        {
            replicasNum=2;
        }
        else
        {
            if(rd<0.6067)
            {
                replicasNum=3;
            }
            else
            {
                replicasNum=5;
            }
        }
        break;
    }
    case 3:
    {}
    default:
    {
        throw cRuntimeError("DaraMac -- Error replicas rate!");
        break;
    }
    }
    return replicasNum;
}

void DaraMac::selectSlotIndex(set<int> &indexSet)
{
    int replicasNum = getReplicasNum();

    int rdSlotIndex;
    for(int i = 0; i < replicasNum; i++)
    {
        rdSlotIndex = intrand(m_SlotNum-m_AckSlotNum);
        while(indexSet.find(rdSlotIndex)!=indexSet.end())
        {
            rdSlotIndex = intrand(m_SlotNum-m_AckSlotNum);
        }
        indexSet.insert(rdSlotIndex);
    }
}

}



