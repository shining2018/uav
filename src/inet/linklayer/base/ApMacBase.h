/*
 * ApMacBase.h
 *
 *  Created on: 2018Äê1ÔÂ25ÈÕ
 *      Author: NETLAB
 */

#ifndef INET_LINKLAYER_BASE_APMACBASE_H_
#define INET_LINKLAYER_BASE_APMACBASE_H_

#include "inet/common/INETDefs.h"
#include "inet/mobility/base/MovingMobilityBase.h"
#include "inet/common/geometry/common/Coord.h"
namespace inet
{
class ApMacBase : public cSimpleModule
{
protected:
    simtime_t m_SlotLength;
    int m_SlotNum;

    MovingMobilityBase *m_Mobility;


protected:
    virtual void initialize(int stage) override;

public:
    Coord getCurrentPosition();
    ApMacBase();
};
}




#endif /* INET_LINKLAYER_BASE_APMACBASE_H_ */
