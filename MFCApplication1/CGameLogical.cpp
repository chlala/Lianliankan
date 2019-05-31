#include "stdafx.h"
#include "CGameLogical.h"
#include "CGameDlg.h"

CGameLogical::CGameLogical(int anMap[][COL])
{
	for (int i = 0;i < ROW;i++)
	{
		for (int j = 0;j < COL;j++)
		{
			anMap[i][j] = BLANK;
		}
	}
}

void CGameLogical::InitMap(int anMap[][COL])
{
	int num[ROW] = { 0 };
	srand(time(NULL));
	for (int i = 0;i < ROW;i++)
	{
		for (int j = 0;j < COL;j++)
		{
			int randNum = rand() % ROW;
			if (num[randNum] < COL)
			{
				anMap[i][j] = randNum;
				num[randNum]++;
			}
			else {
				while (true)
				{
					int randNum = rand() % ROW;
					if (num[randNum] < COL)
					{
						anMap[i][j] = randNum;
						num[randNum]++;
						break;
					}
				}
			}
		}
	}
/*	for (int i = 0;i < 10;i++)
	{
		for (int j = 0;j < 16;j++)
		{
			anMap[i][j]=-1;
		}
	}
	anMap[0][4] = 1;
	anMap[2][0] = 5;
	anMap[4][0] = 1;
	anMap[2][1] = 9;
	anMap[3][1] = 7;
	anMap[4][2] = 8;
	anMap[3][1] = 5;
	anMap[5][0] = 9;
	anMap[5][1] = 2;*/
}

bool CGameLogical::isLink(int anMap[][COL], Vertex v1, Vertex v2)
{
	int nRow1 = v1.row;
	int nCol1 = v1.col;
	int nRow2 = v2.row;
	int nCol2 = v2.col;
	if ((anMap[nRow1][nCol1] == anMap[nRow2][nCol2]) &&
		((nRow1 != nRow2) || (nCol1 != nCol2)))
	{
		return true;
	}
	return false;
}

void CGameLogical::Clear(int anMap[][COL], Vertex v1, Vertex v2)
{
	anMap[v1.row][v1.col] = BLANK;
	anMap[v2.row][v2.col] = BLANK;
}

bool CGameLogical::lineLink(int anMap[][COL], Vertex v1, Vertex v2)
{
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	if (nRow1 == nRow2)
	{
		if (nCol1 > nCol2)
		{
			int temp = nCol1;
			nCol1 = nCol2;
			nCol2 = temp;
		}
		while (++nCol1 < nCol2)
		{
			if (anMap[nRow1][nCol1] != BLANK)
			{
				return false;
			}
		}
		return true;
	}
	else if (nCol1 == nCol2)
	{
		if (nRow1 > nRow2)
		{
			int temp = nRow1;
			nRow1 = nRow2;
			nRow2 = temp;
		}
		while (++nRow1 < nRow2)
		{
			if (anMap[nRow1][nCol1] != BLANK)
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

void CGameLogical::position(int anMap[][COL], Vertex &v1, Vertex &v2)
{
	if (v1.col > v2.col)
	{
		Vertex temp = v1;
		v1 = v2;
		v2 = temp;
	}
}

bool CGameLogical::xLine(int anMap[][COL], int nCol1, int nCol2, int nRow)
{
	for (int i = nCol1 + 1;i < nCol2;i++)
	{
		if (anMap[nRow][i] != BLANK) {
			return false;
		}
	}
	return true;
}

bool CGameLogical::yLine(int anMap[][COL], int nRow1, int nRow2, int nCol)
{
	for (int i = nRow1 + 1;i < nRow2;i++)
	{
		if (anMap[i][nCol] != BLANK) {
			return false;
		}
	}
	return true;
}

bool CGameLogical::twoLink(int anMap[][COL], Vertex v1, Vertex v2)
{	
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	int i = 0;
	if (xLine(anMap, nCol1, nCol2, nRow1) == true)
	{
		if (nRow1 > nRow2)
		{
			if (yLine(anMap, nRow2, nRow1, nCol2) == true && anMap[nRow1][nCol2] == BLANK) {
				cor1.row = v1.row;
				cor1.col = v2.col;
				return true;
			}
		}
		else
		{
			if (yLine(anMap, nRow1, nRow2, nCol2) == true && anMap[nRow1][nCol2] == BLANK)
			{
				cor1.row = v1.row;
				cor1.col = v2.col;
				return true;
			}
		}
	}
	if (nRow1 > nRow2)
	{
		if (yLine(anMap, nRow2, nRow1, nCol1) && xLine(anMap,nCol1, nCol2, nRow2) 
			&& anMap[nRow2][nCol1] == BLANK)
		{
			cor1.row = v2.row;
			cor1.col = v1.col;
			return true;
		}
	}
	else
	{
		if (yLine(anMap, nRow1, nRow2, nCol1) && xLine(anMap, nCol1, nCol2, nRow2) 
			&& anMap[nRow2][nCol1] == BLANK)
		{
			cor1.row = v2.row;
			cor1.col = v1.col;
			return true;
		}
	}
	return false;
}

bool CGameLogical::threeLink(int anMap[][COL], Vertex v1, Vertex v2)
{
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	//同一行
	if (nRow1 == nRow2)
	{
		//   |------|
		//   |      |
		if (nRow1 - 1 >= 0 && anMap[nRow1 - 1][nCol1] == BLANK)
		{
			for (int i = nRow1 - 1;i >=0; i--)
			{
				if (anMap[i][nCol1] == BLANK)
				{
					if (xLine(anMap, nCol1, nCol2, i) && yLine(anMap, i, nRow1, nCol2)
						&& anMap[i][nCol1] == BLANK && anMap[i][nCol2] == BLANK)
					{
						cor1.row = i;
						cor1.col = nCol1;
						cor2.row = i;
						cor2.col = nCol2;
						return true;
					}
				}
				else
				{
					break;
				}
			}
		}
		//   |      |
		//   |______|
		else if (nRow1 + 1 < 16 && anMap[nRow1 + 1][nCol1] == BLANK)
		{
			for (int i = nRow1 + 1;i < COL; i++)
			{
				if (anMap[i][nCol1] == BLANK)
				{
					if (xLine(anMap, nCol1, nCol2, i) && yLine(anMap, nRow1, i, nCol2)
						&& anMap[i][nCol1] == BLANK && anMap[i][nCol2] == BLANK)
					{
						cor1.row = i;
						cor1.col = nCol1;
						cor2.row = i;
						cor2.col = nCol2;
						return true;
					}
				}
				else
				{
					break;
				}
			}
		}
	}
	//同一列
	else if (nCol1 == nCol2)
	{
		if (nRow1 > nRow2)
		{
			int temp = nRow1;
			nRow1 = nRow2;
			nRow2 = temp;
		}
		// |----
		// |
		// |----
		if (nCol1 - 1 >= 0 && anMap[nRow1][nCol1 - 1] == BLANK)
		{
			for (int i = nCol1 - 1;i >= 0; i--)
			{
				if (anMap[nRow1][i] == BLANK)
				{
					if (yLine(anMap, nRow1, nRow2, i) && xLine(anMap, i, nCol1, nRow2)
						&& anMap[nRow1][i] == BLANK && anMap[nRow2][i] == BLANK)
					{
						cor1.row = nRow1;
						cor1.col = i;
						cor2.row = nRow2;
						cor2.col = i;
						return true;
					}
				}
				else
				{
					break;
				}
			}
		}
		//  ---|
		//     |
		//  ---|
		else if (nCol1 + 1 < COL && anMap[nRow1][nCol1 + 1] == BLANK)
		{
			for (int i = nCol1 + 1;i < COL; i++)
			{
				if (anMap[nRow1][i] == BLANK)
				{
					if (yLine(anMap, nRow1, nRow2, i) && xLine(anMap, nCol1, i, nRow2)
						&& anMap[nRow1][i] == BLANK && anMap[nRow2][i] == BLANK)
					{
						cor1.row = nRow1;
						cor1.col = i;
						cor2.row = nRow2;
						cor2.col = i;
						return true;
					}
				}
				else
				{
					break;
				}
			}
		}
	}
	//左上角 右下角
	else if (nRow1 < nRow2)
	{
		if (anMap[nRow1 + 1][nCol1] == BLANK)
		{
			//   |
			//   ----
			//       |
			for (int i = nRow1 + 1;i < nRow2;i++)
			{
				if (anMap[i][nCol1] == BLANK)
				{
					if (xLine(anMap, nCol1, nCol2, i)
						&& yLine(anMap, i, nRow2, nCol2) && anMap[i][nCol2] == BLANK)
					{
						cor1.row = i;
						cor1.col = nCol1;
						cor2.row = i;
						cor2.col = nCol2;
						return true;
					}
				}
				else
				{
					break;
				}
			}
			//  |
			//  |   |
			//  ----    
			if (yLine(anMap, nRow1, nRow2, nCol1) && anMap[nRow2][nCol1] == BLANK)
			{
				for (int i = nRow2 + 1;i < COL;i++)
				{
					if (anMap[i][nCol1] == BLANK)
					{
						if (xLine(anMap, nCol1, nCol2, i)
							&& yLine(anMap, nRow2, i, nCol2) && anMap[i][nCol2] == BLANK)
						{
							cor1.row = i;
							cor1.col = nCol1;
							cor2.row = i;
							cor2.col = nCol2;
							return true;
						}
					}
					else
					{
						break;
					}
				}
			}
		}
		if (anMap[nRow1][nCol1 + 1] == BLANK)
		{
			//  ------ 
			//       |
			//       -------
			for (int i = nCol1 + 1;i < nCol2;i++)
			{
				if (anMap[nRow1][i] == BLANK)
				{
					if (yLine(anMap, nRow1, nRow2, i)
						&& xLine(anMap, i, nCol2, nRow2) && anMap[nRow2][i] == BLANK)
					{
						cor1.row = nRow1;
						cor1.col = i;
						cor2.row = nRow2;
						cor2.col = i;
						return true;
					}
				}
				else
				{
					break;
				}
			}
			//  --------
			//          |
			//      ----
			if (xLine(anMap, nCol1, nCol2, nRow1) && anMap[nRow1][nCol2] == BLANK)
			{
				for (int i = nCol2 + 1;i < COL;i++)
				{
					if (anMap[nRow1][i] == BLANK)
					{
						if (yLine(anMap, nRow1, nRow2, i)
							&& xLine(anMap, nCol2, i, nRow2) && anMap[nRow2][i] == BLANK)
						{
							cor1.row = nRow1;
							cor1.col = i;
							cor2.row = nRow2;
							cor2.col = i;
							return true;
						}
					}
					else
					{
						break;
					}
				}
			}
		}
		//  ---
		// |
		//  ---------
		if (nCol1 - 1 >= 0 && anMap[nRow1][nCol1 - 1] == BLANK)
		{
			for (int i = nCol1 - 1;i >= 0;i--)
			{
				if (anMap[nRow1][i] == BLANK)
				{
					if (yLine(anMap, nRow1, nRow2, i)
						&& xLine(anMap, i, nCol2, nRow2) && anMap[nRow2][i] == BLANK)
					{
						cor1.row = nRow1;
						cor1.col = i;
						cor2.row = nRow2;
						cor2.col = i;
						return true;
					}
				}
				else
				{
					break;
				}
			}
		}
		//   |----
		//   |    |
		//        |
		if (nRow1 - 1 >= 0 && anMap[nRow1 - 1][nCol1] == BLANK)
		{
			for (int i = nRow1 - 1;i >= 0;i--)
			{
				if (anMap[i][nCol1] == BLANK)
				{
					if (xLine(anMap, nCol1, nCol2, i)
						&& yLine(anMap, i, nRow2, nCol2) && anMap[i][nCol2] == BLANK)
					{
						cor1.row = i;
						cor1.col = nCol1;
						cor2.row = i;
						cor2.col = nCol2;
						return true;
					}
				}
				else
				{
					break;
				}
			}
		}
	}
	//左下角 右上角
	else
	{
		if (anMap[nRow1 - 1][nCol1] == BLANK)
		{
			//         |
			//   -------
			//   |
			for (int i = nRow1 - 1;i > nRow2;i--)
			{
				if (anMap[i][nCol1] == BLANK)
				{
					if (xLine(anMap, nCol1, nCol2, i) && yLine(anMap, nRow2, i, nCol2)
						&& anMap[i][nCol2] == BLANK)
					{
						cor1.row = i;
						cor1.col = nCol1;
						cor2.row = i;
						cor2.col = nCol2;
						return true;
					}
				}
				else
				{
					break;
				}
			}
			//   -----
			//   |    |
			//   |
			if (yLine(anMap, nRow2, nRow1, nCol1) && anMap[nRow2][nCol1] == BLANK)
			{
				for (int i = nRow2 - 1;i >= 0;i--)
				{
					if (anMap[i][nCol1] == BLANK)
					{
						if (xLine(anMap, nCol1, nCol2, i)
							&& yLine(anMap, i, nRow2, nCol2) && anMap[i][nCol2] == BLANK)
						{
							cor1.row = i;
							cor1.col = nCol1;
							cor2.row = i;
							cor2.col = nCol2;
							return true;
						}
					}
					else
					{
						break;
					}
				}
			}
		}
		if (anMap[nRow1][nCol1 + 1] == BLANK)
		{
			//        ----
			//        |
			//     ----
			for (int i = nCol1 + 1;i < nCol2;i++)
			{
				if (anMap[nRow1][i] == BLANK)
				{
					if (yLine(anMap, nRow2, nRow1, i)
						&& xLine(anMap, i, nCol2, nRow2) && (anMap[nRow2][i] == BLANK))
					{
						cor1.row = nRow1;
						cor1.col = i;
						cor2.row = nRow2;
						cor2.col = i;
						return true;
					}
				}
				else
				{
					break;
				}
			}
			//            ----
			//                |
			//      -----------
			if (xLine(anMap, nCol1, nCol2, nRow1) && anMap[nRow1][nCol2] == BLANK)
			{
				for (int i = nCol2 + 1;i < COL;i++)
				{
					if (anMap[nRow1][i] == BLANK)
					{
						if (yLine(anMap, nRow2, nRow1, i)
							&& xLine(anMap, nCol2, i, nRow2) && anMap[nRow2][i] == BLANK)
						{
							cor1.row = nRow1;
							cor1.col = i;
							cor2.row = nRow2;
							cor2.col = i;
							return true;
						}
					}
					else
					{
						break;
					}
				}
			}
		}
		//  ---------
		//  |
		//  ----
		if (nCol1 - 1 >= 0 && anMap[nRow1][nCol1 - 1] == BLANK)
		{
			for (int i = nCol1 - 1;i >= 0;i--)
			{
				if (anMap[nRow1][i] == BLANK)
				{
					if (yLine(anMap, nRow2, nRow1, i)
						&& xLine(anMap, i, nCol2, nRow2) && anMap[nRow2][i] == BLANK)
					{
						cor1.row = nRow1;
						cor1.col = i;
						cor2.row = nRow2;
						cor2.col = i;
						return true;
					}
				}
				else
				{
					break;
				}
			}
		}
		//      |
		//      |
		//  |___|
		if (nRow1 + 1 < 16 && anMap[nRow1 + 1][nCol1] == BLANK)
		{
			for (int i = nRow1 + 1;i < COL;i++)
			{
				if (anMap[i][nCol1] == BLANK)
				{
					if (xLine(anMap, nCol1, nCol2, i)
						&& yLine(anMap, nRow2, i, nCol2) && anMap[i][nCol2] == BLANK)
					{
						cor1.row = i;
						cor1.col = nCol1;
						cor2.row = i;
						cor2.col = nCol2;
						return true;
					}
				}
				else
				{
					break;
				}
			}
		}
	}
	return false;
}

bool CGameLogical::isBlank(int anMap[][COL])
{
	for (int i = 0;i < ROW;i++)
	{
		for (int j = 0;j < COL;j++)
		{
			if (anMap[i][j] != BLANK)
			{
				return false;
			}
		}
	}
	return true;
}

bool CGameLogical::findLink(int anMap[][COL], Vertex &v1, Vertex &v2)
{
  	for (int i = 0;i < ROW;i++)
	{
		for (int j = 0;j < COL;j++)
		{
			if (anMap[i][j] != BLANK)
			{
				v1.row = i;
				v1.col = j;
				int k1 = i;
				int k2 = j;
				while (findSame(anMap, v1, v2, k1, k2))
				{
					if (v1.col > v2.col)
					{
						if (lineLink(anMap, v1, v2) || twoLink(anMap, v2, v1) 
							|| threeLink(anMap, v2, v1))
						{
							return true;
						}
					}
					else
					{
						if (lineLink(anMap, v1, v2) || twoLink(anMap, v1, v2)
							|| threeLink(anMap, v1, v2))
						{
							return true;
						}
					}
					k1 = v2.row;
					k2 = v2.col;
				}
			}
		}
	}
	return false;
}

bool CGameLogical::findSame(int anMap[][COL], Vertex &v1, Vertex &v2, int k1, int k2)
{
	for (int i = k1;i < ROW;i++)
	{
		int j = 0;
		if (i == k1)
		{
			j = k2 + 1;
		}
		for (;j < COL;j++)
		{
			if (anMap[i][j] == anMap[v1.row][v1.col])
			{
				v2.row = i;
				v2.col = j;
				return true;
			}
		}
	}
	return false;
}

void CGameLogical::exchange(int anMap[][COL])
{
	srand(time(NULL));
	for (int k = 0; k < CHANGENUM; k++)
	{
		int row1 = rand() % ROW;
		int col1 = rand() % COL;
		int row2 = rand() % ROW;
		int col2 = rand() % COL;
		if (row1 != row2 || col1 != col2)
		{
			int t = anMap[row1][col1];
			anMap[row1][col1] = anMap[row2][col2];
			anMap[row2][col2] = t;
		}
	}
}
