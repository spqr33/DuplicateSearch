#ifndef SAMESIZEFILEHOLDER_H
#define	SAMESIZEFILEHOLDER_H

#include <map>
#include <list>
#include <tr1/memory>
#include <cstdint>
#include <stdint.h>

#include "FileMetaData.h"
#include "DuplicatesHolder.h"

using std::map;
using std::list;
using std::tr1::shared_ptr;

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

        bool calculateHashe(AbstractHash::Algo algoType);
        
        map<uint64_t, list<shared_ptr<FileMetaData> > > sameSizeHolder_;
    }; //end class SameSizeFileHolder

    void PrintSameSizeFileHolder(const SameSizeFileHolder& ssfh);
}


#endif	/* SAMESIZEFILEHOLDER_H */

