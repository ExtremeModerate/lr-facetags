#############################################################################
# Makefile for building: lr-facetags
# Generated by qmake (2.01a) (Qt 4.8.6) on: Mon Sep 15 18:09:32 2014
# Project:  lr-facetags.pro
# Template: app
# Command: /usr/bin/qmake-qt4 -spec /usr/share/qt4/mkspecs/linux-g++ -o Makefile lr-facetags.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -march=x86-64 -mtune=generic -O2 -pipe -fstack-protector --param=ssp-buffer-size=4 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -march=x86-64 -mtune=generic -O2 -pipe -fstack-protector --param=ssp-buffer-size=4 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -I/usr/local/include/opencv -I. -I.
LINK          = g++
LFLAGS        = -Wl,-O1,--sort-common,--as-needed,-z,relro -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib -L/usr/local/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_flann -lopencv_nonfree -lQtGui -lQtCore -lpthread 
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

SOURCES       = benchmark.cpp \
		Detection.cpp \
		FaceObject.cpp \
		Main.cpp \
		MainUI.cpp \
		readWriteObjectFile.cpp \
		RecognitionOpenCV.cpp \
		TagTrainingSetDialog.cpp \
		plotdialog.cpp \
		qcustomplot.cpp \
		bbdialog.cpp moc_MainUI.cpp \
		moc_TagTrainingSetDialog.cpp \
		moc_plotdialog.cpp \
		moc_qcustomplot.cpp \
		moc_bbdialog.cpp
OBJECTS       = benchmark.o \
		Detection.o \
		FaceObject.o \
		Main.o \
		MainUI.o \
		readWriteObjectFile.o \
		RecognitionOpenCV.o \
		TagTrainingSetDialog.o \
		plotdialog.o \
		qcustomplot.o \
		bbdialog.o \
		moc_MainUI.o \
		moc_TagTrainingSetDialog.o \
		moc_plotdialog.o \
		moc_qcustomplot.o \
		moc_bbdialog.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
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

$(TARGET): ui_mainwindow.h ui_TagTrainingSetDialog.h ui_plotdialog.h ui_bbdialog.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: lr-facetags.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
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
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -o Makefile lr-facetags.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_phonon.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/shared.prf:
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
/usr/lib/libQtGui.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -o Makefile lr-facetags.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/lr-facetags1.0.0 || $(MKDIR) .tmp/lr-facetags1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/lr-facetags1.0.0/ && $(COPY_FILE) --parents benchmark.h Detection.h FaceObject.h MainUI.h readWriteObjectFile.h RecognitionOpenCV.h TagTrainingSetDialog.h plotdialog.h qcustomplot.h bbdialog.h .tmp/lr-facetags1.0.0/ && $(COPY_FILE) --parents benchmark.cpp Detection.cpp FaceObject.cpp Main.cpp MainUI.cpp readWriteObjectFile.cpp RecognitionOpenCV.cpp TagTrainingSetDialog.cpp plotdialog.cpp qcustomplot.cpp bbdialog.cpp .tmp/lr-facetags1.0.0/ && $(COPY_FILE) --parents mainwindow.ui TagTrainingSetDialog.ui plotdialog.ui bbdialog.ui .tmp/lr-facetags1.0.0/ && (cd `dirname .tmp/lr-facetags1.0.0` && $(TAR) lr-facetags1.0.0.tar lr-facetags1.0.0 && $(COMPRESS) lr-facetags1.0.0.tar) && $(MOVE) `dirname .tmp/lr-facetags1.0.0`/lr-facetags1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/lr-facetags1.0.0


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

compiler_moc_header_make_all: moc_MainUI.cpp moc_TagTrainingSetDialog.cpp moc_plotdialog.cpp moc_qcustomplot.cpp moc_bbdialog.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_MainUI.cpp moc_TagTrainingSetDialog.cpp moc_plotdialog.cpp moc_qcustomplot.cpp moc_bbdialog.cpp
moc_MainUI.cpp: TagTrainingSetDialog.h \
		MainUI.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) MainUI.h -o moc_MainUI.cpp

moc_TagTrainingSetDialog.cpp: TagTrainingSetDialog.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) TagTrainingSetDialog.h -o moc_TagTrainingSetDialog.cpp

moc_plotdialog.cpp: plotdialog.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) plotdialog.h -o moc_plotdialog.cpp

moc_qcustomplot.cpp: qcustomplot.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) qcustomplot.h -o moc_qcustomplot.cpp

moc_bbdialog.cpp: bbdialog.h
	/usr/lib/qt4/bin/moc $(DEFINES) $(INCPATH) bbdialog.h -o moc_bbdialog.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mainwindow.h ui_TagTrainingSetDialog.h ui_plotdialog.h ui_bbdialog.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainwindow.h ui_TagTrainingSetDialog.h ui_plotdialog.h ui_bbdialog.h
ui_mainwindow.h: mainwindow.ui
	/usr/lib/qt4/bin/uic mainwindow.ui -o ui_mainwindow.h

ui_TagTrainingSetDialog.h: TagTrainingSetDialog.ui
	/usr/lib/qt4/bin/uic TagTrainingSetDialog.ui -o ui_TagTrainingSetDialog.h

ui_plotdialog.h: plotdialog.ui \
		qcustomplot.h
	/usr/lib/qt4/bin/uic plotdialog.ui -o ui_plotdialog.h

ui_bbdialog.h: bbdialog.ui
	/usr/lib/qt4/bin/uic bbdialog.ui -o ui_bbdialog.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

benchmark.o: benchmark.cpp benchmark.h \
		readWriteObjectFile.h \
		FaceObject.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o benchmark.o benchmark.cpp

Detection.o: Detection.cpp FaceObject.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Detection.o Detection.cpp

FaceObject.o: FaceObject.cpp FaceObject.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o FaceObject.o FaceObject.cpp

Main.o: Main.cpp MainUI.h \
		TagTrainingSetDialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Main.o Main.cpp

MainUI.o: MainUI.cpp MainUI.h \
		TagTrainingSetDialog.h \
		ui_mainwindow.h \
		Detection.h \
		FaceObject.h \
		RecognitionOpenCV.h \
		readWriteObjectFile.h \
		benchmark.h \
		plotdialog.h \
		bbdialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o MainUI.o MainUI.cpp

readWriteObjectFile.o: readWriteObjectFile.cpp readWriteObjectFile.h \
		FaceObject.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o readWriteObjectFile.o readWriteObjectFile.cpp

RecognitionOpenCV.o: RecognitionOpenCV.cpp FaceObject.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o RecognitionOpenCV.o RecognitionOpenCV.cpp

TagTrainingSetDialog.o: TagTrainingSetDialog.cpp TagTrainingSetDialog.h \
		ui_TagTrainingSetDialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o TagTrainingSetDialog.o TagTrainingSetDialog.cpp

plotdialog.o: plotdialog.cpp plotdialog.h \
		ui_plotdialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o plotdialog.o plotdialog.cpp

qcustomplot.o: qcustomplot.cpp qcustomplot.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qcustomplot.o qcustomplot.cpp

bbdialog.o: bbdialog.cpp bbdialog.h \
		ui_bbdialog.h \
		readWriteObjectFile.h \
		FaceObject.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bbdialog.o bbdialog.cpp

moc_MainUI.o: moc_MainUI.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_MainUI.o moc_MainUI.cpp

moc_TagTrainingSetDialog.o: moc_TagTrainingSetDialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_TagTrainingSetDialog.o moc_TagTrainingSetDialog.cpp

moc_plotdialog.o: moc_plotdialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_plotdialog.o moc_plotdialog.cpp

moc_qcustomplot.o: moc_qcustomplot.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_qcustomplot.o moc_qcustomplot.cpp

moc_bbdialog.o: moc_bbdialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_bbdialog.o moc_bbdialog.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

