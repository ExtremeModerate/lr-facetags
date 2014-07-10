lr-facetags
===========

# Installation

Requirements: OpenCV, QT

Makefile: compiling could throw some undefined reference errors to openCV functions, then you have to add 'pkg-config --cflags --libs opencv' to the Makefile at line 115

the Makefile should look like this:
all: Makefile $(TARGET)
$(TARGET): ui_mainwindow.h $(OBJECTS)
$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS) `pkg-config --cflags --libs opencv`




# Usage

For the datatool usage see: [Datasettools2](https://github.com/mll-freiburg/lr-facetags/wiki/Datasettools2)
