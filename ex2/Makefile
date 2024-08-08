all: mkd bin/test_ex2 bin/main_ex2

CC = gcc

BUILDDIR1 = build
BUILDDIR2 = build/Unity
BUILDDIR3 = bin

 

CFLAGS = -g  -Wall -Wextra -Wconversion

INCLUDES = src/*.h

COMMON_DEPS = $(INCLUDES) Makefile

mkd:  
	@echo "Creating the build folder..."
	@mkdir -p $(BUILDDIR1)
	@echo "Creating the build/Unity folder..."
	@mkdir -p $(BUILDDIR2)
	@echo "Creating the bin folder..."
	@mkdir -p $(BUILDDIR3)


build/%.o: src/%.c $(COMMON_DEPS)
	@$(CC) $(CFLAGS) -o $@  -c $<
	
build/Unity/%.o: ../Unity/%.c $(COMMON_DEPS)
	@$(CC) $(CFLAGS) -o $@  -c $<

bin/main_ex2: build/main_ex2.o build/lib.o build/utils.o $(COMMON_DEPS)
	@echo "Building main..."
	@$(CC) $(CFLAGS) -o bin/main_ex2  src/main_ex2.c src/lib.c build/utils.o
	
bin/test_ex2: build/test_ex2.o build/lib.o build/Unity/unity.o $(COMMON_DEPS)
	@echo "Building tests..."
	@$(CC) -o bin/test_ex2  build/test_ex2.o build/lib.o build/Unity/unity.o
	@echo "All operation terminated successfully."

clean:
	@echo "Removing all object files and executable..."
	@rm -f build/Unity/*
	@rmdir build/Unity
	@rm -f build/* bin/* src/results.csv
	@rmdir build bin
