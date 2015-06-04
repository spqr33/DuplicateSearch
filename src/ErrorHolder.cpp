#include "ErrorHolder.h"
#include <iostream>
#include <assert.h>

LobKo::ErrorsHolder::ErrorsHolder() {
    ;
}

LobKo::ErrorsHolder::~ErrorsHolder() {
}

void LobKo::ErrorsHolder::addErrorPath(const string& errorPath) {
    errorPathList_.push_front(errorPath);
}

const list < string >& LobKo::ErrorsHolder::getHolder() const {
    return errorPathList_;
}

void LobKo::PrintErrorHolder(const ErrorsHolder * const eh) {
    using std::cout;
    using std::endl;

    assert((eh != NULL) && "Errors Holder is NULL");

    list<string>::const_iterator iter = eh->getHolder().begin();
    list<string>::const_iterator end = eh->getHolder().end();

    cout << "Holder Size:" << eh->getHolder().size() << endl;

    for (; iter != end; ++iter ) {
        cout << "Error occured at " << *iter << std::endl;
    }
}