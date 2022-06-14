#define SFML
#ifdef SFML
#include <SFML/Graphics.hpp>
#endif

class CaseShape : public sf::RectangleShape
{
public :

    CaseShape(const float lenght = 10,sf::Vector2f pos)   
    {   
        CaseShape::lenght=lenght;
        CaseShape::pos = pos;
        setPosition(pos);
        setFillColor(sf::Color(158, 158, 158));
        update();

    }

    void setLenght(float lenght)
    {
        CaseShape::lenght = lenght;
        update();
    }

    const float getLenght() const
    {
        return lenght;
    }

    


private :

    sf::Vector2f pos;
    float lenght;
};