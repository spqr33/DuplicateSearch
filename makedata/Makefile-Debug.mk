#Debug configuration of duplicatesearch
#Program Name
PROGNAME=duplicatesearch

#Configuration
CONF=Debug

#Macros
ARCH=Linux-x86
DESTDIR=dst
BUILDDIR=bld

#Environment
MKDIR=mkdir
RM=rm
CC=gcc
CCC=g++
CXX=g++

#Compiler Flags
CCFLAGS=-g -std=c++0x
CXXFLAGS=-g -std=c++0x

#Link Libraries
LDLIBSOPTIONS=-Wl,-Bstatic -lboost_program_options -lboost_serialization -Wl,-Bdynamic -lcrypto

#Directory for Object files - OBJECTDIR
#Object Files - OBJECTFILES
#Vars will load from makedata/Makefile-Objectives.mk
include makedata/Makefile-Objectives.mk

JUSTDOIT=.yesJustDoIt

build:	${JUSTDOIT}
	@echo "**************************Build started**************************";
	${MAKE}  -f makedata/Makefile-${CONF}.mk ${DESTDIR}/${CONF}/${ARCH}/${PROGNAME}

${DESTDIR}/${CONF}/${ARCH}/${PROGNAME}: ${OBJECTFILES}
	${MKDIR} -p ${DESTDIR}/${CONF}/${ARCH}
#	linker      	dest			  duplicatesearch
	${LINK.cc} -o ${DESTDIR}/${CONF}/${ARCH}/${PROGNAME} ${OBJECTFILES} ${LDLIBSOPTIONS}
	@echo "**************************Build finished*************************";

${OBJECTDIR}/src/DirClass.o: src/DirClass.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@if [ -f $@.d ];\
	then \
	    ${RM} $@.d ;\
	fi
	$(COMPILE.cc) -g -std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/DirClass.o src/DirClass.cpp
#If you want make to simply ignore a makefile which does not exist or cannot be remade, with no error message, use the -include directive instead of include, like this: 
-include ${OBJECTDIR}/src/DirClass.o.d

${OBJECTDIR}/src/DublicatesHolder.o: src/DublicatesHolder.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@if [ -f $@.d ];\
	then \
	    ${RM} $@.d ;\
	fi
	$(COMPILE.cc) -g -std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/DublicatesHolder.o src/DublicatesHolder.cpp
-include ${OBJECTDIR}/src/DublicatesHolder.o.d

${OBJECTDIR}/src/ErrorHolder.o: src/ErrorHolder.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@if [ -f $@.d ];\
	then \
	    ${RM} $@.d ;\
	fi
	$(COMPILE.cc) -g -std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ErrorHolder.o src/ErrorHolder.cpp
-include ${OBJECTDIR}/src/ErrorHolder.o.d

${OBJECTDIR}/src/FileMetaData.o: src/FileMetaData.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@if [ -f $@.d ];\
	then \
	    ${RM} $@.d ;\
	fi
	$(COMPILE.cc) -g -std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/FileMetaData.o src/FileMetaData.cpp
-include ${OBJECTDIR}/src/FileMetaData.o.d

${OBJECTDIR}/src/FileSystemTraverser.o: src/FileSystemTraverser.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@if [ -f $@.d ];\
	then \
	    ${RM} $@.d ;\
	fi
	$(COMPILE.cc) -g -std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/FileSystemTraverser.o src/FileSystemTraverser.cpp
-include ${OBJECTDIR}/src/FileSystemTraverser.o.d

${OBJECTDIR}/src/MD5Hash.o: src/MD5Hash.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@if [ -f $@.d ];\
	then \
	    ${RM} $@.d ;\
	fi
	$(COMPILE.cc) -g -std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/MD5Hash.o src/MD5Hash.cpp
-include ${OBJECTDIR}/src/MD5Hash.o.d

${OBJECTDIR}/src/MetaDataFilesHolder.o: src/MetaDataFilesHolder.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@if [ -f $@.d ];\
	then \
	    ${RM} $@.d ;\
	fi
	$(COMPILE.cc) -g -std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/MetaDataFilesHolder.o src/MetaDataFilesHolder.cpp
-include ${OBJECTDIR}/src/MetaDataFilesHolder.o.d

${OBJECTDIR}/src/SameSizeFileHolder.o: src/SameSizeFileHolder.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@if [ -f $@.d ];\
	then \
	    ${RM} $@.d ;\
	fi
	$(COMPILE.cc) -g -std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/SameSizeFileHolder.o src/SameSizeFileHolder.cpp
-include ${OBJECTDIR}/src/SameSizeFileHolder.o.d

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@if [ -f $@.d ];\
	then \
	    ${RM} $@.d ;\
	fi
	$(COMPILE.cc) -g -std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp
-include ${OBJECTDIR}/src/main.o.d
	
.yesJustDoIt:
	