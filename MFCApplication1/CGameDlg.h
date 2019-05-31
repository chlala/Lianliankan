#pragma once
#include "global.h"
#include "CGameControl.h"
#include "CGameHelpDlg.h"
#define TIME 300
#define TIP 0
// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAMEBASIC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
	void InitBackground();
	void InitElement();

private:
	BOOL CGameDlg::OnInitDialog();
public:
	afx_msg void OnBnClickedStart();
protected:
	CDC m_dcMem;
	CDC m_dcElement;
	CDC m_dcMask;
	CDC m_dcBG;
	CPoint m_ptGameTop;
	CSize m_sizeElem;
	bool m_bFirstPoint;
	CRect m_rtGameRect1;
	CRect m_rtGameRect2;
	CRect m_rtGameRect;
	CGameControl m_gameControl;
	bool isRunning;
	bool pause;

public:
	afx_msg void OnPaint();
	CButton m_start;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void DrawTipFrame(int nRow, int nCol, int type);
	void DrawTipLine();
	void updateMap();
	afx_msg void OnBnClickedReset();
	CButton m_reset;
	CButton m_pause;
	CButton m_tip;
	afx_msg void OnBnClickedPause();
	afx_msg void OnBnClickedTip();
	CProgressCtrl m_GameProcess;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void dreawGameTime();
	int m_timeCount;
	CStatic m_time;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedHelp();
};
