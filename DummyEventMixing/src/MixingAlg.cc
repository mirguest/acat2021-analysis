#include "MixingAlg.hh"

#include "SniperKernel/AlgBase.h"
#include "SniperKernel/AlgFactory.h"
#include "SniperKernel/SniperLog.h"
#include "SniperKernel/SniperPtr.h"

#include "EvtNavigator/NavBuffer.h"

DECLARE_ALGORITHM(MixingAlg);

MixingAlg::MixingAlg(const std::string& name)
    : AlgBase(name) {

    declProp("Rates", m_rates);
    declProp("Inputs", m_inputs);
}

bool MixingAlg::initialize() {

    return true;
}

bool MixingAlg::execute() {

    return true;
}

bool MixingAlg::finalize() {

    return true;
}
