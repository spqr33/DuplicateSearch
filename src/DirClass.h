#ifndef DIRCLASS_H
#define	DIRCLASS_H

#include <sys/types.h>
#include <dirent.h>

namespace LobKo {

    class DirClass {
    public:
        explicit DirClass(DIR* dir);
        virtual ~DirClass();

        DIR* getDir() const {
            return dir_;
        };

    private:
        DirClass(const DirClass& orig);
        const DirClass& operator=(const DirClass& rhs);

        DIR* dir_;
    };
}

#endif	/* DIRCLASS_H */

