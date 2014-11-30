#MODULE_TOPDIR = ../..
#MODULE_TOPDIR=/Users/fxi/Downloads/grass-7.0.0beta3
MODULE_TOPDIR=/usr/local/Cellar/grass-70/7.0.0beta3/grass-7.0.0beta3/
PGM = r.walk.accesmod

LIBES = $(SEGMENTLIB) $(VECTORLIB) $(RASTERLIB) $(GISLIB) $(MATHLIB)
DEPENDENCIES = $(SEGMENTDEP) $(VECTORDEP) $(RASTERDEP) $(GISDEP)
EXTRA_INC = $(VECT_INC)
EXTRA_CFLAGS = $(VECT_CFLAGS)

#include $(MODULE_TOPDIR)/include/Make/Module.make
include $(MODULE_TOPDIR)/include/Make/Module.make

default: cmd
