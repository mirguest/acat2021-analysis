#include "EventIndex/EventIndex.hh"
#include <iostream>

int main() {
    std::string fn = "dummyindex.txt";
    std::string outfn = "out-" + fn;
    AEIPlainReader reader;
    AEIPlainWriter writer;
    bool st = reader.open(fn);
    if (!st) {
        std::cerr << "Failed to open " << fn << std::endl;
        return -1;
    }

    st = writer.open(outfn);
    if (!st) {
        std::cerr << "Failed to open " << outfn << std::endl;
        return -1;
    }


    while (reader.next()) {
        AEI idx = reader.get();
        std::cout << idx.getFileId() << " "
                  << idx.getEntryId() << " "
                  << idx.energy << " "
                  << std::endl;
        writer.put(idx);
    }

    writer.close();
    reader.close();
}
