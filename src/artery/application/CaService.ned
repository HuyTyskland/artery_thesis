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

package artery.application;

simple CaService like ItsG5Service
{
    parameters:
        @signal[CamReceived](type=CaObject);
        @signal[CamSent](type=CaObject);

        @statistic[reception](source=CamReceived;record=vector(camStationId)?,vector(camGenerationDeltaTime)?);
        @statistic[transmission](source=CamSent;record=vector(camStationId)?,vector(camGenerationDeltaTime)?);

        //huy's signal
        @signal[SNumCamSent](type=long);
        @signal[SNumCamRcvFrPL](type=long);
        @signal[SNumCamRcvFrLL](type=long);
        @signal[SNumCamRcvFrM1](type=long);
        @signal[SNumCamRcvFrM2](type=long);
        @signal[SNumCamRcvFrM3](type=long);
        @signal[SNumCamRcvFrM4](type=long);

        @statistic[NumSent](source=SNumCamSent;record=vector);
        @statistic[NumRcvPL](source=SNumCamRcvFrPL;record=vector);
        @statistic[NumRcvLL](source=SNumCamRcvFrLL;record=vector);
        @statistic[NumRcvM1](source=SNumCamRcvFrM1;record=vector);
        @statistic[NumRcvM2](source=SNumCamRcvFrM2;record=vector);
        @statistic[NumRcvM3](source=SNumCamRcvFrM3;record=vector);
        @statistic[NumRcvM4](source=SNumCamRcvFrM4;record=vector);

        //huy's signal time record
        @signal[STsFrPL](type=long);
        @signal[STsFrLL](type=long);
        @signal[STsFrM1](type=long);
        @signal[STsFrM2](type=long);
        @signal[STsFrM3](type=long);
        @signal[STsFrM4](type=long);

        @statistic[TimeLapsePL](source=STsFrPL;record=vector);
        @statistic[TimeLapseLL](source=STsFrLL;record=vector);
        @statistic[TimeLapseM1](source=STsFrM1;record=vector);
        @statistic[TimeLapseM2](source=STsFrM2;record=vector);
        @statistic[TimeLapseM3](source=STsFrM3;record=vector);
        @statistic[TimeLapseM4](source=STsFrM4;record=vector);

        //huy's signal time record
        @signal[SRcvCAMGenTime](type=unsigned long);

        @statistic[RcvCAMGenTime](source=SRcvCAMGenTime;record=vector);
        // evaluate DCC transmission interval restrictions
        bool withDccRestriction = default(true);

        // generation interval boundaries
        double minInterval @unit(s) = default(0.1s);
        double maxInterval @unit(s) = default(1s);

        // generate at fixed rate (using minInterval, optionally restricted by DCC)
        bool fixedRate = default(false);

        // change in orientation triggering CAM generation (in degree)
        double headingDelta = default(4.0);

        // change in position triggering CAM generation
        double positionDelta @unit(m) = default(4.0m);

        // change in speed triggering CAM generation (in meter/second)
        double speedDelta @unit(mps) = default(0.5mps);

        // length of path history
        volatile int pathHistoryLength = default(23);
}
