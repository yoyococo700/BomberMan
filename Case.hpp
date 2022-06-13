#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>
#include "point.hpp"

#define N 15
namespace CaseAttribut {
	enum CaseType { bombe = 1, vide = 0 };
	enum CaseState { open = 1, closed = 0, flag = 2 };
}

class Case {

public:
	Case();
	Case(point pos, CaseAttribut::CaseType type);
	//~Case();

	CaseAttribut::CaseType getType();
	CaseAttribut::CaseState getCaseState();

	void setCaseType(CaseAttribut::CaseType);
	void setCaseState(CaseAttribut::CaseState state);
	void setCasePos(point pos);
	void setCaseNeedToBeOpen(bool condition);

	void flagLogic();
	void openCase();
	bool isNeedToBeOpen();
	bool isCaseABomb();
	bool isCaseABordure();

	void setNbBombeAround(int nb);
	int getNbBombeAround();

private:
	point pos;
	CaseAttribut::CaseState state;
	CaseAttribut::CaseType type;
	int nbBombeAround;
	bool needToBeOpen;
	

	
};

class Tableau {

public:
	Tableau();
	Tableau(int proba);
	Tableau(int proba, int cas);
	//~Tableau();

	void updateTab();

	void clearScreen();

	void drawTab();
	void debugBombeTab();
	void debugNbBombeAround();
	void debugOpener();
	void debugBoundary();
	int nbBombe();

	

private:


	Case tab[N][N];
	float proba;
	bool change;

	std::vector<point> boundary;

	void nbBombeAroundCase(point pos);
	void openNeedToBeOpenCase();
	bool isCaseIsABoundary(point pos);

};