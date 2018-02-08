//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package uav.inet.node;
import uav.inet.linklayer.contract.IApMac;
import uav.inet.mobility.contract.IMobility;
import uav.inet.common.queue.Sink;

module Ap
{
    parameters:
        string mobilityType = default("StationaryMobility");
        string macType = default("");
        @display("i=device/receiverdish_l");
        @networkNode();

    gates:
        input in @directIn;

    submodules:
        mobility: <mobilityType> like IMobility {
            @display("p=25,42");
        }
        mac: <macType> like IApMac {
            @display("p=86,160");
        }
        sink: Sink {

            @display("p=86,73");
        }
    connections:
        in --> mac.inFromAp;
        mac.outToSink --> sink.in++;
}

