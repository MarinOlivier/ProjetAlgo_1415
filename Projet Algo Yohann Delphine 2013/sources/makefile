SHELL      = /bin/bash
CC         = gcc
MKDEP      = gcc -MM
RM         = rm -f
GLLIBS     = 
GLINCLUDES = 
CCOPTS     = -Wall -g

OBJECTS = main.o chaine_caracteres.o dictionnaire.o lecture_ecriture.o compression.o decompression.o
EXEC    = lzw

all : $(EXEC)

.c.o :
	$(CC) $(CCOPTS) -c $*.c

$(EXEC) : $(OBJECTS)
	$(CC) $^ -o $@ $(GLLIBS)

clean :
	$(RM) *.o $(EXEC) depend

depend :
	$(MKDEP) *.c > depend

include depend
