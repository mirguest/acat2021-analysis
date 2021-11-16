#include "MixingAlg.hh"

#include "SniperKernel/AlgBase.h"
#include "SniperKernel/AlgFactory.h"
#include "SniperKernel/SniperLog.h"
#include "SniperKernel/SniperPtr.h"

#include "EvtNavigator/NavBuffer.h"

#include "TRandom.h"

DECLARE_ALGORITHM(MixingAlg);

MixingAlg::MixingAlg(const std::string& name)
    : AlgBase(name),
      m_buf(nullptr), m_current_time(0), m_totalrates(0), m_totaltau(0) {

    declProp("Rates", m_rates);
    declProp("Inputs", m_inputs);
}

bool MixingAlg::initialize() {
    // GET THE DATA BUFFER
    SniperPtr<IDataMemMgr> navBuf(*getParent(), "BufferMemMgr");
    if ( navBuf.invalid() ) {
        LogError << "cannot get the NavBuffer @ /Event" << std::endl;
        return false;
    }
    m_buf = navBuf.data();


    // INIT THE INPUT STREAM
    for (auto& [key, rate]: m_rates) {
        m_totalrates += rate;

        m_rates_cdf.push_back(m_totalrates);
        m_rates_cdf_key.push_back(key);

        int nbr = m_inputs[key].size();
        m_nbranches.push_back(nbr);

        LogInfo << "key: " << key
                << " rate: " << rate
                << " cdf: " << m_totalrates
                << " nbr: " << nbr
                << std::endl;

        std::vector<BranchStream> brs;
        for (auto brfn: m_inputs[key]) {
            BranchStream br(brfn);
            brs.push_back(br);
        }

        m_inputstreams.push_back(brs);
    }

    m_totaltau = 1./m_totalrates;

    return true;
}

bool MixingAlg::execute() {

    // sample the next time
    double deltatime = gRandom->Exp(m_totaltau);

    m_current_time += deltatime;

    int sec = (int)m_current_time;
    int nsec = (int)((m_current_time-sec)*1e9);
    TTimeStamp curtime(sec, nsec);

    // sample
    double r = gRandom->Uniform(m_totalrates);
    LogInfo << "sample r: " << r << std::endl;

    // get the sample (label)
    size_t sample_idx = 0;

    for (size_t i = 0; i < m_rates_cdf.size(); ++i) {
        // select the sample key
        if (r < m_rates_cdf[i]) {
            // HERE we find it
            sample_idx = i;
            break; // found it, so skip the next loop
        }
    }

    // then, according to the label, sample which branch
    int nbranches = m_nbranches[sample_idx];
    int ibr = gRandom->Integer(nbranches);

    LogInfo << "select sample " << sample_idx << " ibr " << ibr << std::endl;

    // according to the isample and ibr, get the event
    auto& current_stream =  m_inputstreams[sample_idx][ibr];
    auto st = current_stream.next();

    auto evtnav = current_stream.get();

    // copy SimEvent to OECEvent
    auto simheader = dynamic_cast<JM::SimHeader*>(evtnav->getHeader("/Event/Sim"));
    auto simevent = dynamic_cast<JM::SimEvent*>(simheader->event());

    Float_t total_energy=0.0;
    Float_t genx=0.0;
    Float_t geny=0.0;
    Float_t genz=0.0;
    auto tracks = simevent->getTracksVec();

    for (auto& track: tracks) {
        Float_t energy = track->getQEdep();
        genx+=track->getQEdepX()*energy;
        geny+=track->getQEdepY()*energy;
        genz+=track->getQEdepZ()*energy;
        total_energy+=energy;
    }
    genx = genx/total_energy;
    geny = geny/total_energy;
    genz = genz/total_energy;


    auto oecheader = new JM::OECHeader();
    auto oecevent = new JM::OECEvent();

    oecevent->setEnergy(total_energy);
    oecevent->setTime(curtime);
    oecevent->setVertexX(genx);
    oecevent->setVertexY(geny);
    oecevent->setVertexZ(genz);

    oecevent->addTag(int(sample_idx));
    oecevent->setMuID(int(ibr));

    oecheader->setEvent(oecevent);

    // new Event Navigator

    auto anew_evtnav = new JM::EvtNavigator();
    anew_evtnav->setTimeStamp(curtime);
    anew_evtnav->addHeader("/Event/OEC", oecheader);
    m_buf->adopt(anew_evtnav, "/Event");

    return true;
}

bool MixingAlg::finalize() {

    return true;
}

MixingAlg::BranchStream::BranchStream(const std::string& fn)
    : stream(nullptr) {

    std::vector<std::string> pathList;
    pathList.push_back(fn);
    stream = new NavInputStream(pathList);

    bool okay = stream->initialize();
    if (!okay) {
        std::cerr << "Failed to initialize NavInputStream"<< std::endl;
    }
    okay = stream->first(true);
    if (!okay) {
        std::cerr << "Failed to get tag stream"<< std::endl;
    }

}

bool MixingAlg::BranchStream::next() {
    stream->next();
    auto cur_entry = stream->getEntry();
    auto total_entry = stream->getEntries();

    // reuse the data
    if(cur_entry>=total_entry){
        stream->first();
    }
    
    return true;
}

JM::EvtNavigator* MixingAlg::BranchStream::get() {
    return dynamic_cast<JM::EvtNavigator*>(stream->get());
}
