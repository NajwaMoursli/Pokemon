EXEC=Pokemon
SOURCES=$(wildcard *.cc)
OBJECTS=$(SOURCES:.cc=.o)
CC=g++ -std=c++11 -g
CLIBS= -L/c/MinGW/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio


INCDIR=-I/c/MinGW/include/SFML

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) $(CLIBS)  -o $(EXEC)
%.o: %.cc
	$(CC) -Wall $(INCDIR) -c $< -o $@

.depend: $(SOURCES)
	g++ -std=c++11 -MM $(SOURCES) > .depend
-include .depend
clean:
	rm -f $(OBJECTS)