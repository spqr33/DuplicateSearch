#Program Name
PROGNAME=duplicatesearch

#Configurations
ALLCONFS=Debug Release 
DEFAULTCONF=Debug
CONF=${DEFAULTCONF}

#Hints
#make -p to see default make options

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

#Link Libraries
LDLIBSOPTIONS=-Wl,-Bstatic -lboost_program_options -lboost_serialization -Wl,-Bdynamic -lcrypto

#Macros
ARCH=Linux-x86
DESTDIR=dst
BUILDDIR=bld

#Directory for Object files - OBJECTDIR
#Object Files - OBJECTFILES
#Vars will load from makedata/Makefile-Objectives.mk
include makedata/Makefile-Objectives.mk

build:
	${MAKE}  -f makedata/Makefile-${CONF}.mk ${DESTDIR}/${CONF}/${ARCH}/${PROGNAME}

#include makedata/Makefile-${CONF}.mk