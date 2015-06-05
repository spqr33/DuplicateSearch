#include "MD5Hash.h"
#include <openssl/evp.h>
#include <cassert>
#include <sys/types.h>
#include <fcntl.h>
#include <cstdio>

const std::string LobKo::MD5Hash::hashName_("md5");
const static std::uint32_t K_[64] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

const static std::uint32_t s_[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
    5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

LobKo::MD5Hash::MD5Hash() //:
//a_(A_),
//b_(B_),
//c_(C_),
//d_(D_) 
{
    digest_.reserve(16);
}

LobKo::MD5Hash::~MD5Hash() {
    ;
}

const std::string& LobKo::MD5Hash::getHashName() const {
    return hashName_;
}

bool LobKo::MD5Hash::fileHashCalculate(shared_ptr<LobKo::FileMetaData> spFileMetaData) {
    assert(spFileMetaData.get() && "LobKo::MD5Hash::fileHashCalculate, Pointer is NULL");
    //TODO control memory Leak, think about RAII
    
    using std::uint64_t;
    uint64_t blocksQuantity = spFileMetaData->getSize() / blockSize_;

    unsigned char mdValue[EVP_MAX_MD_SIZE]; // Hash will be here
    unsigned int mdLen; // Hash length

    OpenSSL_add_all_digests();
    
    const EVP_MD *md = EVP_get_digestbyname(getHashName().c_str());
        if ( md == NULL ) {

        EVP_cleanup();
        return false;
    }

    EVP_MD_CTX *mdctx = EVP_MD_CTX_create();
    
    EVP_DigestInit_ex(mdctx, md, NULL);

    int32_t fileDescriptor = open(spFileMetaData->getFullName().c_str(), O_RDONLY);
    if ( fileDescriptor <= 0 ) {

        EVP_MD_CTX_destroy(mdctx);
        EVP_cleanup();
        return false;
    }

    shared_ptr<unsigned char> readBuff(new unsigned char[blockSize_]);
    int readLength;
    for ( uint64_t i = 0; i < blocksQuantity; ++i ) {
        readLength = read(fileDescriptor, &(*readBuff), blockSize_);
        if ( readLength != blockSize_ ) {

            close(fileDescriptor);
            EVP_MD_CTX_destroy(mdctx);
            EVP_cleanup();
            return false;
        }
        EVP_DigestUpdate(mdctx, &(*readBuff), readLength);
    };

    if ( spFileMetaData->getSize() != blockSize_ * blocksQuantity ) {
        uint32_t readLastBypes = spFileMetaData->getSize() % blockSize_;
        readLength = read(fileDescriptor, &(*readBuff), readLastBypes);
        if ( readLength != readLastBypes ) {

            close(fileDescriptor);
            EVP_cleanup();
            EVP_MD_CTX_destroy(mdctx);
            return false;
        }
        EVP_DigestUpdate(mdctx, readBuff.get(), readLength);
    }
    EVP_DigestFinal_ex(mdctx, mdValue, &mdLen);

    char str[3] = {0};
    for ( int i = 0; i < mdLen; i++ ) {
        snprintf(str, 3, "%02x", mdValue[i]);
        str[2] ='\0'; //For reliability
        digest_.append(str);
    }

    EVP_MD_CTX_destroy(mdctx);
    close(fileDescriptor);
    EVP_cleanup(); // Cleans after OpenSSL_add_all_digests() OpenSSL_add_all_algorithms() OpenSSL_add_all_ciphers()

    return true;
}