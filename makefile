CC = g++
CFLAGS = -Wall -Wextra -std=c++17
TARGET = trajets
OBJS = main.o Trajet.o TrajetSimple.o TrajetCompose.o Catalogue.o Graphe.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp Trajet.h TrajetSimple.h TrajetCompose.h Catalogue.h Graphe.h
	$(CC) $(CFLAGS) -c main.cpp

Trajet.o: Trajet.cpp Trajet.h
	$(CC) $(CFLAGS) -c Trajet.cpp

TrajetSimple.o: TrajetSimple.cpp TrajetSimple.h Trajet.h
	$(CC) $(CFLAGS) -c TrajetSimple.cpp

TrajetCompose.o: TrajetCompose.cpp TrajetCompose.h Trajet.h
	$(CC) $(CFLAGS) -c TrajetCompose.cpp

Catalogue.o: Catalogue.cpp Catalogue.h Trajet.h TrajetSimple.h TrajetCompose.h Graphe.h
	$(CC) $(CFLAGS) -c Catalogue.cpp

Graphe.o: Graphe.cpp Graphe.h Trajet.h
	$(CC) $(CFLAGS) -c Graphe.cpp

clean:
	rm -f $(OBJS) $(TARGET)
