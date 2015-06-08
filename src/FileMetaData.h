#ifndef FILEMETADATA_H
#define	FILEMETADATA_H

#include <string>
//#include <tr1/memory>
#include <memory>
#include <cstdint>
#include "AbstractHash.h"

using std::string;
//using std::tr1::shared_ptr;
using std::shared_ptr;
using std::uint64_t;

#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>



namespace LobKo {

    class AbstractHash;

    class FileMetaData {
        friend class boost::serialization::access;
        friend class FileMetaDataSerializable;
    public:
        FileMetaData(const string& fullName, const uint64_t size, const string& fsID);
        virtual ~FileMetaData();

        //        uint64_t getSize() {
        //            return size_;
        //        };

        const uint64_t& getSize() const {
            return size_;
        };

        const string& getFullName() const {
            return fullName_;
        };

        const string& getFsID() const {
            return fsID_;
        };

        const shared_ptr<AbstractHash> getHash() const;
        void setHash(shared_ptr<AbstractHash> spHash);

    private:
        string fullName_;
        uint64_t size_;
        shared_ptr<AbstractHash> spHash_;
        string fsID_;

    private:

        template<class Archive>
        void serialize(Archive & ar, const unsigned int /* file_version */) {
            ar & BOOST_SERIALIZATION_NVP(fullName_);
            ar & BOOST_SERIALIZATION_NVP(size_);

            //ar & BOOST_SERIALIZATION_NVP(getHash());
            ar & BOOST_SERIALIZATION_NVP(fsID_);
        }
    };
}

#endif	/* FILEMETADATA_H */

