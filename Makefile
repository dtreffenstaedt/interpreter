CXX = g++
LDFLAGS = -std=c++17
CXXFLAGS = -Wall 
LIBS = 

INCLUDEDIRS = include

SOURCEFILES = main.cpp Scanner.cpp VariableManager.cpp Token.cpp Parser.cpp FunctionManager.cpp AST/Assignment.cpp AST/Compound.cpp AST/Real.cpp AST/Integer.cpp AST/Variable.cpp AST/Base.cpp AST/FunctionCall.cpp AST/ReturnStatement.cpp AST/VariableDefinition.cpp AST/BinaryOperation.cpp AST/FunctionDefinition.cpp AST/UnaryOperation.cpp AST/String.cpp AST/Character.cpp AST/Boolean.cpp AST/PrintStatement.cpp
#HEADERFILES = Token.h Scanner.h VariableManager.h Queue.h Timer.h Parser.h AST.h FunctionManager.h AST/Base.h AS
SOURCEDIR = src
HEADERDIR = include

BINDIR = bin
DOCDIR = doc

TARGET = interpreter


SOURCES=$(patsubst %, $(SOURCEDIR)/%,$(SOURCEFILES))
#HEADERS=$(patsubst %, $(HEADERDIR)/%,$(HEADERFILES))
LIBRARIES=$(patsubst %, -L%,$(LIBS))
INCLUDE=$(patsubst %,-I%,$(INCLUDEDIRS))


all: debug release

release: CXXFLAGS += -O3
release: TARGETFILES = $(BINDIR)/Release/$(TARGET)
release: mkdir -p bin/Release
release: executable

debug: CXXFLAGS += -g -Og
debug: TARGETFILES = $(BINDIR)/Debug/$(TARGET)
debug: mkdir -p bin/Debug
debug: executable

executable: $(SOURCES)# $(HEADERS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LIBRARIES) $(INCLUDE) $(SOURCES) -o $(TARGETFILES)

clean:
	rm -rf $(BINDIR)/* & m -rf $(DOCDIR)/*
