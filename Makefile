# Nom du fichier exécutable
TARGET = RobotArena

# Compilateur C++
CXX = g++

# Options de compilation
CXXFLAGS = -std=c++11 -Wall -g

# Dossiers pour les fichiers source
SRC_DIR = .

# Trouver tous les fichiers source dans le dossier courant
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Fichiers objets, un pour chaque fichier source
OBJECTS = $(SOURCES:.cpp=.o)

# Liens vers les bibliothèques de SFML
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Règle par défaut pour créer l'exécutable
all: $(TARGET) start clean

# Lier les fichiers objets pour créer l'exécutable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(SFML_LIBS)

# Compilation des fichiers source en fichiers objets
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage des fichiers compilés
clean:
	rm -f $(OBJECTS) $(TARGET)
start:
	./RobotArena
.PHONY: all clean
