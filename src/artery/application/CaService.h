/*
* Artery V2X Simulation Framework
* Copyright 2014-2019 Raphael Riebl et al.
* Licensed under GPLv2, see COPYING file for detailed license and warranty terms.
*/

#ifndef ARTERY_CASERVICE_H_
#define ARTERY_CASERVICE_H_

#include "artery/application/ItsG5BaseService.h"
#include "artery/utility/Channel.h"
#include "artery/utility/Geometry.h"
#include <vanetza/asn1/cam.hpp>
#include <vanetza/btp/data_interface.hpp>
#include <vanetza/units/angle.hpp>
#include <vanetza/units/velocity.hpp>
#include <omnetpp/simtime.h>

namespace artery
{

class NetworkInterfaceTable;
class Timer;
class VehicleDataProvider;

class CaService : public ItsG5BaseService
{
	public:
		CaService();
		void initialize() override;
		void indicate(const vanetza::btp::DataIndication&, std::unique_ptr<vanetza::UpPacket>) override;
		void trigger() override;

	private:
		void checkTriggeringConditions(const omnetpp::SimTime&);
		bool checkHeadingDelta() const;
		bool checkPositionDelta() const;
		bool checkSpeedDelta() const;
		void sendCam(const omnetpp::SimTime&);
		void emitCorrespondingSignal(const CaObject);
		void emitTimeReceived(const CaObject);
		omnetpp::SimTime genCamDcc();

		ChannelNumber mPrimaryChannel = channel::CCH;
		const NetworkInterfaceTable* mNetworkInterfaceTable = nullptr;
		const VehicleDataProvider* mVehicleDataProvider = nullptr;
		const Timer* mTimer = nullptr;
		LocalDynamicMap* mLocalDynamicMap = nullptr;

		omnetpp::SimTime mGenCamMin;
		omnetpp::SimTime mGenCamMax;
		omnetpp::SimTime mGenCam;
		unsigned mGenCamLowDynamicsCounter;
		unsigned mGenCamLowDynamicsLimit;
		Position mLastCamPosition;
		vanetza::units::Velocity mLastCamSpeed;
		vanetza::units::Angle mLastCamHeading;
		omnetpp::SimTime mLastCamTimestamp;
		omnetpp::SimTime mLastLowCamTimestamp;
		vanetza::units::Angle mHeadingDelta;
		vanetza::units::Length mPositionDelta;
		vanetza::units::Velocity mSpeedDelta;
		bool mDccRestriction;
		bool mFixedRate;
		bool mIsLowPriority;

		//huy statistics
		long NumCamSent = 0; //Number of Cam a vehicle send
		long NumRcvFrPL = 0; //number of Cam a vehicle receive from PL
		long NumRcvFrLL = 0; //number of Cam a vehicle receive from LL
		long NumRcvFrM1 = 0; //number of Cam a vehicle receive from M1
		long NumRcvFrM2 = 0; //number of Cam a vehicle receive from M2
		long NumRcvFrM3 = 0; //number of Cam a vehicle receive from M3
		long NumRcvFrM4 = 0; //number of Cam a vehicle receive from M4

		//Huy time statistic
		omnetpp::SimTime lastPLTime = 0; // timestamp of the last received message from PL
		omnetpp::SimTime lastLLTime = 0; // timestamp of the last received message from LL
		omnetpp::SimTime lastM1Time = 0; // timestamp of the last received message from M1
		omnetpp::SimTime lastM2Time = 0; // timestamp of the last received message from M2
		omnetpp::SimTime lastM3Time = 0; // timestamp of the last received message from M3
		omnetpp::SimTime lastM4Time = 0; // timestamp of the last received message from M4
};

vanetza::asn1::Cam createCooperativeAwarenessMessage(const VehicleDataProvider&, uint16_t genDeltaTime);
void addLowFrequencyContainer(vanetza::asn1::Cam&, unsigned pathHistoryLength = 0);

} // namespace artery

#endif /* ARTERY_CASERVICE_H_ */
