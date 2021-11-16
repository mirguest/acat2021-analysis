#ifndef OECHEADER_H
#define OECHEADER_H

#include "Event/HeaderObject.h"
#include "EDMUtil/SmartRef.h"
#include "OECEvent.h"

using namespace std;

namespace JM{
    class OECHeader:public HeaderObject{
        public:
            OECHeader();
            ~OECHeader();

            uint32_t l1id() { return m_l1id; }
            void setL1id(uint32_t l1id) { m_l1id = l1id; }

            //virtual function
            EventObject *event(const string &value);
            void setEventEntry(const string &eventName, Long64_t &value);
            
            void setEvent(OECEvent* value){m_event=value;}


        private:
            uint32_t     m_l1id;
            JM::SmartRef m_event;

        public:
            ClassDef(OECHeader,2)
    };
}

#endif
