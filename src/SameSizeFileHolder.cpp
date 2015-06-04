#include "SameSizeFileHolder.h"
#include <iostream>

LobKo::SameSizeFileHolder::SameSizeFileHolder() {
    ;
}

LobKo::SameSizeFileHolder::~SameSizeFileHolder() {
    ;
}

void LobKo::SameSizeFileHolder::addPair(uint64_t fileSize, shared_ptr<FileMetaData> spFileMeta) {
    sameSizeHolder_[fileSize].push_back(spFileMeta);
}

const map<uint64_t, list<shared_ptr<LobKo::FileMetaData> > >& LobKo::SameSizeFileHolder::getHolder() const {
    return sameSizeHolder_;
}

shared_ptr<LobKo::DuplicatesHolder> LobKo::SameSizeFileHolder::getDuplicates(AbstractHash::Algo algoType) {
    shared_ptr<LobKo::DuplicatesHolder> spDupHolder(new DuplicatesHolder());

    typedef map<uint64_t, list<shared_ptr<FileMetaData> > >::const_iterator MapCIter;
    MapCIter iter = this->getHolder().begin();

    for (; iter != getHolder().end(); ++iter ) {
        list<shared_ptr<FileMetaData> >::const_iterator lIter = iter->second.begin();

        for (; lIter != iter->second.end(); ++lIter ) {
            spDupHolder->addPair((*lIter)->getHash()->getDigest(), (*lIter));
         }
    }
    spDupHolder->deleteNodeWithOutDupliactes();

    return spDupHolder;
};

void LobKo::PrintSameSizeFileHolder(const SameSizeFileHolder& ssfh) {
    std::cout << "Holder Size: " << ssfh.getHolder().size() << std::endl;

    typedef map<uint64_t, list<shared_ptr<FileMetaData> > >::const_iterator MapCIter;
    MapCIter iter = ssfh.getHolder().begin();

    for (; iter != ssfh.getHolder().end(); ++iter ) {
        std::cout << "Size: " << iter->first << std::endl;

        list<shared_ptr<FileMetaData> >::const_iterator lIter = iter->second.begin();

        for (; lIter != iter->second.end(); ++lIter ) {
            std::cout << "\tName: " << (*lIter)->getFullName() << "\n\tDigest: " <<\
                    (*lIter)->getHash()->getDigest() << std::endl;
        }
    }
}