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
#include <boost/serialization/shared_ptr.hpp>
#include "MD5Hash.h"

///

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
//#include "FileMetaDataSerializable.h"
#include <boost/serialization/shared_ptr.hpp>
/////


namespace LobKo {

    class AbstractHash;
    class MD5Hash;

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
            BOOST_SERIALIZATION_ASSUME_ABSTRACT(AbstractHash);
            ar & BOOST_SERIALIZATION_NVP(fullName_);
            ar & BOOST_SERIALIZATION_NVP(size_);
            ar.register_type(static_cast<MD5Hash*> (NULL));
            //ar.register_type(static_cast<AbstractHash*> (NULL));
            
            //ar.register_ty
            //ar.re
            ar & BOOST_SERIALIZATION_NVP(spHash_);
            ar & BOOST_SERIALIZATION_NVP(fsID_);
        }
    };
}

#endif	/* FILEMETADATA_H */

