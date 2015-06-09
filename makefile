#Configurations
ALLCONFS=Debug Release 
DEFAULTCONF=Debug
CONF=${DEFAULTCONF}

#Include project Makefile
#include <- include additional makefiles if necessary 

#Environment
MKDIR=mkdir
CC=gcc
CCC=g++
CXX=g++

#Compiler Flags
CCFLAGS=-std=c++0x
CXXFLAGS=-std=c++0x

# Link Libraries
LDLIBSOPTIONS=-Wl,-Bstatic -lboost_program_options -lboost_serialization -Wl,-Bdynamic -lcrypto

#Macros
ARCH=Linux-x86
DESTDIR=dst
BUILDDIR=bld

#Directory for Object files
OBJECTDIR=${BUILDDIR}/${CONF}/${ARCH}

#Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/DirClass.o \
	${OBJECTDIR}/src/DublicatesHolder.o \
	${OBJECTDIR}/src/ErrorHolder.o \
	${OBJECTDIR}/src/FileMetaData.o \
	${OBJECTDIR}/src/FileSystemTraverser.o \
	${OBJECTDIR}/src/MD5Hash.o \
	${OBJECTDIR}/src/MetaDataFilesHolder.o \
	${OBJECTDIR}/src/SameSizeFileHolder.o \
	${OBJECTDIR}/src/main.o
