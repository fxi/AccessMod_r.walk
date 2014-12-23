# ex. installation : 
# linux : sudo make MODULE_TOPDIR=/home/vagrant/download/grass-7.0.0beta3 INST_DIR=/usr/local/grass-7.0.0beta/

MODULE_TOPDIR = ../..

PGM = r.walk.accesmod
GSL_LIB = `gsl-config --libs`

LIBES = $(SEGMENTLIB) $(VECTORLIB) $(RASTERLIB) $(GISLIB) $(MATHLIB) $(GSL_LIB)
DEPENDENCIES = $(SEGMENTDEP) $(VECTORDEP) $(RASTERDEP) $(GISDEP)
EXTRA_INC = $(VECT_INC)
EXTRA_CFLAGS = $(VECT_CFLAGS)

include $(MODULE_TOPDIR)/include/Make/Module.make

default: cmd
