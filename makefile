CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.c GestionMemoire.c Ordonnacement.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=Simulateur.run

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@