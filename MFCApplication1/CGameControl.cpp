#include "stdafx.h"
#include "CGameControl.h"

CGameControl::CGameControl()
{
	CGameLogical gameLogical(m_anMap);
}

void CGameControl::StartGame()
{
	CGameLogical gameLogical;
	gameLogical.InitMap(m_anMap);
}

int CGameControl::getElement(int nRow, int nCol)
{
	return m_anMap[nRow][nCol];
}

void CGameControl::setFirstPoint(int nRow, int nCol) {
	m_ptSelFirst.row = nRow;
	m_ptSelFirst.col = nCol;
}

void CGameControl::setSecPoint(int nRow, int nCol) {
	m_ptSelSec.row = nRow;
	m_ptSelSec.col = nCol;
}

bool CGameControl::Link()
{
	CGameLogical gameLogical;
	if (gameLogical.isLink(m_anMap, m_ptSelFirst, m_ptSelSec) == false)
	{
		return false;
	}
	return true;
}

void  CGameControl::clear()
{
	CGameLogical gameLogical;
	gameLogical.Clear(m_anMap, m_ptSelFirst, m_ptSelSec);
}

bool CGameControl::isCanLink()
{
	CGameLogical gameLogical;
	int i = 0;
	cor1.row = -1;
	cor1.col = -1;
	cor2.row = -1;
	cor2.col = -1;
	if (gameLogical.lineLink(m_anMap, m_ptSelFirst, m_ptSelSec))
	{
		return true;
	}
	gameLogical.position(m_anMap, m_ptSelFirst, m_ptSelSec);
	if (gameLogical.twoLink(m_anMap, m_ptSelFirst, m_ptSelSec))
	{
		cor1 = gameLogical.cor1;
		return true;
	}
	if (gameLogical.threeLink(m_anMap, m_ptSelFirst, m_ptSelSec))
	{
		cor1 = gameLogical.cor1;
		cor2 = gameLogical.cor2;
		return true;
	}
	return false;
}

bool CGameControl::canWin()
{
	CGameLogical gameLogical;
	if (gameLogical.isBlank(m_anMap))
	{
		return true;
	}
	return false;
}

bool  CGameControl::findLink(Vertex &v1, Vertex &v2)
{
	CGameLogical gameLogical;
	if (gameLogical.findLink(m_anMap, v1, v2))
	{
		return true;
	}
	return false;
}

void CGameControl::exchange()
{
	CGameLogical gameLogical;
	gameLogical.exchange(m_anMap);
}