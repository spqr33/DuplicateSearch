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
using std::string;
using std::list;
using std::vector;


namespace LobKo {

    class ErrorsHolder {
    public:
        ErrorsHolder();
        ErrorsHolder(const ErrorsHolder& orig);
        virtual ~ErrorsHolder();
        void addErrorPath(string errorPath);
        const list < string >& getHolder() const;
        private:
        list< string> errorPathList_;
    };

    void PrintErrorHolder(const ErrorsHolder * const eh);
};
#endif	/* ERRORHOLDER_H */

