#############################################################################
# Makefile for building: lr-facetags
# Generated by qmake (2.01a) (Qt 4.8.1) on: Thu Jul 17 08:51:01 2014
# Project:  lr-facetags.pro
# Template: app
# Command: /usr/bin/qmake-qt4 -o Makefile lr-facetags.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_WEBKIT -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -I. -I.
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/i386-linux-gnu -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = Detection.cpp \
		FaceObject.cpp \
		Main.cpp \
		MainUI.cpp \
		readWriteObjectFile.cpp \
		RecognitionOpenCV.cpp \
		Tests/readWriteObjectFileTest.cpp \
		benchmark.cpp moc_MainUI.cpp
OBJECTS       = Detection.o \
		FaceObject.o \
		Main.o \
		MainUI.o \
		readWriteObjectFile.o \
		RecognitionOpenCV.o \
		readWriteObjectFileTest.o \
		benchmark.o \
		moc_MainUI.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		lr-facetags.pro
QMAKE_TARGET  = lr-facetags
DESTDIR       = 
TARGET        = lr-facetags

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_mainwindow.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS) `pkg-config --cflags --libs opencv`

Makefile: lr-facetags.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/i386-linux-gnu/libQtGui.prl \
		/usr/lib/i386-linux-gnu/libQtCore.prl
	$(QMAKE) -o Makefile lr-facetags.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/i386-linux-gnu/libQtGui.prl:
/usr/lib/i386-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile lr-facetags.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/lr-facetags1.0.0 || $(MKDIR) .tmp/lr-facetags1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/lr-facetags1.0.0/ && $(COPY_FILE) --parents Detection.h FaceObject.h MainUI.h readWriteObjectFile.h RecognitionOpenCV.h benchmark.h .tmp/lr-facetags1.0.0/ && $(COPY_FILE) --parents Detection.cpp FaceObject.cpp Main.cpp MainUI.cpp readWriteObjectFile.cpp RecognitionOpenCV.cpp Tests/readWriteObjectFileTest.cpp benchmark.cpp .tmp/lr-facetags1.0.0/ && $(COPY_FILE) --parents mainwindow.ui .tmp/lr-facetags1.0.0/ && (cd `dirname .tmp/lr-facetags1.0.0` && $(TAR) lr-facetags1.0.0.tar lr-facetags1.0.0 && $(COMPRESS) lr-facetags1.0.0.tar) && $(MOVE) `dirname .tmp/lr-facetags1.0.0`/lr-facetags1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/lr-facetags1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_MainUI.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_MainUI.cpp
moc_MainUI.cpp: MainUI.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) MainUI.h -o moc_MainUI.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mainwindow.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainwindow.h
ui_mainwindow.h: mainwindow.ui
	/usr/bin/uic-qt4 mainwindow.ui -o ui_mainwindow.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

Detection.o: Detection.cpp FaceObject.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Detection.o Detection.cpp

FaceObject.o: FaceObject.cpp FaceObject.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o FaceObject.o FaceObject.cpp

Main.o: Main.cpp MainUI.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Main.o Main.cpp

MainUI.o: MainUI.cpp MainUI.h \
		ui_mainwindow.h \
		Detection.h \
		FaceObject.h \
		RecognitionOpenCV.h \
		readWriteObjectFile.h \
		benchmark.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o MainUI.o MainUI.cpp

readWriteObjectFile.o: readWriteObjectFile.cpp readWriteObjectFile.h \
		FaceObject.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o readWriteObjectFile.o readWriteObjectFile.cpp

RecognitionOpenCV.o: RecognitionOpenCV.cpp FaceObject.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o RecognitionOpenCV.o RecognitionOpenCV.cpp

readWriteObjectFileTest.o: Tests/readWriteObjectFileTest.cpp readWriteObjectFile.h \
		FaceObject.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o readWriteObjectFileTest.o Tests/readWriteObjectFileTest.cpp

benchmark.o: benchmark.cpp benchmark.h \
		readWriteObjectFile.h \
		FaceObject.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o benchmark.o benchmark.cpp

moc_MainUI.o: moc_MainUI.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_MainUI.o moc_MainUI.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

