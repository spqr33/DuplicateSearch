#ifndef MD5HASH_H
#define	MD5HASH_H

#include <cstdint>
#include <memory>
#include "AbstractHash.h"

#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>

using std::shared_ptr;
using std::string;
using std::uint32_t;

namespace LobKo {

    class MD5Hash : public AbstractHash {
    public:
        MD5Hash();
        virtual ~MD5Hash();

        virtual bool fileHashCalculate(shared_ptr<FileMetaData> spFileMetaData);

        //TODO we Have to return string& instead of string

        virtual const string getDigest() const {
            return digest_;
        };
        virtual const string& getHashName() const;
    private:
        string digest_;

        // For future, I am going to replace OpenSSL implementation of MD5 
        static const string hashName_;
        static const uint32_t K_[64];
        static const uint32_t s_[64];
        static const uint32_t blockSize_ = 512;
        //std::uint32_t a_;
        //std::uint32_t b_;
        //std::uint32_t c_;
        //std::uint32_t d_;
        static const uint32_t A_ = 0x67452301;
        static const uint32_t B_ = 0xefcdab89;
        static const uint32_t C_ = 0x98badcfe;
        static const uint32_t D_ = 0x10325476;
        //void* readBuff_;
    private:
        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive & ar, const unsigned int /* file_version */) {
            ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(AbstractHash);
            ar & BOOST_SERIALIZATION_NVP(digest_);
        }
    };
}
#endif	/* MD5HASH_H */

