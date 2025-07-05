#
# --------------------------------------------------------------------------
#  Gurux Ltd
#
#
#
# Filename:        $HeadURL$
#
# Version:         $Revision$,
#                  $Date$
#                  $Author$
#
# Copyright (c) Gurux Ltd
#
#---------------------------------------------------------------------------
#
#  DESCRIPTION
#
# This file is a part of Gurux Device Framework.
#
# Gurux Device Framework is Open Source software; you can redistribute it
# and/or modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; version 2 of the License.
# Gurux Device Framework is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
#
# More information of Gurux products: http://www.gurux.org
#
# This code is licensed under the GNU General Public License v2.
# Full text may be retrieved at http://www.gnu.org/licenses/gpl-2.0.txt
#---------------------------------------------------------------------------
# Generate STATIC library.
TARGET   = libgurux_dlms_cpp.a
CC       = g++
# compiling flags here
CFLAGS   = -O3 -Wall -fPIC 

LINKER   = ar rvs

# linking flags here
LFLAGS   =  

# change these to set the proper directories where each files shoould be

SRCDIR   = src
OBJDIR   = obj
LIBDIR   = lib

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
rm       = rm -rf
mkdir    = mkdir -p

# Test related variables
TEST_SRCDIR = tests
TEST_OBJDIR = $(OBJDIR)/tests
TEST_TARGET = test_runner
TEST_SOURCES  := $(wildcard $(TEST_SRCDIR)/*.cpp)
TEST_OBJECTS  := $(TEST_SOURCES:$(TEST_SRCDIR)/%.cpp=$(TEST_OBJDIR)/%.o)
GTEST_SRCDIR = $(TEST_SRCDIR)/lib/googletest/googletest
GTEST_SRC = $(GTEST_SRCDIR)/src/gtest-all.cc
GTEST_OBJ = $(TEST_OBJDIR)/gtest-all.o
TEST_CFLAGS = $(CFLAGS) -Iinclude -I$(GTEST_SRCDIR)/include -pthread
TEST_LFLAGS = $(LFLAGS) -pthread

# Default target
all: $(LIBDIR)/$(TARGET)

$(LIBDIR)/$(TARGET): $(OBJECTS)
	@$(mkdir) $(LIBDIR)
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(mkdir) $(OBJDIR)
	@$(CC) $(CFLAGS) -Iinclude -c $< -o $@
	@echo "Compiled "$<" successfully!"

# Target to build and run tests
test: $(LIBDIR)/$(TARGET) $(TEST_OBJDIR)/$(TEST_TARGET)
	@echo "Running tests..."
	@$(TEST_OBJDIR)/$(TEST_TARGET)

# Target to build the test runner
$(TEST_OBJDIR)/$(TEST_TARGET): $(TEST_OBJECTS) $(GTEST_OBJ) $(LIBDIR)/$(TARGET)
	@$(mkdir) -p $(TEST_OBJDIR)
	@$(CC) $(TEST_CFLAGS) $^ -o $@ $(LIBDIR)/$(TARGET) $(TEST_LFLAGS)
	@echo "Test runner linked successfully!"

# Rule for compiling test source files
$(TEST_OBJECTS): $(TEST_OBJDIR)/%.o : $(TEST_SRCDIR)/%.cpp
	@$(mkdir) -p $(TEST_OBJDIR)
	@$(CC) $(TEST_CFLAGS) -c $< -o $@
	@echo "Compiled test "$<" successfully!"

# Rule for compiling gtest-all.cc
$(GTEST_OBJ): $(GTEST_SRC)
	@$(mkdir) -p $(TEST_OBJDIR)
	@$(CC) $(TEST_CFLAGS) -I$(GTEST_SRCDIR)/include -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean all test
clean:
	@$(rm) $(OBJDIR) $(TEST_OBJDIR)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(LIBDIR)
	@echo "Library and executable removed!"
