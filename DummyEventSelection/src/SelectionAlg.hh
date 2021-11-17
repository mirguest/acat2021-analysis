#ifndef SelectionAlg_hh
#define SelectionAlg_hh

#include <SniperKernel/AlgBase.h>
#include <EvtNavigator/NavBuffer.h>
#include <Event/OECHeader.h>


class SelectionAlg: public AlgBase {

public:
    SelectionAlg(const std::string& name);

    bool initialize();
    bool execute();
    bool finalize();

private:
    JM::NavBuffer* m_buf;

private:
    std::vector<double> m_delay_energy_range;
    std::vector<double> m_prompt_energy_range;
    double m_deltatime_cut; // in second
    double m_distance_cut; // in m

private:
    Long64_t m_counter_selected;
    Long64_t m_counter_selected_cutn; // with multiple events in buffer
    Long64_t m_counter_selected_cutenergydelay; //
    Long64_t m_counter_selected_cutenergyprompt; //
    Long64_t m_counter_selected_cutdeltatime; //
    Long64_t m_counter_selected_cutprompt; // with energy+time+distance
    Long64_t m_counter_processed;
};

#endif
