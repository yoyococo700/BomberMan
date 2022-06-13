
#include "Case.hpp"
#include "point.hpp"

CaseAttribut::CaseType TypeRandom(float proba) {	
	return CaseAttribut::CaseType(rand() % 100 > proba);
}




Case::Case() {

}

Case::Case(point pos, CaseAttribut::CaseType type) {
	Case::type = type;
	Case::state = CaseAttribut::closed();
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
	return (pos.x==0 || pos.x==N-1 || pos.y == 0 || pos.y == N - 1 );
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
	int i=N/2+3;
	int j = N / 2 + 3;
	boundary.push_back(point(i, j));
	for (int m = 0; m<boundary.size();m++)
	{	
		std::vector<point>::iterator pos = std::next(boundary.begin(), boundary.size()-m-1);
		for (int k = pos->x - 1; k <= pos->x + 1; k++)
		{
			for (int l = pos->y - 1; l <= pos->y + 1; l++) {
				if (!tab[k][l].isCaseABomb() && !tab[k][l].isNeedToBeOpen() && !tab[k][l].isCaseABordure()) {
					tab[k][l].setCaseNeedToBeOpen(true);
					if (!isCaseIsABoundary(point(k, l))) {
						boundary.push_back(point(k, l));
						pos = std::next(boundary.begin(), m=0);
					}
				}
				//debugOpener();
				//clearScreen();
				//debugBoundary();
			}
		}
	}
	
}

void Tableau::clearScreen() {
	system("cls");
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

void Tableau::debugOpener()
{
	std::cout << "--------------------------------------\n";
	std::cout << "Debug de l'ouverture des case\n";
	std::cout << "--------------------------------------\n";
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++) {
			
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
	for (point pos : boundary) {
		pos.printPoint();
	}
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

bool Tableau::isCaseIsABoundary(point pos)
{
	return (tab[pos.x][pos.y].getNbBombeAround() != 0);
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
	tab[N / 2][N / 2 + 1].setCaseNeedToBeOpen(true);

}


Tableau::Tableau(int nbBombe,int cas) {
	CaseAttribut::CaseType type;
	point posVec;
	int i, j;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++) {
			tab[i][j].setCaseState(CaseAttribut::closed);
			tab[i][j].setCaseType(CaseAttribut::vide);
			tab[i][j].setCasePos(point(i,j));
		}
	}

	for (int ib = 0; ib < nbBombe; ib++)
	{
		i = rand() % N;
		j = rand() % N;
		if (!tab[i][j].isCaseABomb())
		{
			tab[i][j].setCaseType(CaseAttribut::bombe);
			for (int k = i-1; k <= i+1; k++)
			{
				for (int l = j - 1; l <= j + 1; l++) {
					if (k>=0 && k<N && l>=0 && l<N && !tab[k][l].isCaseABomb())
					{
						tab[k][l].setNbBombeAround(tab[k][l].getNbBombeAround() + 1);
					}
				}
			}
		}
	}
	
	tab[N / 2][N / 2 + 1].setCaseNeedToBeOpen(true);

}

//Tableau::Tableau(int proba,int cas) {
//	CaseAttribut::CaseType type;
//	point posVec;
//	for (int i = 0; i < N; i++)
//	{
//		for (int j = 0; j < N; j++) {
//			posVec.x = i;
//			posVec.y = j;
//			tab[i][j].setCaseType(CaseAttribut::vide);
//			tab[i][j].setCaseState(CaseAttribut::closed);
//			tab[i][j].setCasePos(posVec);
//		}
//	}
//	int k = N/2;
//	int l = N/2+1;
//	int m = 6;
//	for (int i = 0; i <=m ; i++)
//	{
//		tab[k][l + i].setCaseType(CaseAttribut::bombe);
//		tab[k+i][l].setCaseType(CaseAttribut::bombe);
//		tab[k+i][l + m].setCaseType(CaseAttribut::bombe);
//		tab[k + m][l+i].setCaseType(CaseAttribut::bombe);
//	}
//
//	for (int i = 0; i < N; i++)
//	{
//		for (int j = 0; j < N; j++) {
//			nbBombeAroundCase(point(i, j));
//		}
//	}
//	tab[N / 2][N / 2 + 1].setCaseNeedToBeOpen(true);
//
//}
