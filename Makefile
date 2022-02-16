CXXFLAGS=--std=c++14 -Wall -O3 -march=native
HEADERS=${wildcard *.hpp}

.PHONY=clean
all: ca_majority

ca_majority: ca_majority.cpp ${HEADERS}
	${CXX} ${CXXFLAGS} ca_majority.cpp -o $@

clean:
	rm ca_majority