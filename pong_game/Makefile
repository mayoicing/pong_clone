# Replace this with the path you get from `brew info sfml`
SFML_PATH = /usr/local/Cellar/sfml/2.6.2

# Replace "src" with the name of the folder where all your cpp code is
cppFileNames := $(shell find ./src -type f -name "*.cpp")

CXX = clang++
CXXFLAGS = -std=c++17 -I$(SFML_PATH)/include
LDFLAGS = -L$(SFML_PATH)/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

all: compile run

compile:	
	mkdir -p bin
	$(CXX) $(CXXFLAGS) $(cppFileNames) -o bin/app $(LDFLAGS)

run:
	./bin/app

clean:
	rm -rf bin