#include "PLService.h"
#include "msgs/V2Vmsg_m.h"
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
    PLInfo.lane = mVehicleController->getLaneIndex(PLInfo.ID);
}

void PLService::trigger()
{
    Enter_Method("PLService trigger");
    auto& vehicle_api = mVehicleController->getLiteAPI().vehicle();

    auto msg = new V2Vmsg();
    msg->setID(PLInfo.ID);
    msg->setLane(PLInfo.lane);
    msg->setIsPM(1);
    msg->setByteLength(40);

    btp::DataRequestB req;
    req.destination_port = host_cast<PLService::port_type>(getPortNumber());
    re.gn.transport_type = geonet::TransportType::SHB;
    req.gn.traffic_class.tc_id(static_cast<unsigned>(dcc::Profile::DP0));
    req.gn.communication_profile = geonet::CommunicationProfile::ITS_G5;
    request(req, msg);
}

void PLService::indicate(const vanetza::btp::DataIndication& ind, omnetpp::cPacket* packet)
{
    Enter_Method("PLService indicate");
    auto msg = check_and_cast<const V2Vmsg*>(packet);

    auto& vehicle_api = mVehicleController->getLiteAPI().vehicle();
    if (msg->getLane() == PLInfo.Lane && msg->getIsPM() == 1) // messages from member in the same lane
    {

    } else {
        if (msg->getIsPM() == 1 && (msg->getID())[0] == 'l') // messages from Lane Leader
        {

        }
    }
    delete msg;
}