/* 
 * File:   ErrorHolder.h
 * Author: s
 *
 * Created on May 19, 2015, 12:54 AM
 */

#ifndef ERRORHOLDER_H
#define	ERRORHOLDER_H

#include <string>
#include <list>
#include <vector>

#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>

using std::string;
using std::list;
using std::vector;

namespace LobKo {

    class ErrorsHolder {
    public:
        ErrorsHolder();
        virtual ~ErrorsHolder();

        void addErrorPath(const string& errorPath);
        const list < string >& getHolder() const;
    private:
        list< string > errorPathList_;
    private:
        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive & ar, const unsigned int /* file_version */) {
            ar & BOOST_SERIALIZATION_NVP(errorPathList_);
        };
    };

    void PrintErrorHolder(const ErrorsHolder * const eh);
};
#endif	/* ERRORHOLDER_H */

