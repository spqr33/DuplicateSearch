#include "DuplicatesHolder.h"
#include <iostream>

LobKo::DuplicatesHolder::DuplicatesHolder() {
    ;
}

LobKo::DuplicatesHolder::~DuplicatesHolder() {
    ;
}

void LobKo::DuplicatesHolder::addPair(const string& digest, shared_ptr<FileMetaData> spFileMeta) {
    mapDupHolder_[digest].push_back(spFileMeta);
}

const map<string, std::list<shared_ptr<LobKo::FileMetaData> > >& LobKo::DuplicatesHolder::getHolder() const {
    return mapDupHolder_;
}

void LobKo::DuplicatesHolder::deleteNodeWithOutDupliactes() {
    typedef map<string, list<shared_ptr<FileMetaData> > >::iterator MapDupIter;
    MapDupIter mIter = mapDupHolder_.begin();

    for (; mIter != mapDupHolder_.end(); ) {
        if ( (*mIter).second.size() <= 1 ) { // only one value in list
            mIter = mapDupHolder_.erase(mIter);
        } else {
            ++mIter;
        }
    }
}

void LobKo::PrintDuplicatesHolder(const DuplicatesHolder& dh) {
    using std::cout;
    using std::endl;
    cout << "Holder Size:" << dh.getHolder().size() << endl;

    typedef map<string, std::list<shared_ptr<FileMetaData> > >::const_iterator MapCIter;
    MapCIter iter = dh.getHolder().begin();

    for (; iter != dh.getHolder().end(); ++iter ) {
        cout << "Hash: " << iter->first << endl;

        std::list<shared_ptr<FileMetaData> >::const_iterator lIter = iter->second.begin();

        for (; lIter != iter->second.end(); ++lIter ) {
            cout << "\t\tSize:" << (*lIter)->getSize() << " ID: " <<\
                    (*lIter)->getFsID() << " Name: " << (*lIter)->getFullName() << endl;
        }
    }
}