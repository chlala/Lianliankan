// CGameLevelDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "CGameLevelDlg.h"
#include "afxdialogex.h"


// CGameLevelDlg 对话框

IMPLEMENT_DYNAMIC(CGameLevelDlg, CDialogEx)

CGameLevelDlg::CGameLevelDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LEVEL, pParent)
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

CGameLevelDlg::~CGameLevelDlg()
{
}

void CGameLevelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameLevelDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CGameLevelDlg 消息处理程序



BOOL CGameLevelDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	HICON m_hIcon;
	m_hIcon = AfxGetApp()->LoadIcon(IDI_LLK);
	SetIcon(m_hIcon, true);
	InitBackground();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CGameLevelDlg::OnPaint()
{
	CPaintDC dc(this); 
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
}

void CGameLevelDlg::InitBackground()
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
