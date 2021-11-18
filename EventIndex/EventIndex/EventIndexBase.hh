#ifndef EventIndexBase_hh
#define EventIndexBase_hh

#include <cstdint>

/* 
 * Note about the design:
 *
 * Type T should implement the real data, including fileId, entryId and so on. 
 * In this structure, the T don't need to be derived from EventIndexBase.
 *
 * As type T is very simple, it is easy to use different techniques to save/load the data.
 *
 * The EventIndexBase/EventIndexWrapper is used by the framework, so it don't need to know 
 * the real implmentation.
 *
 */

class EventIndexBase {
public:
    virtual const uint64_t& getFileId() const = 0;
    virtual const uint64_t& getEntryId() const = 0;
};

template<typename T>
class EventIndexWrapper: public EventIndexBase, public T {
public:
    typedef EventIndexWrapper<T> self_type;
    typedef T data_type;

    virtual const uint64_t& getFileId() const {
        return data_type::fileId;
    }
    virtual const uint64_t& getEntryId() const {
        return data_type::entryId;
    }

};

#endif

