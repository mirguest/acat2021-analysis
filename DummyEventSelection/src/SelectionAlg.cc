#include "SelectionAlg.hh"

#include "SniperKernel/AlgBase.h"
#include "SniperKernel/AlgFactory.h"
#include "SniperKernel/SniperLog.h"
#include "SniperKernel/SniperPtr.h"

#include "EvtNavigator/NavBuffer.h"


DECLARE_ALGORITHM(SelectionAlg);

SelectionAlg::SelectionAlg(const std::string& name) 
    : AlgBase(name), 
      m_counter_selected(0), m_counter_processed(0) {
    declProp("DelayEnergyRange", m_delay_energy_range={1.9, 2.5});
    declProp("PromptEnergyRange", m_prompt_energy_range={0.7, 12});
    declProp("TimeCut", m_deltatime_cut=0.001);
    declProp("DistanceCut", m_distance_cut=1.5);
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

    ++m_counter_processed;

    // Note:
    //   In this selection, the delayed signal will be searched first. 
    //   Then, the energy of prompt signal will be used.
    //   After that, the delta time should be less than Tcut
    //   Finally, the distance should be less than Dcut.
    //
    //   -- Tao Lin <lintao AT ihep.ac.cn>, 2021-11-17

    // if only one event in the buffer, skip
    if (m_buf->size()<2) {
        return true;
    }

    // energy of delayed signal
    auto delayed_energy = oecevt->getEnergy();
    if (delayed_energy<m_delay_energy_range[0] 
     || delayed_energy>m_delay_energy_range[1]) {
        return true;
    }

    // loop from begin to current
    int counter_found_prompt = 0;

    for (auto it = m_buf->begin(); it != m_buf->current(); ++it) {
        auto hdr = dynamic_cast<JM::OECHeader*>((*it)->getHeader("/Event/OEC"));
        if (not hdr) {
            LogError << "Failed to find the OECHeader. " << std::endl;
            return false;
        }

        auto evt = dynamic_cast<JM::OECEvent*>(hdr->event());
        if (not evt) {
            LogError << "Failed to find the OECEvent. " << std::endl;
            return false;
        }

        // energy of prompt signal
        auto prompt_energy = evt->getEnergy();
        if (prompt_energy<m_prompt_energy_range[0] 
         || prompt_energy>m_prompt_energy_range[1]) {
            continue;
        }

        // delta time 
        double delta_second = oecevt->getTime().AsDouble() - evt->getTime().AsDouble();
        if (delta_second<0 || delta_second>m_deltatime_cut) {
            continue;
        }

        // delta distance
        double dx =  oecevt->getVertexX() - evt->getVertexX();
        double dy =  oecevt->getVertexY() - evt->getVertexY();
        double dz =  oecevt->getVertexZ() - evt->getVertexZ();
        float distance = sqrt(dx*dx+dy*dy+dz*dz) / 1e3; // convert from mm to m
        if (distance > m_distance_cut) {
            continue;
        }

        ++counter_found_prompt;
    }

    // can't find any prompt
    if (counter_found_prompt<1) {
        return true;
    }

    // save the delayed signal
    ++m_counter_selected;
    return true;
}

bool SelectionAlg::finalize() {
    LogInfo << "Total process " << m_counter_processed << " events. "
            << "Total select " << m_counter_selected << " events. "
            << " with following cuts: " << std::endl;
    LogInfo << " Prompt Energy Range: ["
            << m_prompt_energy_range[0] << ", "
            << m_prompt_energy_range[1] << "]" << std::endl;
    LogInfo << " Delay Energy Range: ["
            << m_delay_energy_range[0] << ", "
            << m_delay_energy_range[1] << "]" << std::endl;
    LogInfo << " Delta time cut (s): " << m_deltatime_cut << std::endl;
    LogInfo << " Distance cut (m): " << m_distance_cut << std::endl;
    return true;
}
