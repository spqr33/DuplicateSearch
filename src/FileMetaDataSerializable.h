/* 
 * File:   FileMetaDataSerializable.h
 * Author: s
 *
 * Created on June 7, 2015, 9:08 PM
 */

#ifndef FILEMETADATASERIALIZABLE_H
#define	FILEMETADATASERIALIZABLE_H

#include "FileMetaData.h"
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>
//#include <boost/serialization/>

namespace LobKo {

    class FileMetaDataSerializable : public FileMetaData {
        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive & ar, const unsigned int /* file_version */) {
            ar & BOOST_SERIALIZATION_NVP(getFullName());
            ar & BOOST_SERIALIZATION_NVP(getSize());
           
            //ar & BOOST_SERIALIZATION_NVP(getHash());
            ar & BOOST_SERIALIZATION_NVP(getFsID());
        }

    public:
        FileMetaDataSerializable(const string& fullName, const uint64_t size, const string& fsID);
        virtual ~FileMetaDataSerializable();
        
    };
        
};
#endif	/* FILEMETADATASERIALIZABLE_H */

