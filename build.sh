g++ -c v1.cpp
g++ -c point.cpp
g++ -c Case.cpp
g++ -c Shapes/CaseShape.cpp
g++ -c Shapes/TableauGraphic.cpp
g++ v1.o  point.o Case.o Shapes/TableauGraphic.o Shapes/CaseShape.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
./sfml-app

