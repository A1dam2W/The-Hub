SRC_DIR = src
BIN_DIR = bin
LIB_DIR = lib

CXX = g++
CPPFLAGS = -Wall -g -I$(LIB_DIR)

all: $(BIN_DIR)/.dirstamp interpreter

interpreter: $(BIN_DIR)/ProgramState.o $(SRC_DIR)/interpreter.cpp $(BIN_DIR)/LetStatement.o $(BIN_DIR)/PrintStatement.o $(BIN_DIR)/PrintAllStatement.o $(BIN_DIR)/AddStatement.o $(BIN_DIR)/SubtractStatement.o $(BIN_DIR)/MultiplyStatement.o $(BIN_DIR)/DivisionStatement.o $(BIN_DIR)/Goto.o $(BIN_DIR)/GOSUB.o $(BIN_DIR)/RETURN.o $(BIN_DIR)/END.o $(BIN_DIR)/IfStatement.o $(BIN_DIR)/dotend.o
	$(CXX) $(CPPFLAGS) $^ -o $@

$(BIN_DIR)/LetStatement.o: $(SRC_DIR)/LetStatement.cpp $(LIB_DIR)/LetStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/ProgramState.o: $(SRC_DIR)/ProgramState.cpp $(LIB_DIR)/ProgramState.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/PrintStatement.o: $(SRC_DIR)/PrintStatement.cpp $(LIB_DIR)/PrintStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/PrintAllStatement.o: $(SRC_DIR)/PrintAllStatement.cpp $(LIB_DIR)/PrintAllStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/AddStatement.o: $(SRC_DIR)/AddStatement.cpp $(LIB_DIR)/AddStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/SubtractStatement.o: $(SRC_DIR)/SubtractStatement.cpp $(LIB_DIR)/SubtractStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/MultiplyStatement.o: $(SRC_DIR)/MultiplyStatement.cpp $(LIB_DIR)/MultiplyStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/DivisionStatement.o: $(SRC_DIR)/DivisionStatement.cpp $(LIB_DIR)/DivisionStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/Goto.o: $(SRC_DIR)/Goto.cpp $(LIB_DIR)/Goto.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/GOSUB.o: $(SRC_DIR)/GOSUB.cpp $(LIB_DIR)/GOSUB.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/RETURN.o: $(SRC_DIR)/RETURN.cpp $(LIB_DIR)/RETURN.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/END.o: $(SRC_DIR)/END.cpp $(LIB_DIR)/END.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/IfStatement.o: $(SRC_DIR)/IfStatement.cpp $(LIB_DIR)/IfStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/dotend.o: $(SRC_DIR)/dotend.cpp $(LIB_DIR)/dotend.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BIN_DIR)

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp


