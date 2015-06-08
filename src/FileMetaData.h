#ifndef FILEMETADATA_H
#define	FILEMETADATA_H

#include <string>

#include <memory>
#include <cstdint>
#include "AbstractHash.h"
#include "MD5Hash.h"

#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/string.hpp>

using std::string;
using std::shared_ptr;
using std::uint64_t;

namespace LobKo {

    class AbstractHash;
    class MD5Hash;

    class FileMetaData {
        //friend class FileMetaDataSerializable;
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
        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive & ar, const unsigned int /* file_version */) {
            BOOST_SERIALIZATION_ASSUME_ABSTRACT(AbstractHash);
            ar & BOOST_SERIALIZATION_NVP(fullName_);
            ar & BOOST_SERIALIZATION_NVP(size_);

            ar.register_type(static_cast<MD5Hash*> (NULL));
            ar & BOOST_SERIALIZATION_NVP(spHash_);
            ar & BOOST_SERIALIZATION_NVP(fsID_);
        }
    };
}

#endif	/* FILEMETADATA_H */

