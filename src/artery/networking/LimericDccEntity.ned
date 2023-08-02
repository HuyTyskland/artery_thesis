package artery.networking;

simple LimericDccEntity like IDccEntity
{
    parameters:
        @class(LimericDccEntity);
        string radioDriverModule;
        string routerModule;
        string runtimeModule;

        string ChannelProbeProcessor = default("Local");
        string NetworkEntity = default("");

        double targetCbr = default(0.6);
        int queueLength = default(2);
        bool enableDualAlpha = default(false);

        //Huy's alpha and beta variable
        double adaptedAlpha = default(0.016);
        double adaptedBeta = default(0.0012);

        //Huy's enable dynamic beta
        bool enableDynamicBeta = default(false);

        //Huy's signal
        @signal[testingVehCount](type=long);
        @statistic[VehNum_Limeric](source=testingVehCount; record=vector);

        @signal[averageCBR](type=double);
        @statistic[avgCBR](source=averageCBR; record=vector);

    gates:
        output radioDriverData;
}
