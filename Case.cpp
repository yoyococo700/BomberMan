
#include "Case.hpp"
#include "point.hpp"
#include <algorithm>

CaseAttribut::CaseType TypeRandom(float proba) {	
	return CaseAttribut::CaseType(rand() % 100 > proba);
}




Case::Case() {

}

Case::Case(point pos, CaseAttribut::CaseType type) {
	Case::type = type;
	Case::state = CaseAttribut::closed;
	Case::pos = pos;
	Case::needToBeOpen = false;
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

void Case::setCaseNeedToBeOpen(bool condition)
{
	Case::needToBeOpen = condition;
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
	return needToBeOpen;
}

bool Case::isCaseABomb()
{
    return (Case::getType()==CaseAttribut::bombe);
}

bool Case::isCaseABordure()
{
	return (pos.x==0 || pos.x==SIZE_TAB-1 || pos.y == 0 || pos.y == SIZE_TAB - 1 );
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
	boundary.clear();
	int i=SIZE_TAB/2+3;
	int j = SIZE_TAB / 2 + 3;
	Tableau::reveal(point(i, j));
	//boundary.push_back(point(i, j));
	//for (int m = 0; m<boundary.size();m++)
	//{	
	//	std::vector<point>::iterator pos = std::next(boundary.begin(), boundary.size()-m-1);
	//	for (int k = pos->x - 1; k <= pos->x + 1; k++)
	//	{
	//		for (int l = pos->y - 1; l <= pos->y + 1; l++) {
	//			if (!tab[k][l].isCaseABomb() && !tab[k][l].isNeedToBeOpen() && !tab[k][l].isCaseABordure()) {
	//				tab[k][l].setCaseNeedToBeOpen(true);
	//				if (!isCaseIsABoundary(point(k, l))) {
	//					boundary.push_back(point(k, l));
	//					pos = std::next(boundary.begin(), m=0);
	//				}
	//			}
	//			/*if (nbNeedToBeOpenCaseAround(point(k,l))==9)
	//			{
	//				boundary.erase(pos);
	//			}*/
	//			
	//			//debugOpener();
	//			//clearScreen();
	//			//debugBoundary();
	//		}
	//	}
	//}
	
}

void Tableau::reveal(point pos) {
	
	int a = pos.x;
	int b = pos.y;
	if (pos.inTab(SIZE_TAB))
	{
		if (tab[a][b].isNeedToBeOpen())
			return;
		if (!tab[a][b].isNeedToBeOpen() && !tab[a][b].isCaseABomb())
		{	
			tab[a][b].setCaseNeedToBeOpen(true);
			if (isCaseIsABoundary(pos))
			{
				return;
			}
			for (int i = -1; i <=1; i++)
			{
				for (int j = -1; j <= 1; j++) {
					if (i!=0 || j!=0)
					{
						/*debugOpener();
						clearScreen();*/
						Tableau::reveal(point(a + i, b + j));
						
					}
				}
			}
			
		}
	}
}




void Tableau::clearScreen() {
	system("cls");
}

void Tableau::drawTab()
{
	for (int i = 0; i < SIZE_TAB; i++)
	{
		for (int j = 0; j < SIZE_TAB; j++) {
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
	for (int i = 0; i <SIZE_TAB; i++)
	{
		for (int j = 0; j < SIZE_TAB; j++) {
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
	for (int i = 0; i < SIZE_TAB; i++)
	{
		for (int j = 0; j < SIZE_TAB; j++) {
			if (tab[i][j].getType() == CaseAttribut::CaseType::bombe)
				std::cout << "B";
			else
				std::cout << tab[i][j].getNbBombeAround();
		}
		std::cout << "\n";
	}
	std::cout << "--------------------------------------\n";
}

void Tableau::debugOpener()
{
	std::cout << "--------------------------------------\n";
	std::cout << "Debug de l'ouverture des case\n";
	std::cout << "--------------------------------------\n";
	for (int i = 0; i < SIZE_TAB; i++)
	{
		for (int j = 0; j < SIZE_TAB; j++) {
			
			if (tab[i][j].isNeedToBeOpen()==true) {
				
				std::cout << int(tab[i][j].getNbBombeAround()>0);
			}
			else if (tab[i][j].isCaseABomb()) {
				std::cout << " ";
			}
			else
			{
				std::cout << " ";
			}
			
		}
		std::cout << "\n";
	}
	std::cout << "--------------------------------------\n";
}

void Tableau::debugBoundary() {

	for (int i = 0; i < SIZE_TAB; i++)
	{
		for (int j = 0; j < SIZE_TAB; j++) {
			std::vector<point>::iterator it = std::find(boundary.begin(), boundary.end(), point(i, j));
			if ( it != boundary.end() ) {

				std::cout << "1";
			}
			
			else
			{
				std::cout << " ";
			}
		}
		std::cout << "\n";
	}
	std::cout << boundary.size();
	std::cout << "\n";
}

int Tableau::nbBombe()
{	
	int somme = 0;
	for (int i = 0; i < SIZE_TAB; i++)
	{
		for (int j = 0; j < SIZE_TAB; j++) {
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
        else if (pos.y == SIZE_TAB - 1)
        {
            somme = tab[pos.x + 1][pos.y].isCaseABomb() + tab[pos.x + 1][pos.y - 1].isCaseABomb() + tab[pos.x][pos.y - 1].isCaseABomb();
            tab[pos.x][pos.y].setNbBombeAround(somme);
            return;
        }
    }
    else if (pos.x == SIZE_TAB - 1)
    {
        if (pos.y == 0)
        {
            somme = tab[pos.x][pos.y + 1].isCaseABomb() + tab[pos.x - 1][pos.y + 1].isCaseABomb() + tab[pos.x - 1][pos.y].isCaseABomb();
            tab[pos.x][pos.y].setNbBombeAround(somme);
            return;
        }
        //Cas en bas a droite
        else if (pos.y == SIZE_TAB - 1) {
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
    else if (pos.x == SIZE_TAB - 1) {
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
    else if (pos.y == SIZE_TAB - 1)
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
	for (int i = 0; i < SIZE_TAB; i++)
	{
		for (int j = 0; j < SIZE_TAB; j++) {
			if (tab[i][j].isNeedToBeOpen())
				tab[i][j].openCase();
		}
	}
	
}

int Tableau::nbNeedToBeOpenCaseAround(point pos)
{
	int somme = 0;
	//Cas des bords
	if (pos.x == 0)
	{
		//Cas en haut a gauche
		if (pos.y == 0)
		{
			somme = tab[pos.x][pos.y + 1].isNeedToBeOpen() + tab[pos.x + 1][pos.y + 1].isNeedToBeOpen() + tab[pos.x + 1][pos.y].isNeedToBeOpen();
			
			return somme;
		}
		//Cas en bas a gauche
		else if (pos.y == SIZE_TAB - 1)
		{
			somme = tab[pos.x + 1][pos.y].isNeedToBeOpen() + tab[pos.x + 1][pos.y - 1].isNeedToBeOpen() + tab[pos.x][pos.y - 1].isNeedToBeOpen();
			
			return somme;
		}
	}
	else if (pos.x == SIZE_TAB - 1)
	{
		if (pos.y == 0)
		{
			somme = tab[pos.x][pos.y + 1].isNeedToBeOpen() + tab[pos.x - 1][pos.y + 1].isNeedToBeOpen() + tab[pos.x - 1][pos.y].isNeedToBeOpen();
			tab[pos.x][pos.y].setNbBombeAround(somme);
			return somme;
		}
		//Cas en bas a droite
		else if (pos.y == SIZE_TAB - 1) {
			somme = tab[pos.x - 1][pos.y].isNeedToBeOpen() + tab[pos.x - 1][pos.y - 1].isNeedToBeOpen() + tab[pos.x][pos.y - 1].isNeedToBeOpen();
			
			return somme;
		}
	}
	//Cas a gauche generale
	if (pos.x == 0) {
		for (int i = pos.x; i <= pos.x + 1; i++) {
			for (int j = pos.y - 1; j <= pos.y + 1; j++) {
				somme += tab[i][j].isNeedToBeOpen();
			}
		}
		
		return somme;
	}
	//Cas a droite generale
	else if (pos.x == SIZE_TAB - 1) {
		for (int i = pos.x - 1; i <= pos.x; i++) {
			for (int j = pos.y - 1; j <= pos.y + 1; j++) {
				somme += tab[i][j].isNeedToBeOpen();
			}
		}


		
		return somme;
	}
	//Cas en haut
	else if (pos.y == 0)
	{
		for (int i = pos.x - 1; i <= pos.x + 1; i++)
		{
			for (int j = pos.y; j <= pos.y + 1; j++)
			{
				somme += tab[i][j].isNeedToBeOpen();
			}
		}
		
		return somme;
	}
	//Cas en bas
	else if (pos.y == SIZE_TAB - 1)
	{
		for (int i = pos.x - 1; i <= pos.x + 1; i++)
		{
			for (int j = pos.y - 1; j <= pos.y; j++)
			{
				somme += tab[i][j].isNeedToBeOpen();
			}
		}
		
		return somme;
	}


	//cas general
	for (int i = pos.x - 1; i <= pos.x + 1; i++) {
		for (int j = pos.y - 1; j <= pos.y + 1; j++) {
			somme += tab[i][j].isNeedToBeOpen();
		}
	}
	
	return somme;
}



bool Tableau::isCaseIsABoundary(point pos)
{
	return (tab[pos.x][pos.y].getNbBombeAround() != 0);
}



Tableau::Tableau() {
	for (int i = 0; i < SIZE_TAB; i++)
	{
		for (int j = 0; j < SIZE_TAB
			; j++) {
			tab[i][j].setCaseState(CaseAttribut::closed);	
		}
	}

}

//Tableau::Tableau(int proba) {
//	CaseAttribut::CaseType type;
//	point posVec;
//	for (int i = 0; i < SIZE_TAB; i++)
//	{
//		for (int j = 0; j < SIZE_TAB; j++) {
//			posVec.x=i;
//			posVec.y=j;
//			tab[i][j].setCaseType(TypeRandom(proba));
//			tab[i][j].setCaseState(CaseAttribut::closed);
//			tab[i][j].setCasePos(posVec);
//		}
//	}
//	for (int i = 0; i < SIZE_TAB; i++)
//	{
//		for (int j = 0; j < SIZE_TAB; j++) {
//			nbBombeAroundCase(point(i, j));
//			
//		}
//	}
//	tab[SIZE_TAB / 2][SIZE_TAB / 2 + 1].setCaseNeedToBeOpen(true);
//
//}


Tableau::Tableau(int nbBombe) {
	CaseAttribut::CaseType type;
	point posVec;
	int i, j;
	Tableau::change = false;
	Tableau::proba = 0;


	for (int i = 0; i < SIZE_TAB; i++)
	{
		for (int j = 0; j < SIZE_TAB; j++) {
			tab[i][j].setCaseState(CaseAttribut::closed);
			tab[i][j].setCaseType(CaseAttribut::vide);
			tab[i][j].setCasePos(point(i,j));
			tab[i][j].setNbBombeAround(0);
		}
	}

	for (int ib = 0; ib < nbBombe; ib++)
	{
		i = rand() % SIZE_TAB;
		j = rand() % SIZE_TAB;
		if (!tab[i][j].isNeedToBeOpen())
		{
			tab[i][j].setCaseType(CaseAttribut::bombe);
			for (int k = i-1; k <= i+1; k++)
			{
				for (int l = j - 1; l <= j + 1; l++) {
					if (k>=0 && k<SIZE_TAB && l>=0 && l<SIZE_TAB && !tab[k][l].isNeedToBeOpen())
					{
						tab[k][l].setNbBombeAround(tab[k][l].getNbBombeAround() + 1);
					}
				}
			}
		}
	}
	
	tab[SIZE_TAB / 2][SIZE_TAB / 2 + 1].setCaseNeedToBeOpen(true);

}

//Tableau::Tableau(int proba,int cas) {
//	CaseAttribut::CaseType type;
//	point posVec;
//	for (int i = 0; i < SIZE_TAB; i++)
//	{
//		for (int j = 0; j < SIZE_TAB; j++) {
//			posVec.x = i;
//			posVec.y = j;
//			tab[i][j].setCaseType(CaseAttribut::vide);
//			tab[i][j].setCaseState(CaseAttribut::closed);
//			tab[i][j].setCasePos(posVec);
//		}
//	}
//	int k = SIZE_TAB/2;
//	int l = SIZE_TAB/2+1;
//	int m = 6;
//	for (int i = 0; i <=m ; i++)
//	{
//		tab[k][l + i].setCaseType(CaseAttribut::bombe);
//		tab[k+i][l].setCaseType(CaseAttribut::bombe);
//		tab[k+i][l + m].setCaseType(CaseAttribut::bombe);
//		tab[k + m][l+i].setCaseType(CaseAttribut::bombe);
//	}
//
//	for (int i = 0; i < SIZE_TAB; i++)
//	{
//		for (int j = 0; j < SIZE_TAB; j++) {
//			nbBombeAroundCase(point(i, j));
//		}
//	}
//	tab[SIZE_TAB / 2][SIZE_TAB / 2 + 1].setCaseNeedToBeOpen(true);
//
//}
