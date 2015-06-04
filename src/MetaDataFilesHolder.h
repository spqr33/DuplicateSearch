#ifndef METADATAFILESHOLDER_H
#define	METADATAFILESHOLDER_H

#include <list>
#include <string>
#include <vector>
#include <tr1/memory>
#include "FileMetaData.h"
#include "SameSizeFileHolder.h"

using std::tr1::shared_ptr;
using std::vector;
using std::string;

namespace LobKo {

    struct CompareBySize;
    class SameSizeFileHolder;

    class MetaDataFilesHolder {
    public:
         explicit MetaDataFilesHolder(const string& fsID);
        ~MetaDataFilesHolder();

        enum MergeRes {
            EQUAL_FS_ID = -2, SELF_MERGED, OK
        };

        inline void add(shared_ptr<FileMetaData> file);
        void sort(CompareBySize comp);
        MergeRes merge(shared_ptr<MetaDataFilesHolder> joinedHolder);

        shared_ptr<SameSizeFileHolder> getSameSizes();

        const vector<shared_ptr<FileMetaData> >& getData() const {
            return files_;
        };

        const string getFsId() const {
            return fsID_;
        };

        bool isSorted() const {
            return isSorted_;
        };

    private:
        MetaDataFilesHolder(const MetaDataFilesHolder& orig);
        const MetaDataFilesHolder& operator=(const MetaDataFilesHolder& rhs);

        vector<shared_ptr<FileMetaData> > files_;
        bool isSorted_;
        string fsID_;
    }; // end class MetaDataFilesHolder

    struct CompareBySize {
        bool operator()(const shared_ptr<LobKo::FileMetaData> left, const shared_ptr<LobKo::FileMetaData> right) {
            return left->getSize() < right->getSize();
        };
    };

    void PrintMetaDataFilesHolder(const MetaDataFilesHolder& mdfh);
}

void LobKo::MetaDataFilesHolder::add(shared_ptr<FileMetaData> file) {
    isSorted_ = false;
    files_.push_back(file);
}

#endif	/* METADATAFILESHOLDER_H */