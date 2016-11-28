CC=gcc
#LDIR = `pkg-config --libs gsl`
#LIBS=-lm -lgsl -lgslcblas
#LIB = $(patsubst %,$(LDIR)/%,$(LIBS))

LIB = $(shell pkg-config --libs gsl) 
ODIR = .
INCDIR = .

CFLAGS=-I.
DEPS = 
#DEPS = bikeSpeed.h bikeConstant.h
#gcc -L/usr/local/lib bikeSpeed.o -lgsl -lgslcblas -lm -o bikeSpeed

#%.o: %.c $(DEPS)
	#$(CC) -c -o $@ $< $(CFLAGS) -L$(LDIR) $(LIBS)

all: 

   @echo $(LIB)


timeCostManager: timeCostManager.o  
	$(CC) -o timeCostManager.o -I. $(LIB)
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
