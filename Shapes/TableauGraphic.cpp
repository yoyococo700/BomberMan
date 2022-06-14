#define SFML

#include "CaseShape.cpp"
#include "./Case.hpp"

#ifdef SFML
#include <SFML/Graphics.hpp>
#endif

class TableauShape : sf::Drawable
{
public:

    explicit TableauShape(const float lenght = 10, sf::Vector2f pos)
        
    {   
        TableauShape::lenght = lenght;
        TableauShape::pos = pos;


    }

    void setLenght(float lenght)
    {
        TableauShape::lenght = lenght;

    }

    const float getLenght() const
    {
        return lenght;
    }


private:

    sf::Vector2f pos;
    float lenght;
    CaseShape tab[SIZE_TAB][SIZE_TAB];

    void initTabCab() {
        for (int i = 0; i < SIZE_TAB; i++)
        {
            for (int j = 0; j < SIZE_TAB; j++) {
                tab[i][j].setPosition();
                
            }
        }
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(rect, states);
        target.draw(text, states);
    }
};