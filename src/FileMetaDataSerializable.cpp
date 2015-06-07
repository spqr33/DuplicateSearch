/* 
 * File:   FileMetaDataSerializable.cpp
 * Author: s
 * 
 * Created on June 7, 2015, 9:08 PM
 */

#include "FileMetaDataSerializable.h"

LobKo::FileMetaDataSerializable::FileMetaDataSerializable(const string& fullName,
                const uint64_t size, const string& fsID) :
                FileMetaData(fullName, size, fsID)
{
    ;
}

LobKo::FileMetaDataSerializable::~FileMetaDataSerializable() {
    ;
}

