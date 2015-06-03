#include <iostream>

#include "SameSizeFileHolder.h"
#include "MD5Hash.h"
#include <algorithm>
#include <functional>

LobKo::SameSizeFileHolder::SameSizeFileHolder() {
    ;
}

LobKo::SameSizeFileHolder::~SameSizeFileHolder() {
    ;
}

void LobKo::SameSizeFileHolder::addPair(uint64_t fileSize, shared_ptr<FileMetaData> spFileMeta) {
    std::cout << "Adding to map Size:" << fileSize << " and the Path: " << spFileMeta->getFullName() << std::endl;
    sameSizeHolder_[fileSize].push_back(spFileMeta);
}

const map<uint64_t, list<shared_ptr<LobKo::FileMetaData> > >& LobKo::SameSizeFileHolder::getHolder() const {
    return sameSizeHolder_;
}

shared_ptr<LobKo::DuplicatesHolder> LobKo::SameSizeFileHolder::getDuplicates(AbstractHash::Algo algoType) {

    shared_ptr<LobKo::DuplicatesHolder> dupHolder(new DuplicatesHolder());

    typedef map<uint64_t, list<shared_ptr<FileMetaData> > >::const_iterator MapCIter;
    MapCIter iter = this->getHolder().begin();

    for (; iter != getHolder().end(); ++iter ) {
        std::cout << "Size: " << iter->first << std::endl;

        list<shared_ptr<FileMetaData> >::const_iterator lIter = iter->second.begin();

        for (; lIter != iter->second.end(); ++lIter ) {
            //MD5Hash* pMD5();

            //            shared_ptr<AbstractHash> hash(new MD5Hash());
            //            hash->fileHashCalculate(*lIter);
            //            (*lIter)->setHash(hash);
            //            dupHolder->addPair(hash->getDigest(), (*lIter));
            dupHolder->addPair((*lIter)->getHash()->getDigest(), (*lIter));
            //std::cout << "     Name: " << (*lIter)->getFullName() << std::endl;
        }
    }

    dupHolder->deleteNoDuplicateNode();
    //    typedef map<string, list<shared_ptr<FileMetaData> > >::iterator MapDupIter;
    //    MapDupIter mIter = dupHolder->mapDupHolder_.begin();
    //    MapDupIter mIterEnd = dupHolder->mapDupHolder_.end();
    //
    //    for (; mIter != mIterEnd; ) {
    //        if ( (*mIter).second.size() <= 1 ) {
    //            mIter = dupHolder->mapDupHolder_.erase(mIter);
    //        } else {
    //            ++mIter;
    //        }
    //    }

    //MapDupIter = 
    //std::remove_if(dupHolder->getHolder().begin(), dupHolder->getHolder().end(), ListHasOneNode());

    return dupHolder;
};

void LobKo::PrintSameSizeFileHolder(const SameSizeFileHolder& ssfh) {
    std::cout << "PrintSameSizeFileHolder()" << std::endl;
    std::cout << "Holder Size:" << ssfh.getHolder().size() << std::endl;

    typedef map<uint64_t, list<shared_ptr<FileMetaData> > >::const_iterator MapCIter;
    MapCIter iter = ssfh.getHolder().begin();

    for (; iter != ssfh.getHolder().end(); ++iter ) {
        std::cout << "Size: " << iter->first << std::endl;

        list<shared_ptr<FileMetaData> >::const_iterator lIter = iter->second.begin();

        for (; lIter != iter->second.end(); ++lIter ) {
            std::cout << "     Name: " << (*lIter)->getFullName() << "\n     Digest: " << (*lIter)->getHash()->getDigest() << std::endl;
        }
    }
    std::cout << "End of PrintSameSizeFileHolder()" << std::endl;
}