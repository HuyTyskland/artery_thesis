#include "PLService.h"
#include "step1_msgs/V2Vmsg_m.h"
#include "artery/traci/VehicleController.h"
#include <vanetza/btp/data_request.hpp>
#include <vanetza/dcc/profile.hpp>
#include <vanetza/geonet/interface.hpp>

using namespace omnetpp;
using namespace vanetza;

Define_Module(PLService)

void PLService::initialize()
{
    ItsG5Service::initialize();
    mVehicleController = &getFacilities().get_const<traci::VehicleController>();
    PLInfo.ID = mVehicleController->getVehicleId();
}

void PLService::trigger()
{
    Enter_Method("PLService trigger");
    auto& vehicle_api = mVehicleController->getTraCI()->vehicle;

    auto msg = new V2Vmsg();
    msg->setID((PLInfo.ID).c_str());
    msg->setLane(vehicle_api.getLaneIndex(PLInfo.ID));
    msg->setIsPM(1);
    msg->setByteLength(2000);

    btp::DataRequestB req;
    req.destination_port = host_cast<PLService::port_type>(getPortNumber());
    req.gn.transport_type = geonet::TransportType::SHB;
    req.gn.traffic_class.tc_id(static_cast<unsigned>(dcc::Profile::DP2));
    req.gn.communication_profile = geonet::CommunicationProfile::ITS_G5;
    request(req, msg);
}

void PLService::indicate(const vanetza::btp::DataIndication& ind, omnetpp::cPacket* packet)
{
    Enter_Method("PLService indicate");
    auto msg = check_and_cast<const V2Vmsg*>(packet);

    auto& vehicle_api = mVehicleController->getTraCI()->vehicle;
    if (msg->getLane() == PLInfo.lane && msg->getIsPM() == 1) // messages from member in the same lane
    {

    } else {
        if (msg->getIsPM() == 1 && (msg->getID())[0] == 'l') // messages from Lane Leader
        {

        }
    }
    delete msg;
}