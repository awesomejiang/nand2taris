MAIN=	main.o
BINS= main

CC= gcc
CXX= g++

LIBS= -lm
ifeq	($(DEF),DEBUG)
	CFLAGS= -g -Wall -Wextra
else
	ifeq ($(DEF),PROF)
		CFLAGS= -O3 -pg
	else
		CFLAGS=-O3
	endif
endif

all:$(BINS)

main:$(MAIN) whitespace.h
	$(CXX) $(MAIN) -o $@ $(LIBS) $(CFLAGS)

clean:
	rm -f *.o *.dat

cleanall:clean
	rm -f $(BINS) *.dat

.SUFFIXES: .f90 .0 .mod .F .C .cpp

.c.o:
	$(CC) $(CFLAGS) -C $<

.cPP.o:
	$(CXX) $(CFLAGS) -C $<

