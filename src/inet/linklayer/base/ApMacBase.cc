/*
 * ApMacBase.cc
 *
 *  Created on: 2018Äê1ÔÂ25ÈÕ
 *      Author: NETLAB
 */

#include "inet/linklayer/base/ApMacBase.h"

namespace inet
{
Define_Module(ApMacBase);

ApMacBase::ApMacBase()
{
    m_SlotLength = 0;
    m_SlotNum = 0;

    m_Mobility = nullptr;
}

void ApMacBase::initialize(int stage)
{
    cSimpleModule::initialize(stage);

    if(stage == INITSTAGE_LOCAL)
    {
        m_SlotLength = par("slotLength");
        m_SlotNum = par("slotNum");
    }
    else
    {
        if(stage == INITSTAGE_LINK_LAYER)
        {
            m_Mobility = dynamic_cast<MovingMobilityBase *>(this->getParentModule()->getModuleByPath("mobility"));
        }
    }
}

Coord ApMacBase::getCurrentPosition()
{
    return m_Mobility->getCurrentPosition();
}
}


