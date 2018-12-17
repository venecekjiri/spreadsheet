CXX=g++
LD=g++
CXXFLAGS=-std=c++14 -Wall -pedantic -Wno-long-long -O0 -ggdb -pthread

BIN_DIR=bin
OUTPUT=venecjir
TEST_OUTPUT=test

OBJECTS=\
	$(BIN_DIR)/CApplication.o\
	$(BIN_DIR)/CCell.o\
	$(BIN_DIR)/CExpression.o\
	$(BIN_DIR)/CInputParser.o\
	$(BIN_DIR)/CNode.o\
	$(BIN_DIR)/CSheet.o\
	$(BIN_DIR)/CTable.o\
	$(BIN_DIR)/CLinks.o\
	$(BIN_DIR)/CController.o\
	$(BIN_DIR)/CInputReader.o

all: compile

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

compile: $(BIN_DIR) $(OBJECTS) $(BIN_DIR)/main.o
	$(LD) $(CXXFLAGS) -o $(OUTPUT) $(OBJECTS) $(BIN_DIR)/main.o

compileTest: $(BIN_DIR) $(OBJECTS) $(BIN_DIR)/test.o
	$(LD) $(CXXFLAGS) -o examples/$(TEST_OUTPUT) $(OBJECTS) $(BIN_DIR)/test.o

run:
	./$(OUTPUT)

doc:
	doxygen Doxyfile

clean:
	rm -rf $(OUTPUT) examples/$(TEST_OUTPUT) $(BIN_DIR) doc

$(BIN_DIR)/CApplication.o: src/CApplication.cpp src/CApplication.h src/CSheet.h src/CCell.h \
 src/CExpression.h src/CNode.h src/CLinks.h src/CController.h src/CInputReader.cpp \
 src/CInputReader.h src/CColorStream.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN_DIR)/CCell.o: src/CCell.cpp src/CCell.h src/CExpression.h src/CNode.h src/CInvalidFormat.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN_DIR)/CController.o: src/CController.cpp src/CController.h src/CInputReader.cpp \
 src/CInputReader.h src/CColorStream.h src/CSheet.h src/CCell.h src/CExpression.h src/CNode.h \
 src/CLinks.h src/CTable.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN_DIR)/CExpression.o: src/CExpression.cpp src/CExpression.h src/CNode.h src/CInvalidFormat.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN_DIR)/CInputParser.o: src/CInputParser.cpp src/CInputParser.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN_DIR)/CInputReader.o: src/CInputReader.cpp src/CInputReader.h src/CColorStream.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN_DIR)/CLinks.o: src/CLinks.cpp src/CLinks.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN_DIR)/CNode.o: src/CNode.cpp src/CNode.h src/CSheet.h src/CCell.h src/CExpression.h src/CLinks.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN_DIR)/CSheet.o: src/CSheet.cpp src/CSheet.h src/CCell.h src/CExpression.h src/CNode.h src/CLinks.h \
 src/CInputParser.h src/CInvalidFormat.h src/CInvalidCoordinates.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN_DIR)/CTable.o: src/CTable.cpp src/CTable.h src/CSheet.h src/CCell.h src/CExpression.h src/CNode.h \
 src/CLinks.h src/CColorStream.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN_DIR)/main.o: src/main.cpp src/CApplication.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN_DIR)/test.o: examples/test.cpp examples/TestCExpression.cpp examples/TestCSheet.cpp examples/TestCInputParser.cpp src/CSheet.h src/CExpression.h src/CInputParser.h src/CLinks.h src/CInputReader.h \
src/CController.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<
