#include "DirClass.h"

LobKo::DirClass::DirClass(DIR* dir) :
dir_(dir) {
}

LobKo::DirClass::~DirClass() {
    closedir(dir_);
}

