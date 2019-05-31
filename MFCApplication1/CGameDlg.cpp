// CGameDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "CGameDlg.h"
#include "afxdialogex.h"

// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAMEBASIC, pParent)
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
	m_timeCount = TIME;
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_START, m_start);
	DDX_Control(pDX, IDC_RESET, m_reset);
	DDX_Control(pDX, IDC_PAUSE, m_pause);
	DDX_Control(pDX, IDC_TIP, m_tip);
	DDX_Control(pDX, IDC_PROGRESS1, m_GameProcess);
	DDX_Control(pDX, IDC_TIME, m_time);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_BN_CLICKED(IDC_START, &CGameDlg::OnBnClickedStart)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_RESET, &CGameDlg::OnBnClickedReset)
	ON_BN_CLICKED(IDC_PAUSE, &CGameDlg::OnBnClickedPause)
	ON_BN_CLICKED(IDC_TIP, &CGameDlg::OnBnClickedTip)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_HELP, &CGameDlg::OnBnClickedHelp)
END_MESSAGE_MAP()


// CGameDlg 消息处理程序

BOOL CGameDlg::OnInitDialog()
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
	return true;
}

void CGameDlg::InitBackground()
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

void CGameDlg::OnPaint()
{
	CPaintDC dc(this); 
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
}

void CGameDlg::InitElement()
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

void CGameDlg::updateMap()
{
	int nLeft = m_ptGameTop.x;
	int nTop = m_ptGameTop.y;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;
	m_dcMem.BitBlt(m_rtGameRect1.left, m_rtGameRect1.top, m_rtGameRect1.Width(),
		m_rtGameRect1.Height(),&m_dcBG, m_rtGameRect1.left, m_rtGameRect1.top, SRCCOPY);
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

void CGameDlg::OnBnClickedStart()
{
	if (pause)
	{
		pause = false;
	}
	else
	{
		m_gameControl.StartGame();
		isRunning = true;
		GetDlgItem(IDC_PROGRESS1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_TIME)->ShowWindow(SW_SHOW);
		m_timeCount = TIME;
		dreawGameTime();
		m_GameProcess.SetRange(0, TIME);
		m_GameProcess.SetStep(-3);
		m_GameProcess.SetPos(TIME);
		m_timeCount = TIME;
		m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(),
			m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
		m_gameControl.StartGame();
	}
	updateMap();
	InvalidateRect(m_rtGameRect, FALSE);
	this->SetTimer(IDC_PROGRESS1, 1000, NULL);
	m_start.EnableWindow(0);
	isRunning = true;
	m_reset.EnableWindow(1);
	m_pause.EnableWindow(1);
	m_tip.EnableWindow(1);
}

void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (isRunning == false)
	{
		return;
	}
	CDialogEx::OnLButtonUp(nFlags, point);
	if (point.x < m_ptGameTop.x || point.y < m_ptGameTop.y)
	{
		return CDialogEx::OnLButtonUp(nFlags,point);
	}
	int nRow = (point.y - m_ptGameTop.y) / m_sizeElem.cy;
	int nCol = (point.x - m_ptGameTop.x) / m_sizeElem.cx;
	if (nRow > ROW - 1 || nCol > COL - 1)
	{
		return  CDialogEx::OnLButtonUp(nFlags, point);
	}
	if (m_bFirstPoint) {
		m_gameControl.setFirstPoint(nRow,nCol);
		int nInfo = m_gameControl.getElement(nRow,nCol);
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
		DrawTipFrame(nRow, nCol, 1);
		m_rtGameRect2.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
		m_rtGameRect2.top = m_ptGameTop.y + nRow * m_sizeElem.cy;
		m_rtGameRect2.right = m_rtGameRect2.left + m_sizeElem.cx;
		m_rtGameRect2.bottom = m_rtGameRect2.top + m_sizeElem.cy;
		//判断是否相同图片
		if (m_gameControl.Link() && m_gameControl.isCanLink())
		{
			DrawTipLine();
			m_gameControl.clear();
			updateMap();
		}
		Sleep(250);
		InvalidateRect(m_rtGameRect,FALSE);
		if (m_gameControl.canWin() && isRunning) 
		{
			isRunning = false;
			MessageBox(TEXT("胜利!"));
			OnBnClickedStart();
			isRunning = true;
		}
	}
	m_bFirstPoint = !m_bFirstPoint;
}

void CGameDlg::DrawTipFrame(int nRow, int nCol, int type)
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
	}
	CRect rtTipFrame;
	rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.y + nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
	dc.FrameRect(rtTipFrame, &brush);
}

void CGameDlg::DrawTipLine()
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
	else if(m_gameControl.cor2.row == -1)
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

void CGameDlg::OnBnClickedReset()
{
	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(),
		m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
	m_pause.EnableWindow(1);
	m_tip.EnableWindow(1);
	m_start.EnableWindow(0);
	isRunning = true;
	m_gameControl.exchange();
	updateMap();
	InvalidateRect(m_rtGameRect, FALSE);
}

void CGameDlg::OnBnClickedPause()
{
	m_pause.EnableWindow(0);
	m_start.EnableWindow(1);
	m_tip.EnableWindow(0);
	m_reset.EnableWindow(0);
	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(),
		m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
	InvalidateRect(m_rtGameRect, FALSE);
	isRunning = false;
	pause = true;
	this->KillTimer(IDC_PROGRESS1);
}


void CGameDlg::OnBnClickedTip()
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
}


void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == IDC_PROGRESS1 && isRunning && m_timeCount % 3 == 2)
	{
		m_GameProcess.StepIt();
	}
	m_timeCount--;
	dreawGameTime();
	CDialogEx::OnTimer(nIDEvent);
	if (m_timeCount <= 0 && isRunning)
	{
		m_GameProcess.SetPos(0);
		isRunning = false;
		MessageBox(TEXT("失败>-_-<"));
		m_start.EnableWindow(1);
		m_pause.EnableWindow(0);
		m_tip.EnableWindow(0);
		m_reset.EnableWindow(0);
	}
}


void CGameDlg::dreawGameTime()
{
	CFont font;
	font.CreatePointFont(180, TEXT("宋体"));
	GetDlgItem(IDC_TIME)->SetFont(&font);
	if (isRunning)
	{
		CString str;
		str.Format(_T("%d"),m_timeCount);
		m_time.SetWindowTextW(str);
	}
}


HBRUSH CGameDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID() == IDC_TIME)// IDC_Display为所选文本框ID
	{
		pDC->SetTextColor(RGB(255, 0, 0));//设置字体颜色  
		pDC->SetBkMode(TRANSPARENT);//设置背景透明
		hbr = CreateSolidBrush(RGB(230, 230, 250));
	}
	return hbr;
}

void CGameDlg::OnBnClickedHelp()
{
	if (pause)
	{
		CGameHelpDlg dig;
		dig.DoModal();
	}
	else
	{
		m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(),
			m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
		InvalidateRect(m_rtGameRect, FALSE);
		isRunning = false;
		this->KillTimer(IDC_PROGRESS1);
		CGameHelpDlg dig;
		dig.DoModal();
		isRunning = true;
		this->SetTimer(IDC_PROGRESS1, 1000, NULL);
		updateMap();
		InvalidateRect(m_rtGameRect, FALSE);
	}
}
