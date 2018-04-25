
TESTS:=$(wildcard tests/*.cpp)
TESTOBJS:=objects/tests/main.o objects/tests/InterpolateTests.o

INCLUDES+= -Iinclude

LDLIBS+=-lboost_unit_test_framework-mt

CXXFLAGS+=-std=c++11 -g

.PHONY: all
all: unit-tests

objects/tests/InterpolateTests.o: tests/InterpolateTests.cpp include/Interpolate.hpp include/InterpolateTemplates.cpp
	@echo -n "Compiling $<..."	
	@$(CXX) $(INCLUDES) $(CXXFLAGS) -DBOOST_LOG_DYN_LINK -DBOOST_TEST_DYN_LINK -c $< -o $@
	@echo " done"

objects/tests/main.o:
	@echo -n "Compiling $<..."	
	@$(CXX) $(INCLUDES) $(CXXFLAGS) -DBOOST_LOG_DYN_LINK -DBOOST_TEST_DYN_LINK -c $< -o $@
	@echo " done"

# Link unit tests
unit-tests: $(TESTOBJS) $(OBJS)
	@echo  -n "Linking $@..."
	@$(CXX) $(CXXFLAGS) $(TESTOBJS) $(filter-out objects/$(SYSTEM)/src/main.o, $(OBJS)) $(LDFLAGS) $(LDLIBS) -o $@
	@echo " done"

