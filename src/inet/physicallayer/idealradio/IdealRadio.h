/*
 * IdealRadio.h
 *
 *  Created on: 2018Äê1ÔÂ22ÈÕ
 *      Author: NETLAB
 */

#ifndef INET_PHYSICALLAYER_IDEALRADIO_IDEALRADIO_H_
#define INET_PHYSICALLAYER_IDEALRADIO_IDEALRADIO_H_

#include "inet/common/INETDefs.h"

namespace inet
{
class INET_API IdealRadio: public cSimpleModule
{
private:
    double m_random;
    cModule *m_Ap;

public:
    static simsignal_t m_TxSucceedSignal;
    static simsignal_t m_TxFailSignal;
    static simsignal_t m_OutOfRangeSignal;

protected:
    double m_Alpha;
    double m_TxRate;
    double m_TxPower;
    double m_TxGain;
    double m_RxGain;
    double m_Frequency;


protected:
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *msg) override;
    double getPER();

};
}



#endif /* INET_PHYSICALLAYER_IDEALRADIO_IDEALRADIO_H_ */
