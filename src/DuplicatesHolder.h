#ifndef DUPLICATESHOLDER_H
#define	DUPLICATESHOLDER_H

#include <map>
#include <list>
#include <string>
//#include <tr1/memory>
#include <memory>
#include "FileMetaData.h"
#include "SameSizeFileHolder.h"

using std::list;
using std::string;
using std::map;
//using std::tr1::shared_ptr;
using std::shared_ptr;


namespace LobKo {

    class SameSizeFileHolder;

    class DuplicatesHolder {
    public:
        DuplicatesHolder();
        ~DuplicatesHolder();

        void addPair(const string&, shared_ptr<FileMetaData> spFileMeta);
        const map<string, list<shared_ptr<FileMetaData> > >& getHolder() const;

        void deleteNodeWithOutDupliactes();
    private:
        DuplicatesHolder(const DuplicatesHolder& orig);
        const DuplicatesHolder& operator=(const DuplicatesHolder& rhs);

        map<string, list<shared_ptr<FileMetaData> > > mapDupHolder_;
    };

    void PrintDuplicatesHolder(const DuplicatesHolder& dh);
}

#endif	/* DUPLICATESHOLDER_H */
