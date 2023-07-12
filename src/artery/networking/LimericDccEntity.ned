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

    gates:
        output radioDriverData;
}
