
#include "Case.hpp"
#include "point.hpp"

CaseAttribut::CaseType TypeRandom(float proba) {	
	return CaseAttribut::CaseType(rand() % 100 > proba);
}




Case::Case() {

}

Case::Case(point pos, CaseAttribut::CaseType type, bool needToBeOpen) {
	Case::type = type;
	Case::state = CaseAttribut::closed;
	Case::pos = pos;
	Case::needToBeOpen = needToBeOpen;
	Case::nbBombeAround = 0;
}

void Case::setCaseType(CaseAttribut::CaseType type) {
	Case::type = type;
}

void Case::setCaseState(CaseAttribut::CaseState state)
{
	Case::state = state;
}

void Case::setCasePos(point pos)
{
	Case::pos = pos;
}

void Case::flagLogic()
{
	if (getCaseState() == CaseAttribut::flag) {
		setCaseState(CaseAttribut::closed);
	}
	else if (getCaseState() == CaseAttribut::closed)
	{
		setCaseState(CaseAttribut::flag);
	}
}

void Case::openCase()
{	
	if (getType()!=CaseAttribut::bombe)
	{
		setCaseState(CaseAttribut::open);
	}
	
}

bool Case::isNeedToBeOpen()
{
	return Case::needToBeOpen;
}

bool Case::isCaseABomb()
{
    return (Case::getType()==CaseAttribut::bombe);
}

void Case::setNbBombeAround(int nb)
{
    Case::nbBombeAround = nb;
}

int Case::getNbBombeAround()
{
	return Case::nbBombeAround;
}

CaseAttribut::CaseType Case::getType() {
	return Case::type;
}

CaseAttribut::CaseState Case::getCaseState()
{
	return state;
}

void Tableau::updateTab()
{
	if (change) {
		change = false;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++) {
				
			}
		}
	}

}

void Tableau::drawTab()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++) {
			if (tab[i][j].getType() == CaseAttribut::flag)
				std::cout << "F";
			else
				std::cout << "x";
		}
		std::cout << "\n";
	}
}

void Tableau::debugBombeTab() {
	std::cout << "--------------------------------------\n";
	std::cout << "Debug des des bombes sur les pos\n";
	std::cout << "--------------------------------------\n";
	for (int i = 0; i <N; i++)
	{
		for (int j = 0; j < N; j++) {
			if (tab[i][j].getType() == CaseAttribut::CaseType::bombe)
				std::cout << "B";
			else
				std::cout << " ";
		}
		std::cout << "\n";
	}
	std::cout << "--------------------------------------\n";
}

void Tableau::debugNbBombeAround()
{
	std::cout << "--------------------------------------\n";
	std::cout << "Debug du compte des bombes sur les pos\n";
	std::cout << "--------------------------------------\n";
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++) {
			if (tab[i][j].getType() == CaseAttribut::CaseType::bombe)
				std::cout << "B";
			else
				std::cout << tab[i][j].getNbBombeAround();
		}
		std::cout << "\n";
	}
	std::cout << "--------------------------------------\n";
}

int Tableau::nbBombe()
{	
	int somme = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++) {
			if (tab[i][j].getType() == CaseAttribut::bombe)
				somme++;
		}
	}
	return somme;
}

void Tableau::nbBombeAroundCase(point pos)
{
    int somme = 0;
    //Cas des bords
    if (pos.x == 0)
    {
        //Cas en haut a gauche
        if (pos.y == 0)
        {
            somme = tab[pos.x][pos.y + 1].isCaseABomb() + tab[pos.x + 1][pos.y + 1].isCaseABomb() + tab[pos.x + 1][pos.y].isCaseABomb();
            tab[pos.x][pos.y].setNbBombeAround(somme);
            return ;
        }
        //Cas en bas a gauche
        else if (pos.y == N - 1)
        {
            somme = tab[pos.x + 1][pos.y].isCaseABomb() + tab[pos.x + 1][pos.y - 1].isCaseABomb() + tab[pos.x][pos.y - 1].isCaseABomb();
            tab[pos.x][pos.y].setNbBombeAround(somme);
            return;
        }
    }
    else if (pos.x == N - 1)
    {
        if (pos.y == 0)
        {
            somme = tab[pos.x][pos.y + 1].isCaseABomb() + tab[pos.x - 1][pos.y + 1].isCaseABomb() + tab[pos.x - 1][pos.y].isCaseABomb();
            tab[pos.x][pos.y].setNbBombeAround(somme);
            return;
        }
        //Cas en bas a droite
        else if (pos.y == N - 1) {
            somme = tab[pos.x - 1][pos.y].isCaseABomb() + tab[pos.x - 1][pos.y - 1].isCaseABomb() + tab[pos.x][pos.y - 1].isCaseABomb();
            tab[pos.x][pos.y].setNbBombeAround(somme);
            return;
        }
    }
    //Cas a gauche generale
    if (pos.x == 0) {
        for (int i = pos.x; i <= pos.x + 1; i++) {
            for (int j = pos.y - 1; j <= pos.y + 1; j++) {
                somme += tab[i][j].isCaseABomb();
            }
        }
        tab[pos.x][pos.y].setNbBombeAround(somme);
        return;
    }
    //Cas a droite generale
    else if (pos.x == N - 1) {
        for (int i = pos.x - 1; i <= pos.x; i++) {
            for (int j = pos.y - 1; j <= pos.y + 1; j++) {
                somme += tab[i][j].isCaseABomb();
            }
        }
        
        
        tab[pos.x][pos.y].setNbBombeAround(somme);
        return;
    }
    //Cas en haut
    else if (pos.y == 0)
    {
        for (int i = pos.x - 1; i <= pos.x + 1; i++)
        {
            for (int j = pos.y; j <= pos.y + 1; j++)
            {
                somme += tab[i][j].isCaseABomb();
            }
        }
        tab[pos.x][pos.y].setNbBombeAround(somme);
        return;
    }
    //Cas en bas
    else if (pos.y == N - 1)
    {
        for (int i = pos.x - 1; i <= pos.x + 1; i++)
        {
            for (int j = pos.y - 1; j <= pos.y; j++)
            {
                somme += tab[i][j].isCaseABomb();
            }
        }
        tab[pos.x][pos.y].setNbBombeAround(somme);
        return;
    }


    //cas general
    for (int i = pos.x - 1; i <= pos.x + 1; i++) {
        for (int j = pos.y - 1; j <= pos.y + 1; j++) {
            somme += tab[i][j].isCaseABomb();
        }
    }
    tab[pos.x][pos.y].setNbBombeAround(somme);
    return;
}

void Tableau::openNeedToBeOpenCase()
{	
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++) {
			if (tab[i][j].isNeedToBeOpen())
				tab[i][j].openCase();
		}
	}
	
}



Tableau::Tableau() {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++) {
			tab[i][j].setCaseState(CaseAttribut::closed);	
		}
	}

}

Tableau::Tableau(int proba) {
	CaseAttribut::CaseType type;
	point posVec;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++) {
			posVec.x=i;
			posVec.y=j;
			tab[i][j].setCaseType(TypeRandom(proba));
			tab[i][j].setCaseState(CaseAttribut::closed);
			tab[i][j].setCasePos(posVec);
		}
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++) {
			nbBombeAroundCase(point(i, j));
		}
	}

}

