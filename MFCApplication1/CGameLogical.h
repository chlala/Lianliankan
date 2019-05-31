#pragma once
#include "global.h"
#include<algorithm>
#define CHANGENUM 40
class CGameLogical
{
public:
	Vertex cor1;
	Vertex cor2;
	CGameLogical(){ }
	CGameLogical(int anMap[][COL]);
	void InitMap(int anMap[][COL]);
	bool isLink(int anMap[][COL], Vertex v1, Vertex v2);
	void Clear(int anMap[][COL], Vertex v1, Vertex v2);
	bool lineLink(int anMap[][COL], Vertex v1, Vertex v2);
	void position(int anMap[][COL], Vertex &v1, Vertex &v2);
	bool twoLink(int anMap[][COL], Vertex v1, Vertex v2);
	bool threeLink(int anMap[][COL], Vertex v1, Vertex v2);
	bool xLine(int anMap[][COL], int nCol1, int nCol2, int nRow);
	bool yLine(int anMap[][COL], int nRow1, int nRow2, int nCol);
	bool isBlank(int anMap[][COL]);
	bool findLink(int anMap[][COL], Vertex &v1, Vertex &v2);
	bool findSame(int anMap[][COL], Vertex &v1, Vertex &v2, int k1, int k2);
	void exchange(int anMap[][COL]);
};