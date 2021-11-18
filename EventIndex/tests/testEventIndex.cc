#include "EventIndex/EventIndex.hh"
#include <iostream>

int main() {
    std::string fn = "dummyindex.txt";
    AEIPlainReader reader;
    bool st = reader.open(fn);
    if (!st) {
        std::cerr << "Failed to open " << fn << std::endl;
        return -1;
    }

    while (reader.next()) {
        AEI idx = reader.get();
        std::cout << idx.getFileId() << " "
                  << idx.getEntryId() << " "
                  << idx.energy << " "
                  << std::endl;
    }
}
