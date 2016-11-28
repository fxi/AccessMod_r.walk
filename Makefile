MODULE_TOPDIR = ../..

PGM = r.walk.accessmod
GSL_CFLAGS = $(shell pkg-config --cflags gsl) 
GSL_LIB = $(shell pkg-config --libs gsl) 

LIBES = $(SEGMENTLIB) $(VECTORLIB) $(RASTERLIB) $(GISLIB) $(MATHLIB) $(GSL_LIB)
DEPENDENCIES = $(SEGMENTDEP) $(VECTORDEP) $(RASTERDEP) $(GISDEP)
EXTRA_INC = $(VECT_INC)
EXTRA_CFLAGS = $(VECT_CFLAGS) $(GSL_CFLAGS)

CFLAGS="-O2 -Wall -march=x86-64 -mtune=native"
LDFLAGS="-s"


include $(MODULE_TOPDIR)/include/Make/Module.make

default: cmd
