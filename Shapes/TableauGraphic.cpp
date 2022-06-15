#define SFML

#include "CaseShape.cpp"
#include "../Case.hpp"

#ifdef SFML
#include <SFML/Graphics.hpp>
#endif

class TableauShape : public sf::Drawable
{
public:

    explicit TableauShape(const float lenght = 800, sf::Vector2f pos= sf::Vector2f())
        
    {   
        TableauShape::lenght = lenght;
        TableauShape::pos = pos;
        ratio = 1;
        intercase = 0;
        initTabCab();

    }

    void setLenght(float lenght)
    {
        TableauShape::lenght = lenght;

    }

    const float getLenght() const
    {
        return lenght;
    }

    
    void updateWithBackEnd(Tableau* tabBack) {

        for (int i = 0; i < SIZE_TAB; i++)
        {
            for (int j = 0; j < SIZE_TAB; j++) {
                tab[i][j].setCaseShapeState(tabBack->getTabCaseState(point(i,j)));
            }
        }
    };

private:

    sf::Vector2f pos;
    //Lenght of the tableau in px
    float lenght;
    
    float ratio;

    //Lenght of the intercase in px
    float intercase;

    CaseShape tab[SIZE_TAB][SIZE_TAB];
    
    
//----------------------------------------Fonctions----------------------------------------//
    void initTabCab() {
        ratio = lenght / SIZE_TAB *1.0;
        
        float CaseLenght = ratio;
        intercase = ratio * 0.01;

        for (int i = 0; i < SIZE_TAB; i++)
        {
            for (int j = 0; j < SIZE_TAB; j++) {
                tab[i][j].setPosition(sf::Vector2f((i*ratio)+pos.x,(j*ratio)+pos.y));
                tab[i][j].setLenght(ratio-2);
            }
        }
    }

    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {   
        sf::RectangleShape background(sf::Vector2f(lenght,lenght));
        background.setFillColor(sf::Color(sf::Color::White));
        background.setPosition(pos);
        target.draw(background, states);

        for (int i = 0; i < SIZE_TAB; i++)
        {
            for (int j = 0; j < SIZE_TAB; j++) {
                target.draw(tab[i][j], states);
            }
        }

    }
};