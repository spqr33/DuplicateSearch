#ifndef ABSTRACTHASH_H
#define	ABSTRACTHASH_H

#include <string>
#include "FileMetaData.h"
#include <tr1/memory>

using std::tr1::shared_ptr;
using std::string;

namespace LobKo {

    class FileMetaData;

    class AbstractHash {
    public:

        enum Algo {
            MD5
        };

        AbstractHash() {
        };

        AbstractHash(const AbstractHash&) {
        };

        virtual ~AbstractHash() {
        };
        //bool fileHashCalculate( const string& filePath ) = 0;
        virtual bool fileHashCalculate(shared_ptr<FileMetaData> fileMetaData) = 0;

        //const vector<std::uint32_t>& getDigest() const = 0;
        virtual const string getDigest() const = 0;
        virtual const string& getHashName() const = 0;

    };
}

#endif	/* ABSTRACTHASH_H */

