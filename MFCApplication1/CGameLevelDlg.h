#pragma once
#include "CGameControl.h"

// CGameLevelDlg 对话框

class CGameLevelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameLevelDlg)

public:
	CGameLevelDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameLevelDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LEVEL };
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

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	void InitBackground();
};
