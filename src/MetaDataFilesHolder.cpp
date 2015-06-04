#include "MetaDataFilesHolder.h"
#include <iostream>
#include <algorithm>
#include <cassert>

LobKo::MetaDataFilesHolder::MetaDataFilesHolder(const string& fsID) :
isSorted_(false), fsID_(fsID) {
    files_.reserve(128);
};

LobKo::MetaDataFilesHolder::~MetaDataFilesHolder() {
    ;
};

void LobKo::MetaDataFilesHolder::sort(CompareBySize comp) {
    if ( isSorted_ == false ) {
        std::sort(files_.begin(), files_.end(), comp);
        isSorted_ = true;
    }
};

shared_ptr<LobKo::SameSizeFileHolder> LobKo::MetaDataFilesHolder::getSameSizes() {
    shared_ptr<SameSizeFileHolder> spSameSizeFileHolder(new SameSizeFileHolder());

    sort(CompareBySize());

    if ( !files_.empty() ) {
        typedef vector<shared_ptr<FileMetaData> >::const_iterator Iter;

        Iter iter1 = files_.begin();
        Iter iter2 = iter1;

        for ( uint64_t sameSizeCounter = 0; iter2 != files_.end(); sameSizeCounter = 0 ) {
            while ((iter2 != files_.end())) {
                if ( (*iter2)->getSize() == (*iter1)->getSize() ) {
                    ++iter2;
                    ++sameSizeCounter;
                } else {
                    break;
                }
            }
            if ( sameSizeCounter > 1 ) {
                for ( uint64_t size = (*iter1)->getSize(); sameSizeCounter > 0; ++iter1, --sameSizeCounter ) {
                    spSameSizeFileHolder->addPair(size, *iter1);
                }
            }
            iter1 = iter2;
        }
    }

    return spSameSizeFileHolder;
};

LobKo::MetaDataFilesHolder::MergeRes LobKo::MetaDataFilesHolder::merge(shared_ptr<MetaDataFilesHolder> spMergedHolder) {
    assert((spMergedHolder.get() != NULL) && "LobKo::MetaDataFilesHolder::merge: *joinedHolder == NULL");

    if ( getFsId() == spMergedHolder.get()->getFsId() ) {
        
        return MergeRes::EQUAL_FS_ID;
    }
    if ( &(*spMergedHolder) == this ) { //adding itself

        return MergeRes::SELF_MERGED;
    } else {
        if ( !spMergedHolder->getData().empty() ) {
            isSorted_ = false;
            files_.reserve(files_.size() + spMergedHolder->getData().size());

            files_.insert(files_.end(), spMergedHolder->getData().begin(), spMergedHolder->getData().end());
        }
    }
    return MergeRes::OK;
};

void LobKo::PrintMetaDataFilesHolder(const MetaDataFilesHolder& mdfh) {
    std::cout << "Holder Size: " << mdfh.getData().size() << std::endl;

    vector <shared_ptr<FileMetaData> >::const_iterator iter = mdfh.getData().begin();

    for (; iter != mdfh.getData().end(); ++iter ) {
        std::cout << "Size: " << (*iter)->getSize() << " Name:" << (*iter)->getFullName() << std::endl;
    }
};