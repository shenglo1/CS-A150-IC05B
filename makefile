##################################################
#   GENERIC G++ MAKEFILE
#   MODIFY BELOW
##################################################
# REPLACE THIS WITH THE NAME OF YOUR EXECUTABLE
EXE = main.exe

# Modify compiler flags as desired
CXXFLAGS = -std=c++11 -Wall -pedantic -Os -Wextra -Wconversion -std=c++11

LDFLAGS =
# Uncomment line below for windows programs
# LDFLAGS = -mwindows

######################################################
#	GENERALLY WON'T CHANGE ANY OF THIS
######################################################
ifeq ($(strip $(EXE)),)
empty-exe-error:
	@echo FORGOT TO SUPPLY A NAME TO EXE IN MAKEFILE
endif

# All cpp files in folder
SRC = $(wildcard *.cpp)

# .o file for every .cpp
OBJS = $(SRC:.cpp=.o)

# C++ Compiler
CXX = g++

# Run psuedo target 2x for class
run: $(EXE)
	$(EXE)

# Rule to build the executable, delete the output
$(EXE): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@

# Rule for g++ to build .o files from .cpp files
%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $<
