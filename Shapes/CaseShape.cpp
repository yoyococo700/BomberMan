#define SFML
#ifdef SFML
#include <SFML/Graphics.hpp>
#endif

#include "../Case.hpp"

class CaseShape : public sf::RectangleShape
{
public :

    CaseShape(const float lenght = 10,sf::Vector2f pos = sf::Vector2f(0,0))   
    {   
        CaseShape::lenght=lenght;
        CaseShape::pos = pos;
        setSize(sf::Vector2f(lenght, lenght));
        setPosition(pos);
        setFillColor(sf::Color(158, 158, 158));
        update();

    }

    void setLenght(float lenght)
    {
        CaseShape::lenght = lenght;
        setSize(sf::Vector2f(lenght, lenght));
        update();
    }

    void setCaseShapeState (CaseAttribut::CaseState state) {
        CaseShape::state = state;
        if (state == CaseAttribut::closed)
        {
            setFillColor(sf::Color(158, 158, 158));
            
        }
        else if (state== CaseAttribut::open)
        {
            setFillColor(sf::Color::Black);
            
        }
        else
        {
            setFillColor(sf::Color::Red);
            
        }
        update();
    }

    CaseAttribut::CaseState getCaseShapeState() {
       return CaseShape::state ;
    }

    const float getLenght() const
    {
        return lenght;
    }

    


private :

    sf::Vector2f pos;
    float lenght;
    CaseAttribut::CaseState state;
};