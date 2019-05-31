// CGameHelpDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "CGameHelpDlg.h"
#include "afxdialogex.h"


// CGameHelpDlg 对话框

IMPLEMENT_DYNAMIC(CGameHelpDlg, CDialogEx)

CGameHelpDlg::CGameHelpDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HELP, pParent)
{
	m_rtHelp.top = 0;
	m_rtHelp.left = 0;
	m_rtHelp.right = m_rtHelp.left + 453;
	m_rtHelp.bottom = m_rtHelp.top + 620;
}

CGameHelpDlg::~CGameHelpDlg()
{
}

void CGameHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
//	DDX_Control(pDX, IDC_TEXT, m_text);
}

BEGIN_MESSAGE_MAP(CGameHelpDlg, CDialogEx)
	ON_WM_VSCROLL()
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CGameHelpDlg 消息处理程序

void CGameHelpDlg::OnPaint()
{
	CPaintDC dc(this); 
	dc.BitBlt(0, 0, 453, 620, &m_dcMem, 0, 0, SRCCOPY);
}

BOOL CGameHelpDlg::OnInitDialog()
{
	HICON m_hIcon;
	m_hIcon = AfxGetApp()->LoadIcon(IDI_LLK);
	SetIcon(m_hIcon, true);
	CDialogEx::OnInitDialog();
	CClientDC dc(this);
	HANDLE hbmpHelp = ::LoadImage(NULL, _T("theme\\picture\\basic_help.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcHelp.CreateCompatibleDC(&dc);
	m_dcHelp.SelectObject(hbmpHelp);

	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 453, 620);
	m_dcMem.SelectObject(&bmpMem);
	m_dcMem.BitBlt(0, 0, 453, 620, &m_dcHelp, 0, 0, SRCCOPY);
	CScrollBar* pScrollBar = (CScrollBar*)GetDlgItem(IDC_SCROLLBAR1);
	pScrollBar->SetScrollRange(0, 450, 453);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CGameHelpDlg::init()
{
	CClientDC dc(this);
	HANDLE hbmpHelp = ::LoadImage(NULL, _T("theme\\picture\\basic_help.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcHelp.CreateCompatibleDC(&dc);
	m_dcHelp.SelectObject(hbmpHelp);

	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 453, 620);
	m_dcMem.SelectObject(&bmpMem);
	m_dcMem.BitBlt(0, 0, 453, 620, &m_dcHelp, 0, 0, SRCCOPY);
}

void CGameHelpDlg::updateHelp(int nPos)
{
	m_dcMem.BitBlt(m_rtHelp.left, m_rtHelp.top, m_rtHelp.Width(),
		m_rtHelp.Height(), NULL, 0, 0, WHITENESS);
	m_dcMem.BitBlt(m_rtHelp.left, m_rtHelp.top, m_rtHelp.Width(),
		m_rtHelp.Height(), &m_dcHelp, 0, nPos, SRCCOPY);
	InvalidateRect(m_rtHelp, FALSE);
}


void CGameHelpDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	pScrollBar->GetScrollRange(&nMin, &nMax);  //取得滚动条范围
	nCurpos = pScrollBar->GetScrollPos();
	switch (nSBCode)
	{
	case SB_LINEUP:
		nCurpos -= 5;
		break;
	case SB_LINEDOWN:
		nCurpos += 5;
		break;
	case SB_PAGEUP:
		nCurpos -= 20;
		break;
	case SB_PAGEDOWN:
		nCurpos += 20;
		break;
	case SB_TOP:
		nCurpos = nMin;
		break;
	case SB_BOTTOM:
		nCurpos = nMax;
		break;
	case SB_THUMBPOSITION:
		nCurpos = nPos;
		break;
	default:
		break;
	}
	if (nCurpos > nMax) {
		nCurpos = nMax;
	}
	if (nCurpos < nMin)
	{
		nCurpos = nMin;
	}
	pScrollBar->SetScrollPos(nCurpos);
	updateHelp(nCurpos);
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}
