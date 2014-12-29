# ex. installation : 
# linux : sudo make MODULE_TOPDIR=/usr/local/grass-7.0.0beta/
# mac (homebrew + osge4mac/grass70) make MODULE_TOPDIR=/usr/local/Cellar/grass-70/7.0.0beta3/grass-7.0.0beta3/

MODULE_TOPDIR = ../..
PGM = r.walk.accessmod
GSL_LIB = `gsl-config --libs`

LIBES = $(SEGMENTLIB) $(VECTORLIB) $(RASTERLIB) $(GISLIB) $(MATHLIB) $(GSL_LIB)
DEPENDENCIES = $(SEGMENTDEP) $(VECTORDEP) $(RASTERDEP) $(GISDEP)
EXTRA_INC = $(VECT_INC)
EXTRA_CFLAGS = $(VECT_CFLAGS)

CFLAGS="-O2  -Wall"
LDFLAGS="-s"

include $(MODULE_TOPDIR)/include/Make/Module.make

default: cmd
