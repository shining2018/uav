/*
 * LdMac.cc
 *
 *  Created on: 2018Äê1ÔÂ22ÈÕ
 *      Author: NETLAB
 */

#include "inet/linklayer/ld/LdMac.h"

namespace inet
{
Define_Module(LdMac);

LdMac::LdMac()
{
    m_AckSlotNum = 0;
    m_ReqSlotNum = 0;
    m_ReqSelfMsg = nullptr;
}

LdMac::~LdMac()
{
    cancelAndDelete(m_ReqSelfMsg);
}

void LdMac::initialize(int stage)
{
    HostMacBase::initialize(stage);

    if(stage == INITSTAGE_LINK_LAYER)
    {
        m_AckSlotNum = par("ackSlotNum");
        m_ReqSlotNum = par("reqSlotNum");
        m_ReqSelfMsg = new cMessage("ReqSelfMsg");
        scheduleAt(0,m_ReqSelfMsg);
    }
}

void LdMac::handleMessage(cMessage *msg)
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

void LdMac::handleSelfMsg(cMessage *msg)
{
    EV_INFO<<"LdMac receive a msg: "<<msg->getFullPath();
    send(msg,"radioInOut");
}

void LdMac::handleNonSelfMsg(cMessage *msg)
{

}

}


