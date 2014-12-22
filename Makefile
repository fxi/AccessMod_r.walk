#MODULE_TOPDIR = ../..
#MODULE_TOPDIR=/Users/fxi/Downloads/grass-7.0.0beta3
MODULE_TOPDIR=/usr/local/Cellar/grass-70/7.0.0beta3/grass-7.0.0beta3/

PGM = r.walk.accesmod
GSL_LIB = `gsl-config --libs`

LIBES = $(SEGMENTLIB) $(VECTORLIB) $(RASTERLIB) $(GISLIB) $(MATHLIB) $(GSL_LIB)
DEPENDENCIES = $(SEGMENTDEP) $(VECTORDEP) $(RASTERDEP) $(GISDEP)
EXTRA_INC = $(VECT_INC)
EXTRA_CFLAGS = $(VECT_CFLAGS)

#include $(MODULE_TOPDIR)/include/Make/Module.make
include $(MODULE_TOPDIR)/include/Make/Module.make

default: cmd
