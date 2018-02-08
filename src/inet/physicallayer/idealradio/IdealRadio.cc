/*
 * IdealRadio.cc
 *
 *  Created on: 2018Äê1ÔÂ22ÈÕ
 *      Author: NETLAB
 */
#include "inet/physicallayer/idealradio/IdealRadio.h"
#include "inet/common/PacketKinds.h"

namespace inet
{
Define_Module(IdealRadio);
simsignal_t IdealRadio::m_TxSucceedSignal=cComponent::registerSignal("txSucceed");
simsignal_t IdealRadio::m_TxFailSignal=cComponent::registerSignal("txFail");
simsignal_t IdealRadio::m_OutOfRangeSignal = cComponent::registerSignal("outOfRange");

void IdealRadio::initialize(int stage)
{
    if(stage == INITSTAGE_LOCAL)
    {
        m_Alpha = par("alpha");
        m_TxRate = par("txRate");
        m_TxPower = par("txPower");
        m_TxGain = par("txGain");
        m_RxGain = par("rxGain");
        m_Frequency = par("frequency");


        m_Ap=getModuleByPath("ap");
        if(!m_Ap)
        {
            throw cRuntimeError("HostMacBase--Ap not found!");
        }
        else
        {
            EV_DEBUG<<this->getFullName()<<" found Ap: "<<m_Ap->getFullName()<<endl;
        }
    }
}

void IdealRadio::handleMessage(cMessage *msg)
{
    if(msg->getKind() == AP_ACK)
    {
        EV<<this->getName()<<" receives a packet from AP."<<endl;
        send(msg,"macInOut$o");
    }
    else
    {
        EV<<this->getName()<<" receives a packet from link layer."<<endl;
        //TODO:
        m_random=dblrand();
        EV<<"random number="<<m_random<<endl;
        if(m_random>getPER())
        {
            EV<<this->getName()<<" sends a packet to AP."<<endl;
            emit(m_TxSucceedSignal,msg);
            sendDirect(msg,m_Ap->gate("in"));
        }
        else
        {
            emit(m_TxFailSignal,msg);
        }
    }
}

double IdealRadio::getPER()
{
    return 0.05;
}
}



