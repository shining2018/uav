/*
 * TdmaApMac.cc
 *
 *  Created on: 2018Äê1ÔÂ25ÈÕ
 *      Author: NETLAB
 */

#include "inet/linklayer/tdma/TdmaApMac.h"
#include "inet/common/PacketKinds.h"

namespace inet
{
Define_Module(TdmaApMac);

TdmaApMac::TdmaApMac()
{
    m_ReqSlotNum = 0;
    m_AckSlotNum = 0;
    m_SelfMsgAck = nullptr;
}

TdmaApMac::~TdmaApMac()
{
    cancelAndDelete(m_SelfMsgAck);
}

void TdmaApMac::initialize(int stage)
{
    ApMacBase::initialize(stage);
    if(stage == INITSTAGE_NETWORK_LAYER)
    {
        m_ReqSlotNum = par("reqSlotNum");
        m_AckSlotNum = par("ackSlotNum");
        EV<<"Parameters initialization: "<<endl;
        EV<<"reqSlotNum="<<m_ReqSlotNum<<endl;
        EV<<"ackSlotNum="<<m_AckSlotNum<<endl;

        m_SelfMsgAck = new cMessage("SelfMsgAck");
        scheduleAt(m_SlotLength*m_ReqSlotNum,m_SelfMsgAck);
    }
}

void TdmaApMac::handleMessage(cMessage *msg)
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

void TdmaApMac::handleSelfMsg(cMessage *msg)
{
    if(msg == m_SelfMsgAck)
    {
        EV<<this->getName()<<" receives a self message: "<< msg->getName()<<
                ", and schedule the next one at "<<(simTime()+m_SlotLength*m_SlotNum)<<endl;
        scheduleAt(simTime()+m_SlotLength*m_SlotNum,msg);

        sendAck();
    }
    else
    {

    }
}

void TdmaApMac::handleNonSelfMsg(cMessage *msg)
{
    switch(msg->getKind())
    {
    case HOST_REQUEST:
    {
        EV<<"Ap receives a HOST_REQUEST packet: "<<msg->getName()<<endl;
        m_ReqQueue.insert(msg);
        break;
    }

    case HOST_DATA:
    {
        EV<<"Ap receives a HOST_DATA packet: "<<msg->getName()<<endl;
        send(msg,"outToSink");
        break;
    }

    default:
    {
        throw cRuntimeError("TdmaApMac -- Non self message type error!");
    }

    }
}

void TdmaApMac::sendAck()
{
    int queueLength=m_ReqQueue.getLength();
    EV_INFO<<"There are "<<queueLength<<" requests in m_ReqQueue."<<endl;

    if(queueLength != 0)
    {
        int avgSlotNum = (m_SlotNum-m_ReqSlotNum-m_AckSlotNum) / queueLength;
        int leftSlotNum = (m_SlotNum-m_ReqSlotNum-m_AckSlotNum) % queueLength;
        EV<<"average slot num is "<<avgSlotNum<<", and left is "<<leftSlotNum<<endl;

        int slotIndex = 0;
        int slotNum = 0;
        cModule *mdHost;
        for(int i = 0; i < queueLength; i++)
        {
            TdmaAck *ack = new TdmaAck();
            ack->setKind(AP_ACK);
            ack->setSlotIndex(slotIndex);
            if(i <leftSlotNum)
            {
                slotNum = avgSlotNum +1;
            }
            else
            {
                slotNum = avgSlotNum;
            }
            ack->setSlotNum(slotNum);
            mdHost=getModuleByPath((dynamic_cast<TdmaReq *>(m_ReqQueue.get(i)))->getHostPath());

            EV<<"The "<<i<<"th host "<<mdHost->getFullName()<<" is allocated "<<slotNum<<" slots, and the index is "<<slotIndex<<endl;

            sendDirect(ack,m_SlotLength*m_AckSlotNum,0,mdHost->gate("in"));

            slotIndex += slotNum;
        }
    }

    m_ReqQueue.clear();
}



}
