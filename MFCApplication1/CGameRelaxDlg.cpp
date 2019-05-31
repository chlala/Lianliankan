// CGameRelax.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "CGameRelaxDlg.h"
#include "afxdialogex.h"


// CGameRelax 对话框

IMPLEMENT_DYNAMIC(CGameRelaxDlg, CDialogEx)

CGameRelaxDlg::CGameRelaxDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RELAX, pParent)
{
	m_ptGameTop.x = 50;
	m_ptGameTop.y = 50;
	m_sizeElem.cx = 40;
	m_sizeElem.cy = 40;
	m_bFirstPoint = true;
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * 16;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * 10;
}

CGameRelaxDlg::~CGameRelaxDlg()
{
}

void CGameRelaxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_START2, m_start);
	DDX_Control(pDX, IDC_PAUSE, m_pause);
	DDX_Control(pDX, IDC_TIP, m_tip);
	DDX_Control(pDX, IDC_RESET2, m_reset);
	DDX_Control(pDX, IDC_TOOL, m_tool);
	DDX_Control(pDX, IDC_INTETEXT, m_inteText);
	DDX_Control(pDX, IDC_INTENUM, m_inteNum);
	DDX_Control(pDX, IDC_TOOLTEXT, m_toolText);
	DDX_Control(pDX, IDC_TOOLNUM, m_toolNum);
}


BEGIN_MESSAGE_MAP(CGameRelaxDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_START2, &CGameRelaxDlg::OnBnClickedStart2)
	ON_BN_CLICKED(IDC_PAUSE, &CGameRelaxDlg::OnBnClickedPause)
	ON_BN_CLICKED(IDC_TIP, &CGameRelaxDlg::OnBnClickedTip)
	ON_BN_CLICKED(IDC_RESET2, &CGameRelaxDlg::OnBnClickedReset2)
	ON_BN_CLICKED(IDC_TOOL, &CGameRelaxDlg::OnBnClickedTool)
	ON_BN_CLICKED(IDC_SETTING, &CGameRelaxDlg::OnBnClickedSetting)
	ON_BN_CLICKED(IDC_HELP, &CGameRelaxDlg::OnBnClickedHelp)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CGameRelax 消息处理程序



BOOL CGameRelaxDlg::OnInitDialog()
{
	HICON m_hIcon;
	m_hIcon = AfxGetApp()->LoadIcon(IDI_LLK);
	SetIcon(m_hIcon, true);
	CDialogEx::OnInitDialog();
	InitBackground();
	InitElement();
	m_reset.EnableWindow(0);
	m_pause.EnableWindow(0);
	m_tip.EnableWindow(0);
	m_tool.EnableWindow(0);
	return true;
}


void CGameRelaxDlg::InitBackground()
{
	HANDLE bmp = ::LoadImage(NULL, _T("theme\\picture\\fruit_bg.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	CClientDC dc(this);
	m_dcBG.CreateCompatibleDC(&dc);
	m_dcBG.SelectObject(bmp);

	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	m_dcMem.SelectObject(&bmpMem);
	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);
}

void CGameRelaxDlg::InitElement()
{
	CClientDC dc(this);
	HANDLE hBmpBG = ::LoadImage(NULL, _T("theme\\picture\\fruit_element.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcElement.CreateCompatibleDC(&dc);
	m_dcElement.SelectObject(hBmpBG);

	HANDLE hMask = ::LoadImage(NULL, _T("theme\\picture\\fruit_mask.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcMask.CreateCompatibleDC(&dc);
	m_dcMask.SelectObject(hMask);
}

void CGameRelaxDlg::updateMap()
{
	int nLeft = m_ptGameTop.x;
	int nTop = m_ptGameTop.y;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;
	m_dcMem.BitBlt(m_rtGameRect1.left, m_rtGameRect1.top, m_rtGameRect1.Width(),
		m_rtGameRect1.Height(), &m_dcBG, m_rtGameRect1.left, m_rtGameRect1.top, SRCCOPY);
	m_dcMem.BitBlt(m_rtGameRect2.left, m_rtGameRect2.top, m_rtGameRect2.Width(),
		m_rtGameRect2.Height(), &m_dcBG, m_rtGameRect2.left, m_rtGameRect2.top, SRCCOPY);
	for (int i = 0;i < ROW;i++)
	{
		for (int j = 0;j < COL;j++)
		{
			int nInfo = m_gameControl.getElement(i, j);
			if (nInfo >= 0) {
				m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH,
					&m_dcMask, 0, nInfo * nElemH, SRCPAINT);
				m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH,
					&m_dcElement, 0, nInfo * nElemH, SRCAND);
			}
		}
	}
}


void CGameRelaxDlg::DrawTipFrame(int nRow, int nCol, int type)
{
	CClientDC dc(this);
	CBrush brush;
	if (type == 0)
	{
		brush.CreateSolidBrush(RGB(106, 90, 205));
	}
	else
	{
		brush.CreateSolidBrush(RGB(255, 0, 0));
		//	brush(RGB(233, 43, 43));
	}
	CRect rtTipFrame;
	rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.y + nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
	dc.FrameRect(rtTipFrame, &brush);
}

void CGameRelaxDlg::DrawTipLine()
{
	CClientDC dc(this);
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));
	CPen *pOldPen = dc.SelectObject(&penLine);
	int nRow1 = m_gameControl.m_ptSelFirst.row;
	int nCol1 = m_gameControl.m_ptSelFirst.col;
	int nRow2 = m_gameControl.m_ptSelSec.row;
	int nCol2 = m_gameControl.m_ptSelSec.col;

	if (m_gameControl.cor1.row == -1) {
		dc.MoveTo(m_ptGameTop.x + nCol1 * m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + nRow1 * m_sizeElem.cy + m_sizeElem.cy / 2);
		dc.LineTo(m_ptGameTop.x + nCol2 * m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + nRow2 * m_sizeElem.cy + m_sizeElem.cy / 2);
	}
	else if (m_gameControl.cor2.row == -1)
	{
		int nRow = m_gameControl.cor1.row;
		int nCol = m_gameControl.cor1.col;
		dc.MoveTo(m_ptGameTop.x + nCol1 * m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + nRow1 * m_sizeElem.cy + m_sizeElem.cy / 2);
		dc.LineTo(m_ptGameTop.x + nCol * m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + nRow * m_sizeElem.cy + m_sizeElem.cy / 2);
		dc.LineTo(m_ptGameTop.x + nCol2 * m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + nRow2 * m_sizeElem.cy + m_sizeElem.cy / 2);
	}
	else
	{
		int row1 = m_gameControl.cor1.row;
		int col1 = m_gameControl.cor1.col;
		int row2 = m_gameControl.cor2.row;
		int col2 = m_gameControl.cor2.col;
		if (nRow1 == nRow2)
		{
			dc.MoveTo(m_ptGameTop.x + nCol1 * m_sizeElem.cx + m_sizeElem.cx / 2,
				m_ptGameTop.y + nRow1 * m_sizeElem.cy + m_sizeElem.cy / 2);
			dc.LineTo(m_ptGameTop.x + col1 * m_sizeElem.cx + m_sizeElem.cx / 2,
				m_ptGameTop.y + row1 * m_sizeElem.cy + m_sizeElem.cy / 2);
			dc.LineTo(m_ptGameTop.x + col2 * m_sizeElem.cx + m_sizeElem.cx / 2,
				m_ptGameTop.y + row2 * m_sizeElem.cy + m_sizeElem.cy / 2);
			dc.LineTo(m_ptGameTop.x + nCol2 * m_sizeElem.cx + m_sizeElem.cx / 2,
				m_ptGameTop.y + nRow2 * m_sizeElem.cy + m_sizeElem.cy / 2);
		}
		else if (nCol1 == nCol2)
		{
			dc.MoveTo(m_ptGameTop.x + nCol1 * m_sizeElem.cx + m_sizeElem.cx / 2,
				m_ptGameTop.y + nRow1 * m_sizeElem.cy + m_sizeElem.cy / 2);
			if (nRow1 < nRow2)
			{
				dc.LineTo(m_ptGameTop.x + col1 * m_sizeElem.cx + m_sizeElem.cx / 2,
					m_ptGameTop.y + row1 * m_sizeElem.cy + m_sizeElem.cy / 2);
				dc.LineTo(m_ptGameTop.x + col2 * m_sizeElem.cx + m_sizeElem.cx / 2,
					m_ptGameTop.y + row2 * m_sizeElem.cy + m_sizeElem.cy / 2);
			}
			else
			{
				dc.LineTo(m_ptGameTop.x + col2 * m_sizeElem.cx + m_sizeElem.cx / 2,
					m_ptGameTop.y + row2 * m_sizeElem.cy + m_sizeElem.cy / 2);
				dc.LineTo(m_ptGameTop.x + col1 * m_sizeElem.cx + m_sizeElem.cx / 2,
					m_ptGameTop.y + row1 * m_sizeElem.cy + m_sizeElem.cy / 2);
			}
			dc.LineTo(m_ptGameTop.x + nCol2 * m_sizeElem.cx + m_sizeElem.cx / 2,
				m_ptGameTop.y + nRow2 * m_sizeElem.cy + m_sizeElem.cy / 2);
		}
		else
		{
			dc.MoveTo(m_ptGameTop.x + nCol1 * m_sizeElem.cx + m_sizeElem.cx / 2,
				m_ptGameTop.y + nRow1 * m_sizeElem.cy + m_sizeElem.cy / 2);
			dc.LineTo(m_ptGameTop.x + col1 * m_sizeElem.cx + m_sizeElem.cx / 2,
				m_ptGameTop.y + row1 * m_sizeElem.cy + m_sizeElem.cy / 2);
			dc.LineTo(m_ptGameTop.x + col2 * m_sizeElem.cx + m_sizeElem.cx / 2,
				m_ptGameTop.y + row2 * m_sizeElem.cy + m_sizeElem.cy / 2);
			dc.LineTo(m_ptGameTop.x + nCol2 * m_sizeElem.cx + m_sizeElem.cx / 2,
				m_ptGameTop.y + nRow2 * m_sizeElem.cy + m_sizeElem.cy / 2);
		}
	}
	dc.SelectObject(pOldPen);
}

void CGameRelaxDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
}



void CGameRelaxDlg::OnBnClickedStart2()
{
	if (!firstStart)
	{
		GetDlgItem(IDC_INTETEXT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_INTENUM)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_TOOLTEXT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_TOOLNUM)->ShowWindow(SW_SHOW);
		drawText();
		firstStart = true;
		m_reset.EnableWindow(0);
		m_tip.EnableWindow(0);
	}
	if (pause)
	{
		pause = false;
	}
	else 
	{
		m_gameControl.StartGame();
		isRunning = true;
		m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(),
			m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
		m_gameControl.StartGame();
	}
	updateMap();
	InvalidateRect(m_rtGameRect, FALSE);
	m_start.EnableWindow(0);
	isRunning = true;
	m_reset.EnableWindow(1);
//	m_tool.EnableWindow(1);
//	m_reset.EnableWindow(1);
	m_pause.EnableWindow(1);
//	m_tip.EnableWindow(1);
}


void CGameRelaxDlg::OnBnClickedPause()
{
	m_pause.EnableWindow(0);
	m_start.EnableWindow(1);
	m_tip.EnableWindow(0);
	m_reset.EnableWindow(0);
	m_tool.EnableWindow(0);
	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(),
		m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
	InvalidateRect(m_rtGameRect, FALSE);
	isRunning = false;
	pause = true;
}


void CGameRelaxDlg::OnBnClickedTip()
{
	Vertex v1, v2;
	if (m_gameControl.findLink(v1, v2))
	{
		DrawTipFrame(v1.row, v1.col, 0);
		DrawTipFrame(v2.row, v2.col, 0);
		Sleep(500);
		CRect r1, r2;
		r1.left = m_ptGameTop.x + v1.col * m_sizeElem.cx;
		r1.top = m_ptGameTop.y + v1.row * m_sizeElem.cy;
		r1.right =r1.left + m_sizeElem.cx;
		r1.bottom = r1.top + m_sizeElem.cy;
		r2.left = m_ptGameTop.x + v2.col * m_sizeElem.cx;
		r2.top = m_ptGameTop.y + v2.row * m_sizeElem.cy;
		r2.right = r2.left + m_sizeElem.cx;
		r2.bottom = r2.top + m_sizeElem.cy;
		InvalidateRect(r1, FALSE);
		InvalidateRect(r2, FALSE);
	}
	else
	{
		MessageBox(_T("死路一条!"));
	}
	integral -= 20;
	updateInte();
	if (integral < 20)
	{
		m_tip.EnableWindow(0);
	}
	if (integral < 50)
	{
		m_reset.EnableWindow(0);
	}
}


void CGameRelaxDlg::OnBnClickedReset2()
{
	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(),
		m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
//	m_pause.EnableWindow(1);
//	m_tip.EnableWindow(1);
//	m_start.EnableWindow(0);
//	isRunning = true;
	m_gameControl.exchange();
	updateMap();
	integral -= 50;
	updateInte();
	InvalidateRect(m_rtGameRect, FALSE);
	if (integral < 50)
	{
		m_reset.EnableWindow(0);
	}
}


void CGameRelaxDlg::OnBnClickedTool()
{
	toolNum--;
	integral += 10;
	updateInte();
	updateTool();
	if (toolNum < 1)
	{
		m_tool.EnableWindow(0);
	}
	usedTool = true;
}


void CGameRelaxDlg::OnBnClickedSetting()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CGameRelaxDlg::OnBnClickedHelp()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CGameRelaxDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (isRunning == false)
	{
		return;
	}
	CDialogEx::OnLButtonUp(nFlags, point);
	if (point.x < m_ptGameTop.x || point.y < m_ptGameTop.y)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	int nRow = (point.y - m_ptGameTop.y) / m_sizeElem.cy;
	int nCol = (point.x - m_ptGameTop.x) / m_sizeElem.cx;
	if (nRow > ROW - 1 || nCol > COL - 1)
	{
		return  CDialogEx::OnLButtonUp(nFlags, point);
	}
	if (m_bFirstPoint) {
		m_gameControl.setFirstPoint(nRow, nCol);
		int nInfo = m_gameControl.getElement(nRow, nCol);
		if (nInfo == -1)
			return;
		DrawTipFrame(nRow, nCol, 1);
		m_rtGameRect1.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
		m_rtGameRect1.top = m_ptGameTop.y + nRow * m_sizeElem.cy;
		m_rtGameRect1.right = m_rtGameRect1.left + m_sizeElem.cx;
		m_rtGameRect1.bottom = m_rtGameRect1.top + m_sizeElem.cy;
	}
	else
	{
		m_gameControl.setSecPoint(nRow, nCol);
		int nInfo = m_gameControl.getElement(nRow, nCol);
		if (nInfo == -1)
			return;
		if (usedTool && !m_gameControl.Link())
		{
			return;
		}
		DrawTipFrame(nRow, nCol, 1);
		m_rtGameRect2.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
		m_rtGameRect2.top = m_ptGameTop.y + nRow * m_sizeElem.cy;
		m_rtGameRect2.right = m_rtGameRect2.left + m_sizeElem.cx;
		m_rtGameRect2.bottom = m_rtGameRect2.top + m_sizeElem.cy;
		//判断是否相同图片
		if (usedTool&&m_gameControl.Link())
		{
			integral += 10;
			allNum += 10;
			m_gameControl.clear();
			updateMap();
			usedTool = false;
		}
		else if (m_gameControl.Link() && m_gameControl.isCanLink())
		{
			DrawTipLine();
			m_gameControl.clear();
			integral += 10;
			allNum += 10;
			updateInte();
			updateTool();
			updateMap();
		}
		Sleep(250);
		InvalidateRect(m_rtGameRect, FALSE);
		if (m_gameControl.canWin() && isRunning)
		{
			isRunning = false;
			MessageBox(TEXT("胜利!"));
			OnBnClickedStart2();
			isRunning = true;
		}
	}
	m_bFirstPoint = !m_bFirstPoint;
}

void CGameRelaxDlg::drawText()
{
	CFont font;
	font.CreatePointFont(180, TEXT("楷体"));
	GetDlgItem(IDC_INTETEXT)->SetFont(&font);
	m_inteText.SetWindowTextW(_T("积分"));
	GetDlgItem(IDC_INTENUM)->SetFont(&font);
	m_inteNum.SetWindowTextW(_T("0"));
	GetDlgItem(IDC_TOOLTEXT)->SetFont(&font);
	m_toolText.SetWindowTextW(_T("道具"));
	GetDlgItem(IDC_TOOLNUM)->SetFont(&font);
	m_toolNum.SetWindowTextW(_T("0"));
}

void CGameRelaxDlg::updateInte()
{
	CFont font;
	font.CreatePointFont(180, TEXT("楷体"));
	GetDlgItem(IDC_INTENUM)->SetFont(&font);
	CString str;
	str.Format(_T("%d"), integral);
	m_inteNum.SetWindowTextW(str);
	if (integral >= 20)
	{
		m_tip.EnableWindow(1);
	}
	if (integral >= 50)
	{
		m_reset.EnableWindow(1);
	}
	if (allNum % 100 == 0 && allNum != 0)
	{
		toolNum++;
	}
}

void CGameRelaxDlg::updateTool()
{
	CFont font;
	font.CreatePointFont(180, TEXT("楷体"));
	GetDlgItem(IDC_TOOLNUM)->SetFont(&font);
	CString str;
	str.Format(_T("%d"), toolNum);
	m_toolNum.SetWindowTextW(str);
	if (toolNum >= 1)
	{
		m_tool.EnableWindow(1);
	}
}

HBRUSH CGameRelaxDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID() == IDC_INTETEXT || pWnd->GetDlgCtrlID() == IDC_INTENUM 
		|| pWnd->GetDlgCtrlID() == IDC_TOOLTEXT || pWnd->GetDlgCtrlID() == IDC_TOOLNUM)
	{
		pDC->SetTextColor(RGB(255, 105, 180));//设置字体颜色  
	//	pDC->SetBkColor(RGB(0, 255, 0));//设置背景颜色
		pDC->SetBkMode(TRANSPARENT);//设置背景透明
		hbr = CreateSolidBrush(RGB(230, 230, 250));
	}
	return hbr;
}
