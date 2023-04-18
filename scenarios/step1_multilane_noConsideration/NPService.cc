#include "NPService.h"
#include "step1_msgs/V2Vmsg_m.h"
#include "artery/traci/VehicleController.h"
#include <vanetza/btp/data_request.hpp>
#include <vanetza/dcc/profile.hpp>
#include <vanetza/geonet/interface.hpp>

using namespace omnetpp;
using namespace vanetza;

Define_Module(NPService)

void NPService::initialize()
{
    ItsG5Service::initialize();
    mVehicleController = &getFacilities().get_const<traci::VehicleController>();
    NPInfo.ID = mVehicleController->getVehicleId();
    NPInfo.lane = mVehicleController->getLaneIndex(NPInfo.ID);
}

void NPService::trigger()
{
    Enter_Method("NPService trigger");
    auto& vehicle_api = mVehicleController->getLiteAPI().vehicle();

    auto msg = new V2Vmsg();
    msg->setID(NPInfo.ID);
    msg->setLane(NPInfo.lane);
    msg->setIsPM(0);
    msg->setByteLength(40);

    btp::DataRequestB req;
    req.destination_port = host_cast<NPService::port_type>(getPortNumber());
    re.gn.transport_type = geonet::TransportType::SHB;
    req.gn.traffic_class.tc_id(static_cast<unsigned>(dcc::Profile::DP0));
    req.gn.communication_profile = geonet::CommunicationProfile::ITS_G5;
    request(req, msg);
}

void NPService::indicate(const vanetza::btp::DataIndication& ind, omnetpp::cPacket* packet)
{
    Enter_Method("NPService indicate");
    auto msg = check_and_cast<const V2Vmsg*>(packet);

    auto& vehicle_api = mVehicleController->getLiteAPI().vehicle();
    if (msg->getIsPM() == 1 && (msg->getID())[0] == 'p') // messages from member in the same lane
    {

    }
    delete msg;
}