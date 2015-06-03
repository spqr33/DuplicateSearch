#ifndef FILEMETADATA_H
#define	FILEMETADATA_H

#include <string>
#include <tr1/memory>
#include <stdint.h>
#include "AbstractHash.h"

using std::string;
using std::tr1::shared_ptr;


namespace LobKo {

    class AbstractHash;

    class FileMetaData {
    public:
        FileMetaData(const string& fullName, const uint64_t size, const string& fsID);
        ~FileMetaData();

        uint64_t getSize() const {
            return size_;
        };

        const string& getFullName() const {
            return fullName_;
        };

        const string& getFsID() const {
            return fsID_;
        };

        const shared_ptr<AbstractHash> getHash() const;
        void setHash(shared_ptr<AbstractHash> hash);

    private:
        string fullName_;
        uint64_t size_;
        shared_ptr<AbstractHash> spHash_;
        string fsID_;
    };
}

#endif	/* FILEMETADATA_H */

