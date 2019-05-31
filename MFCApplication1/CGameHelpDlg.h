#pragma once


// CGameHelpDlg 对话框

class CGameHelpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameHelpDlg)

public:
	CGameHelpDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameHelpDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HELP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CDC m_dcHelp;
	CDC m_dcMem;
	CRect m_rtHelp;
	int nMin;
	int nMax;
	int nCurpos;
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_text;

	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	void updateHelp(int nPos);
	void init();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
//	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
