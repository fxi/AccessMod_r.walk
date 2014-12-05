CC=gcc
LDIR = /usr/local/lib
LIBS=-lm -lgsl -lgslcblas
LIB = $(patsubst %,$(LDIR)/%,$(LIBS))
ODIR = .
INCDIR = .

CFLAGS=-I.
DEPS = 
#DEPS = bikeSpeed.h bikeConstant.h
#gcc -L/usr/local/lib bikeSpeed.o -lgsl -lgslcblas -lm -o bikeSpeed

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -L$(LDIR) $(LIBS)

timeCostManager: timeCostManager.o  
	$(CC) -o timeCostManager.o -I. -L$(LDIR) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
