# définition des cibles particulières
.PHONY: clean 
 
# désactivation des règles implicites
.SUFFIXES:
 
# définition des variables
CXX = g++
CXXFLAGS = -Wall
 
 
 
# all
all: main.o
	$(CXX) $^ -o exec $(CXXFLAGS)
 
main.o:
 
%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)
 
 
# clean
clean:
	rm -rf *.o
 
# mrproper
#mrproper: clean
#	rm -rf exec