
TESTS:=$(wildcard tests/*.cpp)
TESTOBJS:=$(addprefix objects/,$(TESTS:.cpp=.o))

LDLIBS+=-lboost_unit_test_framework-mt

# Compile unit tests
objects/tests/%.o: tests/%.cpp
	@echo -n "Compiling $<..."	
	@$(CXX) $(INCLUDES) $(CXXFLAGS) -DBOOST_LOG_DYN_LINK -DBOOST_TEST_DYN_LINK -c $< -o $@
	@echo " done"

# Link unit tests
unit-tests: $(TESTOBJS) $(OBJS)
	@echo  -n "Linking $@..."
	@$(CXX) $(CXXFLAGS) $(TESTOBJS) $(filter-out objects/$(SYSTEM)/src/main.o, $(OBJS)) $(LDFLAGS) $(LDLIBS) -o $@
	@echo " done"

