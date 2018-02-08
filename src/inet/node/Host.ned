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
import uav.inet.applications.contract.IHostApp;
import uav.inet.linklayer.contract.IHostMac;
import uav.inet.physicallayer.contract.IHostRadio;
import uav.inet.common.queue.DropTailQueue;
import uav.inet.mobility.contract.IMobility;



module Host
{
    parameters:
        @display("i=device/uav_vs");
        string appType = default("");
        string macType = default("");
        string radioType = default("");
        string mobilityType = default("StationaryMobility");
        @networkNode();
    gates:
        input in @directIn;

    submodules:
        app: <appType> like IHostApp {
            @display("p=275,27");
        }
        mac: <macType> like IHostMac {
            @display("p=275,230");
        }
        radio: <radioType> like IHostRadio {
            @display("p=275,320");
        }
        pkQueue: DropTailQueue {
            @display("p=275,115");
        }
        reTransQueue: DropTailQueue {
            @display("p=366,115");
        }
        pkBufQueue: DropTailQueue {


            @display("p=366,230");
        }
        mobility: <mobilityType> like IMobility {
            @display("p=25,42");
        }
    connections:
        app.appOut --> pkQueue.in;
        pkQueue.out --> mac.upperLayerInPkQueue;
        reTransQueue.out --> mac.upperLayerInReTransQueue;
        mac.upperLayerOutPkBufQueue --> pkBufQueue.in;
        pkBufQueue.out --> reTransQueue.in;
        mac.radioInOut <--> radio.macInOut;
        in --> radio.radioIn;

}
