#include "FileMetaData.h"
#include <iostream>

LobKo::FileMetaData::FileMetaData(const string& fullName, const uint64_t size, const string& fsID) :
fullName_(fullName), size_(size), fsID_(fsID) {
    //std::cout << "FileName: " << fullName_ << " Size: " << size_ << std::endl;
}

LobKo::FileMetaData::~FileMetaData() {
    //std::cout << "FileName: " << fullName_ << " was demolished"  << std::endl;
}

const shared_ptr<LobKo::AbstractHash> LobKo::FileMetaData::getHash() const {
    return this->spHash_;
}

void LobKo::FileMetaData::setHash(shared_ptr<LobKo::AbstractHash> hash) {
    spHash_ = hash;
}