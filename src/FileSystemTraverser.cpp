#include <dirent.h>
#include "FileSystemTraverser.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include "DirClass.h"
#include <iostream>
#include "AbstractHash.h"
#include "MD5Hash.h"
#include <cstdio>

LobKo::FileSystemTraverser::FileSystemTraverser(const string& path, const string& fsID, shared_ptr<ErrorsHolder> errHolder) :
result_(Result::NOERR), mdfHolder_(), fsID_(fsID), errHolder_(errHolder) {
    if ( path == "/" ) {
        path_ = path;
    } else if ( path[path.size() - 1] == '/' ) {
        path_ = string(path.begin(), path.end() - 1);
    } else {
        path_ = path;
    }
}

LobKo::FileSystemTraverser::~FileSystemTraverser() {
    ;
}

void LobKo::FileSystemTraverser::setPath(const std::string& newPath) {
    path_ = newPath;
}

shared_ptr<LobKo::MetaDataFilesHolder> LobKo::FileSystemTraverser::traverse(Result& result) {
    std::string path(path_);
    result_ = Result::NOERR;

    mdfHolder_.reset(new LobKo::MetaDataFilesHolder(fsID_));

    traverse2(path);

    shared_ptr<MetaDataFilesHolder> mdfHolder(mdfHolder_);
    mdfHolder_.reset();
    errHolder_.reset();

    result = result_;
    return mdfHolder;
}

void LobKo::FileSystemTraverser::traverse2(const string& path) const {
    shared_ptr<struct stat> statbuf(new struct stat);

    if ( lstat(path.c_str(), &(*statbuf)) < 0 ) {
        result_ = Result::ERR;

        return;
    }

    if ( S_ISREG(statbuf->st_mode) ) { // regular file
        uint64_t fileSizeBytes = statbuf->st_size;
        shared_ptr<FileMetaData> spFile(new FileMetaData(path, fileSizeBytes, fsID_));
        shared_ptr<AbstractHash> hash(new MD5Hash());

        if ( hash->fileHashCalculate(spFile) == false ) {
            result_ = Result::ERR;
            errHolder_->addErrorPath(spFile->getFullName());

            return;
        };
        spFile->setHash(hash);
        mdfHolder_->add(spFile);

        return;
    }

    if ( S_ISDIR(statbuf->st_mode) ) { // Directory
        struct dirent* dir;
        DIR* ds = opendir(path.c_str());
        DirClass dirStream(ds);

        if ( dirStream.getDir() == NULL ) { //Directory unavailable
            //TODO add this dir into storage of undread files & dirs.
            result_ = Result::ERR;
            return;
        }

        while ((dir = readdir(dirStream.getDir())) != NULL) {
            if ( (strcmp(dir->d_name, ".") == 0) || (strcmp(dir->d_name, "..") == 0) ) {
                continue;
            } else {
                std::string s((path != "/") ? path : "");
                s += std::string("/");
                s += std::string(dir->d_name);
                std::cout << "Path: " << path << std::endl;

                traverse2(s);
            }
        }
    }
}

