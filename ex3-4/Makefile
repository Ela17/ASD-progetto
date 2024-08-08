# Variables
SRC_DIR = src
BIN_DIR = bin
PACKAGE = graphusage
MAIN_CLASS = Prim
ARGS = italian_dist_graph.csv
JUNITPATH = Junit4/junit-4.13.2.jar:Junit4/hamcrest-core-1.3.jar

# Find all Java source files
SOURCES := $(shell find $(SRC_DIR) -name "*.java" ! -name "UnitTest*.java")
TEST_SOURCES := $(shell find $(SRC_DIR) -name "UnitTest*.java")

all: compile 

# Target to compile all Java source files
compile:
	@mkdir -p $(BIN_DIR)
	javac -cp $(JUNITPATH) -d $(BIN_DIR) $(TEST_SOURCES) $(SOURCES)

# Target to run the main class
run: compile
	java -cp $(BIN_DIR) $(PACKAGE).$(MAIN_CLASS) $(ARGS)

# Target to compile the test files of priority queue
run_test_priority:
	java -cp $(BIN_DIR):$(BIN_DIR)/priorityqueue:$(JUNITPATH) org.junit.runner.JUnitCore test.priorityqueue.UnitTestBase test.priorityqueue.UnitTestAdvanced
	
# Target to compile the test files of graph
run_test_graph: 
	java -cp $(BIN_DIR):$(BIN_DIR)/graph:$(JUNITPATH) org.junit.runner.JUnitCore test.graph.UnitTest 

# Target to clean the bin directory
clean:
	rm -rf $(BIN_DIR)
