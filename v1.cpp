#include "Case.hpp"
#include "Shapes/TableauGraphic.cpp"

#define SFML
#ifdef SFML
#include <SFML/Graphics.hpp>
#endif

int main() {
	std::cout << "Debut du programme\n";
	srand((unsigned)time(0));
	Tableau newtab(5);
	newtab.debugBombeTab();
    newtab.debugNbBombeAround();
    newtab.drawTab();
    
    newtab.updateTab();
    newtab.debugOpener();
    
    

    TableauShape tab(800,sf::Vector2f(50,15));
    tab.updateWithBackEnd(&newtab);


#ifdef SFML
    sf::RenderWindow window(sf::VideoMode(1000, 900), "BomberMan!");
   

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear();
        window.draw(tab);
        window.display();
    }
#endif // SFML

    
        
    
    return 0;

}