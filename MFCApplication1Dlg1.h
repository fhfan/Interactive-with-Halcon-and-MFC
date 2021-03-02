
// MFCApplication1Dlg.h : 头文件
//

#pragma once
#include "HalconCpp.h"

using namespace HalconCpp;


// CMFCApplication1Dlg 对话框
class CMFCApplication1Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	HTuple m_hWnd; //显示窗口句柄

	HObject m_hImage;//图像对象

	HTuple m_hWidth;//图像宽

	HTuple m_hHeight;

	CRect m_rtImage;

	CString m_strImagePath;

	double m_dDispImagePartRow0;

	double m_dDispImagePartCol0;

	double m_dDispImagePartRow1;

	double m_dDispImagePartCol1;
	double m_dScale;//缩放倍数
	int m_nHeightOffset;//偏移量
	int m_nWidthOffset;
	CPoint m_ptStart;//鼠标拖动的起点
	CPoint m_ptEnd;//鼠标拖动的终点
	CStatic m_staticImage;
	void CreateImageWindow();
	BOOL PreTranslateMessage(MSG* pMsg);
	//BOOL InitHalconWindow();
	void ShowImage();
	void InitConsoleWindow();
	afx_msg void OnBnClickedButton1();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	HObject ho_Contours, ho_ContoursScaled, ho_ModelTrans;
	afx_msg void OnBnClickedButton2();
	void DisPlayImage(HObject hImageSrc, HTuple hWindow);//显示图片
	double dpi;
	double angle;
	//double mousex;
	//double mousey;
	double mousex;
	double mousey;
};
