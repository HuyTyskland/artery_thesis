#include "LLService.h"
#include "step1_msgs/V2Vmsg_m.h"
#include "artery/traci/VehicleController.h"
#include <vanetza/btp/data_request.hpp>
#include <vanetza/dcc/profile.hpp>
#include <vanetza/geonet/interface.hpp>

using namespace omnetpp;
using namespace vanetza;

Define_Module(LLService)

void LLService::initialize()
{
    ItsG5Service::initialize();
    mVehicleController = &getFacilities().get_const<traci::VehicleController>();
    LLInfo.ID = mVehicleController->getVehicleId();
}

void LLService::trigger()
{
    Enter_Method("LLService trigger");
    auto& vehicle_api = mVehicleController->getTraCI()->vehicle;

    auto msg = new V2Vmsg();
    msg->setID((LLInfo.ID).c_str());
    msg->setLane(vehicle_api.getLaneIndex(LLInfo.ID));
    msg->setIsPM(1);
    msg->setByteLength(40);

    btp::DataRequestB req;
    req.destination_port = host_cast<LLService::port_type>(getPortNumber());
    req.gn.transport_type = geonet::TransportType::SHB;
    req.gn.traffic_class.tc_id(static_cast<unsigned>(dcc::Profile::DP0));
    req.gn.communication_profile = geonet::CommunicationProfile::ITS_G5;
    request(req, msg);
}

void LLService::indicate(const vanetza::btp::DataIndication& ind, omnetpp::cPacket* packet)
{
    Enter_Method("LLService indicate");
    auto msg = check_and_cast<const V2Vmsg*>(packet);

    auto& vehicle_api = mVehicleController->getTraCI()->vehicle;
    if (msg->getLane() == vehicle_api.getLaneIndex(LLInfo.ID) && msg->getIsPM() == 1)
    {

    }
    delete msg;
}