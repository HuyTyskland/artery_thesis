#ifndef NPSERVICE_H_
#define NPSERVICE_H_

#include "artery/application/ItsG5Service.h"
#include "vehicle.h"

// forward declaration
namespace traci { class VehicleController; }

class NPService : public artery::ItsG5Service
{
    public:
        void trigger() override;

    protected:
        void initialize() override;
        void indicate(const vanetza::btp::DataIndication&, omnetpp::cPacket*);
        const traci::VehicleController* mVehicleController = nullptr;
        vehicle NPInfo;
};

#endif /* NPSERVICE_H_ */
