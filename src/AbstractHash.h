#ifndef ABSTRACTHASH_H
#define	ABSTRACTHASH_H

#include <string>
//#include <tr1/memory>
#include <memory>
#include "FileMetaData.h"

//using std::tr1::shared_ptr;
using std::shared_ptr;
using std::string;

namespace LobKo {

    class FileMetaData;

    class AbstractHash {
    public:
        enum Algo {
            MD5
        };

        virtual ~AbstractHash() {
        };

        virtual bool fileHashCalculate(shared_ptr<FileMetaData> spFileMetaData) = 0;

        virtual const string getDigest() const = 0;
        virtual const string& getHashName() const = 0;
    };
}

#endif	/* ABSTRACTHASH_H */

