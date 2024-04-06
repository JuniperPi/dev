# A basic C++ makefile for my code

# Name of executable
NAME = dev

# directories of significance
BDIR   = ../bin
# LDIR   = ../lib # currently empty
ODIR   = ../obj
OUTDIR = ../out

# combine binary and its directory into one path
BPATH = $(BDIR)/$(NAME)

# compiler and flags
CXX = g++

# I keep my includes in my src directory, along with my makefiles
CXXFLAGS  = -I.
CXXFLAGS += -DOUTDIR=\"$(shell realpath $(OUTDIR))\"
CXXFLAGS += -std=c++17

# C++ source files to compile
SRCS = dev.cc

# for each .cc file here, make a .o file in $(ODIR)
OBJS = $(patsubst %.cc,$(ODIR)/%.o,$(SRCS))

# rule to make .o files
$(ODIR)/%.o: %.cc
	$(CXX) -c -o $@ $< $(CXXFLAGS)

# rule to make binary
$(BPATH): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS)

# phony rules are those which do not make/modify actual files
.PHONY: all clean purge

# all of the things this makefile should make when called without arguments
all: $(BPATH)

# make clean will delete the object files
clean:
	$(RM) $(OBJS)

# make purge will delete the object files and then remake the binary
purge: clean all
