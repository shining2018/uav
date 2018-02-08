/*
 * HostMacBase.cc
 *
 *  Created on: 2018Äê1ÔÂ22ÈÕ
 *      Author: NETLAB
 */
#include "inet/linklayer/base/HostMacBase.h"
namespace inet
{
Define_Module(HostMacBase);

HostMacBase::HostMacBase()
{
    m_SlotLength = 0;
    m_SlotNum = 0;
    m_CommunicationRange = 0;
    m_PkQueue = nullptr;
    m_PkBufQueue = nullptr;
    m_ReTransQueue = nullptr;
    m_Mobility = nullptr;
}

void HostMacBase::initialize(int stage)
{
    cSimpleModule::initialize(stage);

    if(stage == INITSTAGE_LOCAL)
    {
        m_SlotLength = par("slotLength");
        m_SlotNum = par("slotNum");
        m_CommunicationRange = par("communicationRange");
    }
    else
    {
        if(stage == INITSTAGE_LINK_LAYER)
        {
            m_PkQueue = dynamic_cast<DropTailQueue *>(gate("upperLayerInPkQueue")->getPreviousGate()->getOwnerModule());
            m_ReTransQueue = dynamic_cast<DropTailQueue *>(gate("upperLayerInReTransQueue")->getPreviousGate()->getOwnerModule());
            m_PkBufQueue = dynamic_cast<DropTailQueue *>(gate("upperLayerOutPkBufQueue")->getNextGate()->getOwnerModule());

            m_Mobility = dynamic_cast<MovingMobilityBase *>(this->getParentModule()->getModuleByPath("mobility"));

            findAp();
            findParentModule();

        }
    }
}

void HostMacBase::findAp()
{
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

void HostMacBase::findParentModule()
{
    m_Parent=getParentModule();
    if(!m_Parent)
    {
        throw cRuntimeError("HostMacBase--Parent module not found");
    }
    else
    {
        EV_DEBUG<<this->getFullName()<<"'s parent is: "<<m_Parent->getFullName()<<endl;
    }
}

Coord HostMacBase::getCurrentPosition()
{
    cModule *mdMobilityOfHost = m_Parent->getSubmodule("mobility");
    IMobility *mdMovingMobilityOfHost = dynamic_cast<IMobility *>(mdMobilityOfHost);
    //EV<<"Host position: "<<mdMovingMobilityOfHost->getCurrentPosition()<<endl;
    return mdMovingMobilityOfHost->getCurrentPosition();
}

Coord HostMacBase::getApPosition()
{
    cModule *mdMobilityOfAp = m_Ap->getSubmodule("mobility");
    IMobility *mdMovingMobilityOfAp = dynamic_cast<IMobility *>(mdMobilityOfAp);
    //EV<<"Ap position: "<<mdMovingMobilityOfAp->getCurrentPosition()<<endl;
    return mdMovingMobilityOfAp->getCurrentPosition();
}

double HostMacBase::getDistance()
{
    Coord cdHost=getCurrentPosition();
    Coord cdAp=getApPosition();
    Coord cdDistance=cdHost-cdAp;

    return sqrt(cdDistance.x*cdDistance.x+cdDistance.y*cdDistance.y+cdDistance.z*cdDistance.z);

}
int HostMacBase::getPropagationSlots()
{
    double distance=getDistance();
    simtime_t stPropagationTime=distance/SPEED_OF_LIGHT;
    return ceil(stPropagationTime/m_SlotLength);

}

}



