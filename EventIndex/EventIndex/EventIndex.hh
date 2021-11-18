#ifndef EventIndex_hh
#define EventIndex_hh

#include "EventIndex/EventIndexBase.hh"
#include "EventIndex/EventIndexReader.hh"
#include "EventIndex/EventIndexData.hh"

typedef EventIndexWrapper<EventIndexDataV0> AEIv0;
typedef EventIndexReader<EventIndexDataV0PlainInputStreamer> AEIv0PlainReader;

typedef AEIv0 AEI;
typedef AEIv0PlainReader AEIPlainReader;


#endif
