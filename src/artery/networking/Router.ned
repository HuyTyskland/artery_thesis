package artery.networking;

simple Router
{
    parameters:
        @class(Router);
        @signal[IdentityChanged](type=long);
        @signal[LinkReception](type=GeoNetPacket);
        //Huy's signal
        @signal[VehCount](type=long);
        @statistic[VehCount_router](source=VehCount; record=vector);

        @statistic[LinkLatency](source="messageAge(LinkReception)"; unit=s; record=vector?);

        string dccModule;
        string middlewareModule;
        string radioDriverModule;
        string runtimeModule;
        string securityModule;

        bool deferInitialBeacon = default(true);
        bool disableBeaconing = default(false);
        bool isMobile = default(true);

    gates:
        input radioDriverData;
        input radioDriverProperties;
}
