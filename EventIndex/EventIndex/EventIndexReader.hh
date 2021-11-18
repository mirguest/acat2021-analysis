#ifndef EventIndexReader_hh
#define EventIndexReader_hh

#include "EventIndex/EventIndexBase.hh"
#include <string>

template<typename S>
struct EventIndexReader {
    typedef S streamer_type;
    typedef typename streamer_type::data_type data_type;
    typedef typename streamer_type::wrapper_type wrapper_type;

    bool open(const std::string& filename) {
        return m_streamer.open(filename);
    }

    bool close() {
        return m_streamer.close();
    }

    bool next() {
        return m_streamer.next();
    }

    wrapper_type get() {
        return m_streamer.get();
    }

private:
    streamer_type m_streamer;
};

#endif
