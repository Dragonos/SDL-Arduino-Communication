# définition des cibles particulières
.PHONY: clean, mrproper
 
# désactivation des règles implicites
.SUFFIXES:


CC = gcc
CFLAGS = -Wall -w
RM = rm -rf


EXEC = PlaneGame
# -l
LIBS = -lSDL -lSDL_image -lserialport
# -L
LIBSPATH = 
# -I
INCLUDESPATH = 

SOURCES=main.c
OBJECTS=$(SOURCES:.cpp=.o)


all : main.o arduino.o
	$(CC) $^ -o $(EXEC) $(INCLUDESPATH) $(LIBSPATH) $(LIBS)

%.o : %.c
	$(CC)  $(LIBSPATH) $(INCLUDESPATH) -c $< -o $@ $(CFLAGS)
	
clean :
	$(RM) *.o
	
mrproper : clean
	$(RM) $(EXEC)
