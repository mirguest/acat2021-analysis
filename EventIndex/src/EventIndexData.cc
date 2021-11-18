#include "EventIndex/EventIndexData.hh"
#include <sstream>

// INPUT STREAMER
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

// OUTPUT STREAMER
bool EventIndexDataV0PlainOutputStreamer::open(const std::string& filename) {
    m_output.open(filename);
    return m_output.good();
}

bool EventIndexDataV0PlainOutputStreamer::close() {
    m_output.close();
    return true;
}

bool EventIndexDataV0PlainOutputStreamer::put(const EventIndexDataV0PlainOutputStreamer::wrapper_type& data) {

    m_output << data.fileId   << " "
             << data.entryId  << " "
             << data.energy   << " "
             << data.vertex_x << " "
             << data.vertex_y << " "
             << data.vertex_z << " "
             << data.time     << " "
             << std::endl;;

    return m_output.good();
}
