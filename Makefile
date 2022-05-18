EXENAME = main
OBJS = main.o graph.o algorithms.o

CXX = clang++
LD = clang++

WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable
CXXFLAGS = -std=c++1y -stdlib=libc++ -O0 $(WARNINGS) -g -c
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi
MKDIR_P = mkdir -p

# Custom Clang version enforcement logic:
ccred=$(shell echo -e "\033[0;31m")
ccyellow=$(shell echo -e "\033[0;33m")
ccend=$(shell echo -e "\033[0m")

IS_EWS=$(shell hostname | grep "ews.illinois.edu") 
IS_CORRECT_CLANG=$(shell clang -v 2>&1 | grep "version 6")
ifneq ($(strip $(IS_EWS)),)
ifeq ($(strip $(IS_CORRECT_CLANG)),)
CLANG_VERSION_MSG = $(error $(ccred) On EWS, please run 'module load llvm/6.0.1' first when running CS225 assignments. $(ccend))
endif
else
ifneq ($(strip $(SKIP_EWS_CHECK)),True)
CLANG_VERSION_MSG = $(warning $(ccyellow) Looks like you are not on EWS. Be sure to test on EWS before the deadline. $(ccend))
endif
endif

all : $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME): output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp graph.o algorithms.o outputs
	$(CXX) $(CXXFLAGS) main.cpp 

outputs:
	mkdir -p Outputs

test : output_msg tests.o graph.o algorithms.o
	$(LD) tests.o graph.o algorithms.o $(LDFLAGS) -o test

tests.o : tests/tests.cpp tests/catch.hpp
	$(CXX) $(CXXFLAGS) tests/tests.cpp	

graph.o: graph.h graph.cpp
	$(CXX) $(CXXFLAGS) graph.cpp

algorithms.o: algorithms.h algorithms.cpp
	$(CXX) $(CXXFLAGS) algorithms.cpp

.PHONY : output_msg

clean:
	-rm -f *.o $(EXE) test ./Outputs/*
