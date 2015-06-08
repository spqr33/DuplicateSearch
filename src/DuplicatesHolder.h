#ifndef DUPLICATESHOLDER_H
#define	DUPLICATESHOLDER_H

#include <map>
#include <list>
#include <string>
#include <memory>
#include "FileMetaData.h"
#include "SameSizeFileHolder.h"

#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/shared_ptr.hpp>

using std::list;
using std::string;
using std::map;
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

    private:
        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive & ar, const unsigned int /* file_version */) {
            //BOOST_SERIALIZATION_ASSUME_ABSTRACT(AbstractHash);
            ar & BOOST_SERIALIZATION_NVP(mapDupHolder_);
        };

    };

    void PrintDuplicatesHolder(const DuplicatesHolder& dh);
}

#endif	/* DUPLICATESHOLDER_H */
