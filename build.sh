g++ -c v1.cpp
g++ -c point.cpp
g++ -c Case.cpp
g++ v1.o  point.o Case.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
./sfml-app

