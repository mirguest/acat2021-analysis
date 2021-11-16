#ifndef MixingAlg_hh
#define MixingAlg_hh

#include <map>

#include <SniperKernel/AlgBase.h>

#include <EvtNavigator/NavBuffer.h>
#include <Event/SimHeader.h>
#include <Event/OECHeader.h>
#include <RootIOSvc/NavInputStream.h>
#include <BufferMemMgr/IDataMemMgr.h>

class MixingAlg: public AlgBase {

public:
    MixingAlg(const std::string& name);

    bool initialize();
    bool execute();
    bool finalize();

private:
    struct BranchStream {
        NavInputStream* stream;

        BranchStream(const std::string& fn);
        
        bool next();

        JM::EvtNavigator* get();
    };

private:
    // rates: key is the input name, value is the rate
    std::map<std::string, double> m_rates;
    std::map<std::string, std::vector<std::string>> m_inputs;
private:
    IDataMemMgr* m_buf;

    double m_current_time;

    double m_totalrates;
    double m_totaltau; // 1./m_totalrates
    std::vector<double> m_rates_cdf;           // key: label
    std::vector<std::string> m_rates_cdf_key;  // key: label
    std::vector<int> m_nbranches;              // key: label
    std::vector<std::vector<BranchStream>> m_inputstreams; // key: label, value: all the branches
};


#endif
