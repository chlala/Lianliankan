#pragma once
#include "CGameControl.h"

// CGameRelax 对话框

class CGameRelaxDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameRelaxDlg)

public:
	CGameRelaxDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameRelaxDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RELAX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
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
	int integral;
	int toolNum;
	int allNum;
	bool firstStart;
	bool usedTool;
	DECLARE_MESSAGE_MAP()
public:
	BOOL OnInitDialog();
	void DrawTipFrame(int nRow, int nCol, int type);
	void DrawTipLine();
	void updateMap();
	void InitBackground();
	void InitElement();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedStart2();
	afx_msg void OnBnClickedPause();
	afx_msg void OnBnClickedTip();
	afx_msg void OnBnClickedReset2();
	afx_msg void OnBnClickedTool();
	afx_msg void OnBnClickedSetting();
	afx_msg void OnBnClickedHelp();
	void updateInte();
	void updateTool();
	void drawText();
	CButton m_start;
	CButton m_pause;
	CButton m_tip;
	CButton m_reset;
	CButton m_tool;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	CStatic m_inteText;
	CStatic m_inteNum;
	CStatic m_toolText;
	CStatic m_toolNum;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
