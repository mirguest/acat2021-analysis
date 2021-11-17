#include "SelectionAlg.hh"

#include "SniperKernel/AlgBase.h"
#include "SniperKernel/AlgFactory.h"
#include "SniperKernel/SniperLog.h"
#include "SniperKernel/SniperPtr.h"

#include "EvtNavigator/NavBuffer.h"


DECLARE_ALGORITHM(SelectionAlg);

SelectionAlg::SelectionAlg(const std::string& name) 
    : AlgBase(name) {

}

bool SelectionAlg::initialize() {
    SniperDataPtr<JM::NavBuffer>  navBuf(*getRoot(), "/Event");

    if ( navBuf.invalid() ) {
        LogError << "cannot get the NavBuffer @ /Event" << std::endl;
        return false;
    }
    m_buf = navBuf.data();

    return true;
}

bool SelectionAlg::execute() {

    auto nav = m_buf->curEvt();
    if (not nav) {
        LogError << "Failed to find the event navigator. " << std::endl;
        return false;
    }

    auto oechdr = dynamic_cast<JM::OECHeader*>(nav->getHeader("/Event/OEC"));
    if (not oechdr) {
        LogError << "Failed to find the OECHeader. " << std::endl;
        return false;
    }

    auto oecevt = dynamic_cast<JM::OECEvent*>(oechdr->event());

    if (not oecevt) {
        LogError << "Failed to find the OECEvent. " << std::endl;
        return false;
    }


    return true;
}

bool SelectionAlg::finalize() {

    return true;
}
