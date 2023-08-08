#include "artery/networking/LimericDccEntity.h"
#include "artery/utility/PointerCheck.h"

//Huy's inclusion
#include "artery/networking/Router.h"

namespace artery
{
using namespace omnetpp;
//Huy's signal
const simsignal_t scAverageCBR = cComponent::registerSignal("averageCBR");
const simsignal_t scTestingVehCount = cComponent::registerSignal("testingVehCount");
const simsignal_t scUpdatedBeta = cComponent::registerSignal("updatedBeta");
const simsignal_t scDelta = cComponent::registerSignal("currentDelta");

Define_Module(LimericDccEntity)

void LimericDccEntity::finish()
{
    // free those objects before runtime vanishes
    mTransmitRateControl.reset();
    mAlgorithm.reset();
    DccEntityBase::finish();
}

vanetza::dcc::TransmitRateThrottle* LimericDccEntity::getTransmitRateThrottle()
{
    return notNullPtr(mTransmitRateControl);
}

vanetza::dcc::TransmitRateControl* LimericDccEntity::getTransmitRateControl()
{
    return notNullPtr(mTransmitRateControl);
}

void LimericDccEntity::initializeTransmitRateControl()
{
    ASSERT(mRuntime);
    using namespace vanetza::dcc;

    Limeric::Parameters params;
    params.cbr_target = mTargetCbr;

    using namespace vanetza;
    //Huy's parameter: alpha and beta
    UnitInterval alpha(par("adaptedAlpha"));
    params.alpha = alpha;
    UnitInterval beta(par("adaptedBeta"));
    params.beta = beta;

    mAlgorithm.reset(new Limeric(*mRuntime, params));
    if (par("enableDualAlpha")) {
        Limeric::DualAlphaParameters dual_params;
        mAlgorithm->configure_dual_alpha(dual_params);
    }
    mTransmitRateControl.reset(new LimericTransmitRateControl(*mRuntime, *mAlgorithm));

    mAlgorithm->on_duty_cycle_change = [this](const Limeric*, vanetza::Clock::time_point) {
        mTransmitRateControl->update();
    };

    //Huy's subscribtion
    mRouter->subscribe(Router::scVehCount, this);
}

void LimericDccEntity::onGlobalCbr(vanetza::dcc::ChannelLoad cbr)
{
    ASSERT(mAlgorithm);
    mAlgorithm->update_cbr(cbr);
    emit(scAverageCBR, (mAlgorithm->average_cbr()).value());
    double calculatedDelta = (mAlgorithm->returnDelta()).value();
    emit(scDelta, calculatedDelta);
}

//Huy's receive signal function
void LimericDccEntity::receiveSignal(cComponent*, simsignal_t signal, long value, cObject*)
{
    using namespace vanetza;
    if ((signal == Router::scVehCount) && par("enableDynamicBeta"))
    {
        emit(scTestingVehCount, value);
        double estimatedBeta = 1/(double)value;
        UnitInterval new_beta(estimatedBeta);
        mAlgorithm->update_beta(new_beta);
    }
    double updatedBeta = mAlgorithm->returnBeta();
    emit(scUpdatedBeta, updatedBeta);
}

} // namespace arterd
