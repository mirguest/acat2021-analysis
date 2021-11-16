#ifndef MixingAlg_hh
#define MixingAlg_hh

#include <map>

#include <SniperKernel/AlgBase.h>

#include <EvtNavigator/NavBuffer.h>
#include <Event/SimHeader.h>
#include <Event/OECHeader.h>

class MixingAlg: public AlgBase {

public:
    MixingAlg(const std::string& name);

    bool initialize();
    bool execute();
    bool finalize();

private:
    // rates: key is the input name, value is the rate
    std::map<std::string, double> m_rates;
    std::map<std::string, std::vector<std::string>> m_inputs;
private:
    JM::NavBuffer* m_buf;

};


#endif
