/*
 * IMobility.cc
 *
 *  Created on: 2018��1��23��
 *      Author: NETLAB
 */

#include "inet/mobility/contract/IMobility.h"

namespace inet {

simsignal_t IMobility::mobilityStateChangedSignal = cComponent::registerSignal("mobilityStateChanged");

} // namespace inet


