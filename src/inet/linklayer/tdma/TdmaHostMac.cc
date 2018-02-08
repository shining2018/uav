/*
 * TdmaHostMac.cc
 *
 *  Created on: 2018Äê1ÔÂ25ÈÕ
 *      Author: NETLAB
 */

#include "inet/linklayer/tdma/TdmaHostMac.h"
#include "inet/common/PacketKinds.h"
#include "inet/physicallayer/idealradio/IdealRadio.h"
#include "inet/common/ModuleAccess.h"
#define MIN_TIME 0.00000001

namespace inet
{
Define_Module(TdmaHostMac);

TdmaHostMac::TdmaHostMac()
{
    m_SelfMsgData = nullptr;
    m_SelfMsgReq = nullptr;
}

TdmaHostMac::~TdmaHostMac()
{
    cancelAndDelete(m_SelfMsgData);
    cancelAndDelete(m_SelfMsgReq);
}

void TdmaHostMac::initialize(int stage)
{
    HostMacBase::initialize(stage);

    if(stage == INITSTAGE_LINK_LAYER)
    {
        m_ReqSlotNum = par("reqSlotNum");
        m_AckSlotNum = par("ackSlotNum");

        EV<<"Parameters initialization: "<<endl;
        EV<<"reqSlotNum="<<m_ReqSlotNum<<endl;
        EV<<"ackSlotNum="<<m_AckSlotNum<<endl;

        getContainingNode(this)->subscribe(IdealRadio::m_OutOfRangeSignal,this);
        getContainingNode(this)->subscribe(IdealRadio::m_TxFailSignal,this);

        m_SelfMsgData = new cMessage("SelfMsgData");
        m_SelfMsgReq = new cMessage("SelfMsgReq");

        scheduleAt(simTime(),m_SelfMsgReq);
    }
}

void TdmaHostMac::handleMessage(cMessage *msg)
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

void TdmaHostMac::handleSelfMsg(cMessage *msg)
{
    if(msg == m_SelfMsgReq)
    {
        EV<<this->getName()<<" receives a self message: "<< msg->getName()<<
                ", and schedule the next one at "<<(simTime()+m_SlotLength*m_SlotNum,m_SelfMsgReq)<<endl;

        scheduleAt(simTime()+m_SlotLength*m_SlotNum,m_SelfMsgReq);

        if(getDistance() > m_CommunicationRange)
        {
            m_PkQueue->clear();
            m_ReTransQueue->clear();
            m_PkBufQueue->clear();
        }
        else
        {
            sendReq();
        }

    }
    else
    {
        if(msg == m_SelfMsgData)
        {
            EV<<this->getName()<<" receives a self message: "<< msg->getName()<<endl;

            sendData();
        }
        else
        {
            throw cRuntimeError("TdmaHostMac -- self message type error!");
        }
    }
}

void TdmaHostMac::handleNonSelfMsg(cMessage *msg)
{
    if(msg->getKind() == AP_ACK)
    {
        EV<<this->getName()<<" receives a non-self message: "<< msg->getName()<<endl;

        TdmaAck *ack = dynamic_cast<TdmaAck *>(msg);
        m_DataSlotIndex = ack->getSlotIndex();
        m_DataSlotNum = ack->getSlotNum();
        delete msg;
        EV<<"Slots allocated for this host is: index="<<m_DataSlotIndex<<", number="<<m_DataSlotNum<<endl;

        simtime_t dataSendTime = simTime() + m_SlotLength*m_DataSlotIndex;
        scheduleAt(dataSendTime,m_SelfMsgData);
        EV<<"Host will send data at "<<dataSendTime<<endl;
    }
    else
    {

        EV<<this->getName()<<" receives a message from "<<msg->getArrivalGate()->getName()<<endl;

        //cMessage *dup = msg->dup();
        //send(dup,"upperLayerOutPkBufQueue");

        msg->setKind(HOST_DATA);
        send(msg,"radioInOut$o");


        EV<<"msg is sent to radio."<<endl;

    }
}

void TdmaHostMac::sendReq()
{
    TdmaReq *req = new TdmaReq();
    req->setKind(HOST_REQUEST);
    req->setHostId(m_Parent->getId());
    req->setHostPath(m_Parent->getFullPath().c_str());

    EV<<"A request is sent to Ap. The detailed parameters: "<<endl;
    EV<<"Host ID: "<<m_Parent->getId()<<endl;
    EV<<"Host Path: "<<m_Parent->getFullPath()<<endl;

    send(req,"radioInOut$o");
}

void TdmaHostMac::sendData()
{
    while(m_PkBufQueue->getLength() != 0)
    {
        m_PkBufQueue->requestPacket();
    }

    int propagationSlots = getPropagationSlots();

    int leftSlots = m_DataSlotNum - propagationSlots;

    EV<<"Allocated slot number and propagation slot number are "<<m_DataSlotNum<<","<< propagationSlots<<
            ", therefore only "<<leftSlots<<" slots left."<<endl;

    for(int i = 0; i < leftSlots; i++)
    {
        EV<<"reTransQueue length: "<<m_ReTransQueue->getLength()<<", pkQueue length:"<<m_PkQueue->getLength()<<endl;

        if(m_ReTransQueue->getLength() != 0)
        {
            m_ReTransQueue->requestPacket();
        }
        else
        {
            if(m_PkQueue->getLength() != 0)
            {
                m_PkQueue->requestPacket();
            }
            else
            {
                EV<<"Queue is empty!"<<endl;
                return;
            }
        }
    }
}

void TdmaHostMac::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj, cObject *details)
{

    if(signalID == IdealRadio::m_TxFailSignal)
    {
        m_PkBufQueue->enqueue(dynamic_cast<cMessage *>(obj));
    }
    else
    {

    }
}

}

