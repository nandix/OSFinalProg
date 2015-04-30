# Makefile for OpenGL/GLUT programs.

# Author: John M. Weiss, Ph.D.
# Written Fall 2014 for CSC433/533 Computer Graphics.

# Usage:  make target1 target2 ...

#-----------------------------------------------------------------------

# GNU C/C++ compiler and linker:
CC = gcc
CXX = g++
LINK = g++

# Turn on optimization and warnings (add -g for debugging with gdb):
# CPPFLAGS = 		# preprocessor flags
CFLAGS = -g -O3 -Wall
CXXFLAGS = -g -O3 -Wall

VPATH = src
#-----------------------------------------------------------------------

# MAKE allows the use of "wildcards", to make writing compilation instructions
# a bit easier. GNU make uses $@ for the target and $^ for the dependencies.

all:    mmu_simulation

# specific targets
mmu_simulation: simulation_mmu.o reloc.o tlb.o paging.o
	$(LINK) $(CFLAGS) $^ -o $@

#bio_inspired_hw:	main.o bone_marrow.o hill_climbing.o  fit_func.o particle_swarm.o simulated_annealing.o genetic_programming.o
#	$(LINK) -g -Wall -o $@ $^

# generic C and C++ targets for OpenGL programs consisting of only one file
# type "make filename" (no extension) to build
.c:
	$(CC) $(CFLAGS) -o $@ $@.c $(GL_LIBS)

.cpp:
	$(CXX) $(CFLAGS) -o $@ $@.cpp $(GL_LIBS)

# utility targets
clean_objects:
	rm -f *.o *~ core
clean_execs:
	rm -f mmu_simulation
clean:
	rm -f *.o *~ core
	rm -f mmu_simulation
