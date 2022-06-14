#include "Case.hpp"
#define SFML
#ifdef SFML
#include <SFML/Graphics.hpp>
#endif

int main() {
	std::cout << "Debut du programme\n";
	srand((unsigned)time(0));
	Tableau newtab(30);
	newtab.debugBombeTab();
    newtab.debugNbBombeAround();
    newtab.drawTab();
    
    newtab.updateTab();
    newtab.debugOpener();
    
#ifdef SFML
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
#endif // SFML

    
        
    
    return 0;

}