#ifndef LLSERVICE_H_
#define LLSERVICE_H_

#include "artery/application/ItsG5Service.h"
#include "vehicle.h"

// forward declaration
namespace traci { class VehicleController; }

class LLService : public artery::ItsG5Service
{
    public:
        void trigger() override;

    protected:
        void initialize() override;
        void indicate(const vanetza::btp::DataIndication&, omnetpp::cPacket*)
        const traci::VehicleController* mVehicleController = nullptr;
        vehicle LLInfo;
};

#endif /* LLSERVICE_H_ */
