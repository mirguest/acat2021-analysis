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
};

#endif
