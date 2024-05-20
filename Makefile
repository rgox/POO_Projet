# Nom des fichiers exécutables
TARGET = RobotArena
TEST_TARGET = TestSuite

# Compilateur C++
CXX = g++

# Options de compilation
CXXFLAGS = -std=c++11 -Wall -g

# Liens vers les bibliothèques de SFML et Boost.Test
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
BOOST_LIBS = -lboost_unit_test_framework

# Fichiers sources pour l'application principale
APP_SOURCES = affichage.cpp arene.cpp Course.cpp geometry.cpp Init.cpp Projectile.cpp Robot.cpp Sniper.cpp Tank.cpp main_app.cpp

# Fichiers sources pour les tests
TEST_SOURCES = Test.cpp main_test.cpp affichage.cpp arene.cpp Course.cpp geometry.cpp Init.cpp Projectile.cpp Robot.cpp Sniper.cpp Tank.cpp

# Fichiers objets pour l'application principale
APP_OBJECTS = $(APP_SOURCES:.cpp=.o)

# Fichiers objets pour les tests
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

# Règle par défaut pour créer les exécutables
all: $(TARGET) $(TEST_TARGET)

# Lier les fichiers objets pour créer l'exécutable principal
$(TARGET): $(APP_OBJECTS)
	$(CXX) $(APP_OBJECTS) -o $@ $(SFML_LIBS)

# Lier les fichiers objets pour créer l'exécutable de tests
$(TEST_TARGET): $(TEST_OBJECTS)
	$(CXX) $(TEST_OBJECTS) -o $@ $(SFML_LIBS) $(BOOST_LIBS)

# Compilation des fichiers source en fichiers objets
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage des fichiers compilés
clean:
	rm -f *.o $(TARGET) $(TEST_TARGET)

# Exécution de l'application principale
start: $(TARGET)
	./$(TARGET)

# Exécution des tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

.PHONY: all clean start test
