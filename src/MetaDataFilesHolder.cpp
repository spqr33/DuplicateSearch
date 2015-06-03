#include "MetaDataFilesHolder.h"
#include <iostream>
#include <algorithm>

LobKo::MetaDataFilesHolder::MetaDataFilesHolder(const string& fsID) :
isSorted_(false), fsID_(fsID) {
    files_.reserve(128);
}

LobKo::MetaDataFilesHolder::~MetaDataFilesHolder() {
    //std::cout << "There are " << files_.size() << " elements." << std::endl;
}

void LobKo::MetaDataFilesHolder::sort(CompareBySize comp) {
    if ( isSorted_ == false ) {
        std::sort(files_.begin(), files_.end(), comp);
        isSorted_ = true;
    }
};

shared_ptr<LobKo::SameSizeFileHolder> LobKo::MetaDataFilesHolder::getSameSizes() {
    shared_ptr<SameSizeFileHolder> spSameSizeFH(new SameSizeFileHolder());

    sort(CompareBySize());

    if ( !files_.empty() ) {
        typedef vector<shared_ptr<FileMetaData> >::const_iterator Iter;

        Iter iter1 = files_.begin();
        Iter iter2 = iter1;

        for ( uint64_t counter = 0; iter2 != files_.end(); counter = 0 ) {
            while ((iter2 != files_.end())) {
                if ( (*iter2)->getSize() == (*iter1)->getSize() ) {
                    ++iter2;
                    ++counter;
                } else {
                    break;
                }
            }
            if ( counter > 1 ) {
                //for ( uint64_t size = (*iter1)->getSize(); (iter1 != iter2) && (iter1 != files_.end()); ++iter1 ) {
                for ( uint64_t size = (*iter1)->getSize(); counter > 0; ++iter1, --counter ) {
                    spSameSizeFH->addPair(size, *iter1);
                }
            }
            iter1 = iter2;
        }
    }

    return spSameSizeFH;
}

LobKo::MetaDataFilesHolder::MergeRes LobKo::MetaDataFilesHolder::merge(shared_ptr<MetaDataFilesHolder> joinedHolder) {
    if ( &(*joinedHolder) == this ) { //adding itself
        return MergeRes::SELF_ASSING;
        //} else if ( this->fsID_ == joinedHolder->getFsId() ) {
        //    return MergeRes::EQUAL_FS_ID;
    } else {
        if ( !joinedHolder->getData().empty() ) {
            isSorted_ = false;
            files_.reserve(files_.size() + joinedHolder->getData().size());

            files_.insert(files_.end(), joinedHolder->getData().begin(), joinedHolder->getData().end());
        }
    }
    return MergeRes::OK;
}

void LobKo::PrintMetaDataFilesHolder(const MetaDataFilesHolder& mdfh) {
    std::cout << "PrintMetaDataFilesHolder()" << std::endl;
    std::cout << "Holder Size:" << mdfh.getData().size() << std::endl;

    vector <shared_ptr<FileMetaData> >::const_iterator iter = mdfh.getData().begin();

    for (; iter != mdfh.getData().end(); ++iter ) {
        std::cout << "Size: " << (*iter)->getSize() << " Name:" << (*iter)->getFullName() << std::endl;
    }
}