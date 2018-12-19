# vpath %.cpp ./src
# vpath %.o ./build
# 
# classic/maximum_subarray.o : classic/maximum_subarray.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@
# 
# bin/classic/maximum_subarray_time : classic/maximum_subarray_time.cpp classic/maximum_subarray.o
# 	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

# BIN=./bin/
# BUILD=./build/
#

MKDIR = mkdir -p

CXX = g++-8

GTESTDIR = /opt/googletest/googletest
GTEST_HEADERS = $(GTESTDIR)/include/gtest/*.h \
				$(GTESTDIR)/include/gtest/internal/*.h
SRCDIR = src
OBJDIR = build
BINDIR = bin
DEPDIR = dep
INCLUDE = -Iinclude -I.

SOURCES = $(wildcard src/*.cpp)

OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
BINARIES = $(SOURCES:$(SRCDIR)/%.cpp=$(BINDIR)/%)
DEPENDENCIES = $(OBJECTS:$(OBJDIR)/%.o=$(DEPDIR)/%.d)

echo :
	$(info $$OBJECTS is [${OBJECTS}])

CXXFLAGS = -std=c++17 -Wall -Wextra -pthread -g
CPPFLAGS = -isystem $(GTESTDIR)/include $(INCLUDE)

#lib/libalgo.a : $(OBJECTS)
#	$(AR) $(ARFLAGS) $@ $?

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(MKDIR) $(shell dirname $@) # TODO: ili ih samo napraviti na pocetku
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

-include $(DEPENDENCIES)

$(DEPENDENCIES) : $(DEPDIR)/%.d : $(SRCDIR)/%.cpp
	$(MKDIR) $(shell dirname $@) # TODO: ili ih samo napraviti na pocetku
	@$(CPP) $(CPPFLAGS) $(CXXFLAGS) $< -MM -MT $(@:$(DEPDIR)/%.d=$(OBJDIR)/%.o) -o $@

$(BINARIES): $(BINDIR)/% : $(SRCDIR)/%.cpp $(OBJECTS)
	$(MKDIR) $(shell dirname $@) # TODO: ili ih samo napraviti na pocetku
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

SOURCES_TEST = $(wildcard src/test/*.cpp)

OBJECTS_TEST = $(SOURCES_TEST:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
BINARIES_TEST = $(SOURCES_TEST:$(SRCDIR)/%.cpp=$(BINDIR)/%)
DEPENDENCIES_TEST = $(OBJECTS_TEST:$(OBJDIR)/%.o=$(DEPDIR)/%.d)

$(OBJECTS_TEST): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(MKDIR) $(shell dirname $@) # TODO: ili ih samo napraviti na pocetku
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

-include $(DEPENDENCIES_TEST)

$(DEPENDENCIES_TEST) : $(DEPDIR)/%.d : $(SRCDIR)/%.cpp
	$(MKDIR) $(shell dirname $@) # TODO: ili ih samo napraviti na pocetku
	@$(CPP) $(CPPFLAGS) $(CXXFLAGS) $< -MM -MT $(@:$(DEPDIR)/%.d=$(OBJDIR)/%.o) -o $@

$(BINARIES_TEST): $(BINDIR)/% : $(OBJDIR)/%.o  \
	$(GTESTDIR)/make/gtest_main.a $(OBJECTS)	
	$(MKDIR) $(shell dirname $@) # TODO: ili ih samo napraviti na pocetku
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

# 
# $(BUILD)insertion_sort.o: $(SRC)sorting/insertion_sort.cpp
# 	$(CXX) -std=c++11 -O2 -c $< -o $@
# 
# $(BUILD)selection_sort.o: $(SRC)sorting/selection_sort.cpp
# 	$(CXX) -std=c++11 -O2 -c $< -o $@
# 
# $(BUILD)merge_sort.o: $(SRC)sorting/merge_sort.cpp $(SRC)sorting/insertion_sort.cpp
# 	$(CXX) -std=c++11 -O2 -I$(SRC) -c $< -o $@
# 
# $(BUILD)util.o : $(SRC)util.cpp
# 	$(CXX) -std=c++11 -O2 -c $< -o $@
# 
# $(BIN)min_test : $(SRC)test/util.cpp $(BUILD)util.o
# 	$(CXX) -std=c++11 -pthread -I$(SRC) -O2 -o $@ $^
#  
# $(BIN)insertion_sort_test: $(SRC)test/sorting/insertion_sort_test.cpp $(BUILD)insertion_sort.o $(BUILD)util.o
# 	$(CXX) -std=c++11 -pthread -I$(SRC) -O2 -o $@ $^
# 
# $(BIN)selection_sort_test: $(SRC)test/sorting/selection_sort_test.cpp $(BUILD)selection_sort.o $(BUILD)util.o
# 	$(CXX) -std=c++11 -pthread -I$(SRC) -O2 -o $@ $^
# 
# $(BIN)parallel_selection_sort_test: $(SRC)test/sorting/parallel_selection_sort_test.cpp $(BUILD)selection_sort.o $(BUILD)util.o
# 	$(CXX) -std=c++11 -pthread -I$(SRC) -O2 -o $@ $^
# 
# $(BIN)merge_sort_test: $(SRC)test/sorting/merge_sort_test.cpp $(BUILD)util.o $(BUILD)merge_sort.o $(BUILD)insertion_sort.o
# 	$(CXX) -std=c++11 -pthread -I$(SRC) -O2 -o $@ $^
# 
# $(BIN)merge_insertion_sort_test: $(SRC)/test/sorting/merge_insertion_sort_test.cpp $(BUILD)util.o $(BUILD)merge_sort.o $(BUILD)insertion_sort.o
# 	$(CXX) --std=c++11 -pthread -I$(SRC) -O2 -o $@ $^
# 
# test : $(BIN)insertion_sort_test $(BIN)selection_sort_test
# 	$^
# 
# bla :
# 	@sh test_time.sh
