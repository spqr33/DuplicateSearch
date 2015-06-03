#include "ErrorHolder.h"
#include <iostream>
#include <assert.h>

LobKo::ErrorsHolder::ErrorsHolder() {
    //errorPathList_.reserve(128);
    // errorPathList_.push_back()
}

LobKo::ErrorsHolder::ErrorsHolder(const ErrorsHolder& orig) {
}

LobKo::ErrorsHolder::~ErrorsHolder() {
}

void LobKo::ErrorsHolder::addErrorPath(string errorPath) {
    //std::string s(errorPath);
    //std::cout << "errorPath: " << s << std::endl;

    std::cout << "ERROR PATH:" << errorPath << std::endl;
    //getchar();

    errorPathList_.push_front(errorPath);

    //std::cout << "errorPath: " << s << std::endl;
}

const list < string >& LobKo::ErrorsHolder::getHolder() const {
    return errorPathList_;
}

void LobKo::PrintErrorHolder(const ErrorsHolder * const eh) {
    //using std::cout;
    //using std::endl;

    assert((eh != NULL) && "EH is NuLL");
    //ErrorHolder* ehTemp = const_cast<ErrorHolder*> (eh);
    //list<string>* lsTemp = const_cast<list<string>*> (&ehTemp->getHolder());
    list<string>::const_iterator iter = eh->getHolder().begin();
    list<string>::const_iterator end = eh->getHolder().end();


    //list<string>::iterator iter = ehTemp->errorPathList_.begin();
        //list<string>::iterator end =  ehTemp->errorPathList_.end();
    //list<string>::iterator end = lsTemp->end();

    std::cout << "Error holder size" << eh->getHolder().size() << std::endl; //" Last: " << *(--end) << std::endl;

    //for (int i = 0; iter != eh->getHolder().end(); ++iter, ++i ) {
    for ( int i = 1; iter != end; ++iter, ++i ) {

        //if ( iter != end ) { 
        std::cout << "I == " << i << "From " << eh->getHolder().size() << " Error occured:" << *iter << "!" << std::endl;
        //        } else {
        //            std:: cout << "Something ocured!" << std::endl;
        //            break;
        //        }
    }

    std::cout << "PrintErrorHolder exit" << std::endl;

    return;
}