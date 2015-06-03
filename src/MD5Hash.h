#ifndef MD5HASH_H
#define	MD5HASH_H

#include <cstdint>
#include "AbstractHash.h"

namespace LobKo {

    class MD5Hash : public AbstractHash {
    public:
        MD5Hash();
        MD5Hash(const MD5Hash& orig);
        virtual ~MD5Hash();

        virtual bool fileHashCalculate(std::tr1::shared_ptr<LobKo::FileMetaData> fileMetaData);

        //const vector<std::uint32_t>& getDigest() const = 0;

        virtual const std::string getDigest() const {
            return digest_;
        };
        virtual const std::string& getHashName() const;

    private:
        std::string digest_;

        static const std::string hashName_;
        static const std::uint32_t K_[64];
        static const std::uint32_t s_[64];
        static const std::uint32_t blockSize_ = 512;
        //std::uint32_t a_;
        //std::uint32_t b_;
        //std::uint32_t c_;
        //std::uint32_t d_;
        static const std::uint32_t A_ = 0x67452301;
        static const std::uint32_t B_ = 0xefcdab89;
        static const std::uint32_t C_ = 0x98badcfe;
        static const std::uint32_t D_ = 0x10325476;
        //void* readBuff_;

    };
}
#endif	/* MD5HASH_H */

