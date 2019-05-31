#pragma once
#include "global.h"
#include "CGameLogical.h"

class CGameControl
{
public:
	int m_anMap[10][16];
	Vertex cor1;
	Vertex cor2;
	Vertex m_ptSelFirst;
	Vertex m_ptSelSec;
	CGameControl();
	void StartGame();
	int getElement(int nRow, int nCol);
	void setFirstPoint(int nRow, int nCol);
	void setSecPoint(int nRow, int nCol);
	bool Link();
	void clear();
	bool isCanLink();
	bool canWin();
	bool findLink(Vertex &v1, Vertex &v2);
	void exchange();
};