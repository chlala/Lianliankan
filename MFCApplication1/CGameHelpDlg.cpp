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
//	ON_WM_RBUTTONUP()
//	ON_WM_MOUSEHWHEEL()
//	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CGameHelpDlg 消息处理程序


void CGameHelpDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 453, 620, &m_dcMem, 0, 0, SRCCOPY);
}

BOOL CGameHelpDlg::OnInitDialog()
{
//	CDialogEx::OnInitDialog();


	HICON m_hIcon;
	m_hIcon = AfxGetApp()->LoadIcon(IDI_LLK);
	SetIcon(m_hIcon, true);
	CDialogEx::OnInitDialog();
//	init();
	//加载Help图片资源
/*	CClientDC dc(this);
	HANDLE hbmpHelp = ::LoadImage(NULL, _T("theme\\picture\\basic_help.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcHelp.CreateCompatibleDC(&dc);
	m_dcHelp.SelectObject(hbmpHelp);
	//创建内存DC大小
	CRect rtClient;
	this->GetWindowRect(&rtClient);
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, rtClient.Width(), rtClient.Height());
	bmpMem.CreateCompatibleBitmap(&dc, 500, 600);
	m_dcMem.SelectObject(&bmpMem);
	//绘制白色背景
	m_dcMem.BitBlt(0, 0, rtClient.Width(), rtClient.Height(),
		NULL, 0, 0, WHITENESS);
	m_dcMem.BitBlt(0, 0, 500, 600,
				NULL, 0, 0, WHITENESS);*/
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
	//绘制帮助信息显示区域
/*	this->GetDlgItem(IDC_SCROLLBAR1)->GetWindowRect(&m_rtHelp);
	this->ScreenToClient(&m_rtHelp);
	//绘制帮助信息
	updateHelp(0);
	//设置滚动条范围
	CBitmap bmpHelp;
	bmpHelp.Attach(hbmpHelp);
	BITMAP bmpInfo;
	bmpHelp.GetBitmap(&bmpInfo);
	((CScrollBar*)this->GetDlgItem(IDC_SCROLLBAR1))->SetScrollRange(0, bmpInfo.bmHeight,bmpInfo.bmWidth);
*/
/*	CBitmap bmpHelp;
	bmpHelp.Attach(hbmpHelp);
	BITMAP bmpInfo;
	bmpHelp.GetBitmap(&bmpInfo);*/
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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

/*
void CGameHelpDlg::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// 此功能要求 Windows Vista 或更高版本。
	// _WIN32_WINNT 符号必须 >= 0x0600。
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (zDelta < 0)
	{
		OnVScroll(SB_LINEDOWN, GetScrollPos(SB_VERT), GetScrollBarCtrl(SB_VERT));
	}
	else if (zDelta > 0)
	{
		OnVScroll(SB_LINEUP, GetScrollPos(SB_VERT), GetScrollBarCtrl(SB_VERT));
	}
	CDialogEx::OnMouseHWheel(nFlags, zDelta, pt);
}


void CGameHelpDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetFocus();
	CDialogEx::OnLButtonUp(nFlags, point);
}*/
