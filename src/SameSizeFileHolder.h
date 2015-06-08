#ifndef SAMESIZEFILEHOLDER_H
#define	SAMESIZEFILEHOLDER_H

#include <map>
#include <list>
#include <memory>
#include <cstdint>
#include "FileMetaData.h"
#include "DuplicatesHolder.h"

using std::map;
using std::list;
using std::shared_ptr;
using std::uint64_t;

namespace LobKo {

    class DuplicatesHolder;

    class SameSizeFileHolder {
    public:
        SameSizeFileHolder();
        ~SameSizeFileHolder();

        void addPair(uint64_t, shared_ptr<FileMetaData> spFileMeta);
        const map<uint64_t, list<shared_ptr<FileMetaData> > >& getHolder() const;
        shared_ptr<DuplicatesHolder> getDuplicates(AbstractHash::Algo algoType);
    private:
        SameSizeFileHolder(const SameSizeFileHolder& orig);
        const SameSizeFileHolder& operator=(const SameSizeFileHolder& rhs);

        map<uint64_t, list<shared_ptr<FileMetaData> > > sameSizeHolder_;
    };

    void PrintSameSizeFileHolder(const SameSizeFileHolder&);
}

#endif	/* SAMESIZEFILEHOLDER_H */

