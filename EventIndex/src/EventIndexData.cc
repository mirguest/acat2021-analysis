#include "EventIndex/EventIndexData.hh"
#include <sstream>

// STREAMER
bool EventIndexDataV0PlainInputStreamer::open(const std::string& filename) {
    m_input.open(filename);
    return m_input.good();
}

bool EventIndexDataV0PlainInputStreamer::close() {
    m_input.close();
    return true;
}

bool EventIndexDataV0PlainInputStreamer::next() {
    std::getline(m_input, m_cache_line);

    return m_input.good() and not m_input.eof();
}

EventIndexDataV0PlainInputStreamer::wrapper_type
EventIndexDataV0PlainInputStreamer::get() {
    wrapper_type tmp;
    std::stringstream ss(m_cache_line);

    ss >> tmp.fileId
       >> tmp.entryId
       >> tmp.energy
       >> tmp.vertex_x
       >> tmp.vertex_y
       >> tmp.vertex_z
       >> tmp.time;

    return tmp;
}
