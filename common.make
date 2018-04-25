
TESTS:=$(wildcard tests/*.cpp)
TESTOBJS:=objects/tests/main.o

LDLIBS+=-lboost_unit_test_framework-mt

.PHONY: all
all: unit-tests

objects/tests/main.o: tests/main.cpp include/Interpolate.hpp
	@echo -n "Compiling $<..."	
	@$(CXX) $(INCLUDES) $(CXXFLAGS) -DBOOST_LOG_DYN_LINK -DBOOST_TEST_DYN_LINK -c $< -o $@
	@echo " done"

# Link unit tests
unit-tests: $(TESTOBJS) $(OBJS)
	@echo  -n "Linking $@..."
	@$(CXX) $(CXXFLAGS) $(TESTOBJS) $(filter-out objects/$(SYSTEM)/src/main.o, $(OBJS)) $(LDFLAGS) $(LDLIBS) -o $@
	@echo " done"

