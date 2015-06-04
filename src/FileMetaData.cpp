#include "FileMetaData.h"

LobKo::FileMetaData::FileMetaData(const string& fullName, const uint64_t size, const string& fsID) :
fullName_(fullName), size_(size), fsID_(fsID) {
;
}

LobKo::FileMetaData::~FileMetaData() {
;
}

const shared_ptr<LobKo::AbstractHash> LobKo::FileMetaData::getHash() const {
    return this->spHash_;
}

void LobKo::FileMetaData::setHash(shared_ptr<LobKo::AbstractHash> spHash) {
    spHash_ = spHash;
}