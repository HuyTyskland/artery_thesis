#include "MService.h"
#include "step1_msgs/V2Vmsg_m.h"
#include "artery/traci/VehicleController.h"
#include <vanetza/btp/data_request.hpp>
#include <vanetza/dcc/profile.hpp>
#include <vanetza/geonet/interface.hpp>

using namespace omnetpp;
using namespace vanetza;

Define_Module(MService)

void MService::initialize()
{
    ItsG5Service::initialize();
    mVehicleController = &getFacilities().get_const<traci::VehicleController>();
    MInfo.ID = mVehicleController->getVehicleId();
}

void MService::trigger()
{
    Enter_Method("MService trigger");
    auto& vehicle_api = mVehicleController->getTraCI()->vehicle;

    auto msg = new V2Vmsg();
    msg->setID((MInfo.ID).c_str());
    msg->setLane(vehicle_api.getLaneIndex(MInfo.ID));
    msg->setIsPM(1);
    msg->setByteLength(40);

    btp::DataRequestB req;
    req.destination_port = host_cast<MService::port_type>(getPortNumber());
    req.gn.transport_type = geonet::TransportType::SHB;
    req.gn.traffic_class.tc_id(static_cast<unsigned>(dcc::Profile::DP2));
    req.gn.communication_profile = geonet::CommunicationProfile::ITS_G5;
    request(req, msg);
}

void MService::indicate(const vanetza::btp::DataIndication& ind, omnetpp::cPacket* packet)
{
    Enter_Method("MService indicate");
    auto msg = check_and_cast<const V2Vmsg*>(packet);

    auto& vehicle_api = mVehicleController->getTraCI()->vehicle;
    if (msg->getIsPM() == 1) // messages from member in the same lane
    {

    }
    delete msg;
}