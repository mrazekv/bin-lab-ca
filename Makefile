CPP=g++
CPPFLAGS=-Wall -std=gnu++11

all: ca_gp
ca_gp: ca_gp.cpp ca_sim.hpp
	$(CPP) $(CPPFLAGS) -o $@ $^

pack:
	zip bin_lab3.zip ca_gp.cpp ca_sim.hpp Makefile
