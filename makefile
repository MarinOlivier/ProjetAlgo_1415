# définition des cibles particulières
.PHONY: clean 
 
# désactivation des règles implicites
.SUFFIXES:
 
# définition des variables
CXX = g++
CXXFLAGS = -Wall
 
 
 
# all
all: main.o compression.o decompression.o
	$(CXX) $^ -o lzw $(CXXFLAGS)
 
main.o: compression.h decompression.h
 
%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)
 
 
# clean
clean:
	rm -rf *.o
 
# mrproper
#mrproper: clean
#	rm -rf exec