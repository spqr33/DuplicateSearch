#ifndef ABSTRACTHASH_H
#define	ABSTRACTHASH_H

#include <string>
//#include <tr1/memory>
#include <memory>
#include "FileMetaData.h"

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

//using std::tr1::shared_ptr;
using std::shared_ptr;
using std::string;

namespace LobKo {

    class FileMetaData;

    class AbstractHash {
    public:

        enum Algo {
            MD5
        };
        
        AbstractHash() {};
        virtual ~AbstractHash() {
        };

        virtual bool fileHashCalculate(shared_ptr<FileMetaData> spFileMetaData) = 0;

        virtual const string getDigest() const = 0;
        virtual const string& getHashName() const = 0;
    private:
        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive & ar, const unsigned int /* file_version */) {
            ;
        }
    };
}

#endif	/* ABSTRACTHASH_H */

