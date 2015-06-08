#ifndef FILESYSTEMTRAVERSER_H
#define	FILESYSTEMTRAVERSER_H

#include <string>
#include <memory>
#include "MetaDataFilesHolder.h"
#include "ErrorHolder.h"

using std::string;
using std::shared_ptr;
using LobKo::MetaDataFilesHolder;

namespace LobKo {

    class FileSystemTraverser {
    public:
        FileSystemTraverser(const string& path, const string& fsID, shared_ptr<ErrorsHolder> spErrHolder_);
        ~FileSystemTraverser();

        enum Result {
            ERR = -1, NOERR
        };

        shared_ptr<MetaDataFilesHolder> traverse(Result& result);
        void setPath(const string& newPath);

        const string& getPath() const {
            return path_;
        };

        Result getLastTraverseResult() const {
            return result_;
        };

    private:
        FileSystemTraverser(const FileSystemTraverser& orig);
        const FileSystemTraverser& operator=(const FileSystemTraverser& rhs);

        void traverse2(const string& path_) const;

        mutable Result result_;
        shared_ptr<MetaDataFilesHolder> spMetaDataFilesHolder_;
        shared_ptr<ErrorsHolder> spErrHolder_;
        string path_;
        string fsID_;
    };
}

#endif	/* FILESYSTEMTRAVERSER_H */

