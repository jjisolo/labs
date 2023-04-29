CXX=g++
STD=-std=c++20
OBJ=main.cc plainc.cc modernc.cc
EXEC=lab 

all:
	$(CXX) $(OBJ) -o $(EXEC) $(STD)
