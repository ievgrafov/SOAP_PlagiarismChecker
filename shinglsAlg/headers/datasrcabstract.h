#ifndef DATASRCABSTRACT_H
#define DATASRCABSTRACT_H

#include "./DocHeader.h"
#include "constants.h"
#include "../include/threads.h"

namespace DePlaguarism{

    class DataSrcAbstract
    {
    public:
        std::string * error;
        virtual std::vector<unsigned int> * getIdsByHashes(const unsigned int * hashes, unsigned int count) = 0;
        virtual void save(const unsigned int * hashes, unsigned int count, DocHeader header, t__text * txt) = 0;
        virtual void getDocument(unsigned int docNumber, t__text **trgt, soap * parent) = 0;
        virtual ~DataSrcAbstract() {};
    };

}

#endif // DATASRCABSTRACT_H