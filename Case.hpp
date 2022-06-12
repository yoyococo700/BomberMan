#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>
#include "point.hpp"

#define N 5
namespace CaseAttribut {
	enum CaseType { bombe = 1, vide = 0 };
	enum CaseState { open = 1, closed = 0, flag = 2 };
}

class Case {

public:
	Case();
	Case(point pos, CaseAttribut::CaseType type, bool needToBeOpen=false);
	//~Case();

	CaseAttribut::CaseType getType();
	CaseAttribut::CaseState getCaseState();

	void setCaseType(CaseAttribut::CaseType);
	void setCaseState(CaseAttribut::CaseState state);
	void setCasePos(point pos);

	void flagLogic();
	void openCase();
	bool isNeedToBeOpen();
	bool isCaseABomb();

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
	//~Tableau();

	void updateTab();

	void drawTab();
	void debugBombeTab();
	void debugNbBombeAround();
	int nbBombe();

	

private:


	Case tab[N][N];
	float proba;
	bool change;


	void nbBombeAroundCase(point pos);
	void openNeedToBeOpenCase();

};