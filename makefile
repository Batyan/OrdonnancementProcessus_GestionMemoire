CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.c GestionMemoire.c Ordonnancement.c DialoguesPereFils.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=Simulateur.run

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean: 
	rm -rf *o $(EXECUTABLE)
