CXX=g++
RM=rm -f
CXXFLAGS=-std=c++11 -fpermissive -O3

SRCS=cryptanalysisOTS.cpp routines.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: cryptanalysisOTS clean

cryptanalysisOTS: $(OBJS)
	$(CXX) $(CXXFLAGS) -o breakOTS $(OBJS)

routines.o: routines.cpp 

cryptanalysisOTS.o: cryptanalysisOTS.cpp 

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) breakOTS
