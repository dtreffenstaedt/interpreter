CXX = g++
LDFLAGS = -std=c++14
CXXFLAGS = -Wall 
LIBS = 

INCLUDEDIRS = include

SOURCEFILES = main.cpp Scanner.cpp VariableManager.cpp Token.cpp Parser.cpp FunctionManager.cpp AST.cpp
HEADERFILES = Token.h Scanner.h VariableManager.h Queue.h Timer.h Parser.h AST.h FunctionManager.h

SOURCEDIR = src
HEADERDIR = include

BINDIR = bin
DOCDIR = doc

TARGET = interpreter


SOURCES=$(patsubst %, $(SOURCEDIR)/%,$(SOURCEFILES))
HEADERS=$(patsubst %, $(HEADERDIR)/%,$(HEADERFILES))
LIBRARIES=$(patsubst %, -L%,$(LIBS))
INCLUDE=$(patsubst %,-I%,$(INCLUDEDIRS))


all: debug release

release: CXXFLAGS += -O3
release: TARGETFILES = $(BINDIR)/Release/$(TARGET)
release: executable

debug: CXXFLAGS += -g -Og
debug: TARGETFILES = $(BINDIR)/Debug/$(TARGET)
debug: executable

executable: $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LIBRARIES) $(INCLUDE) $(SOURCES) $(HEADERS) -o $(TARGETFILES)

clean:
	rm -rf $(BINDIR)/* & m -rf $(DOCDIR)/*
