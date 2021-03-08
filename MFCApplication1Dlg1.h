#pragma once
#include<vector>
#include <iostream>
#include <string>
#include "HalconCpp.h"
#include "VarPackage.h"
#include "afxwin.h"

using namespace std;
using namespace HalconCpp;

// MultiRegions 对话框

class MultiRegions : public CDialogEx
{
	DECLARE_DYNAMIC(MultiRegions)

public:
	MultiRegions(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MultiRegions();

// 对话框数据
	enum { IDD = IDD_MULTIXLD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL MultiRegions::PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
protected:
	HICON m_hIcon;
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

public:
	CRect Rect;
	CRect PicRect;
	float  m_dDispImagePartRow0;
	float  m_dDispImagePartCol0;
	float  m_dDispImagePartRow1;
	float  m_dDispImagePartCol1;

	CComboBox m_combo_xldOut;
	CComboBox m_combo_detectmethod;
	CComboBox m_combo_roiplottype;
	CComboBox m_combo_lightdark;
	CListCtrl m_list_xldIn;
	CListCtrl m_list_detectAllRegion;

	HObject hoImage, hoImageResult; //hoImage原图像对象
	HObject ho_Rectangle;
	HObject ho_DiffRectangle;
	HObject ho_GenRegions;
	HObject ho_GenContours;
	HTuple hv_contourGroupIdx;
	HTuple hv_regionIdDefinedByUser;
	HTuple hv_mousePositionRegionID;
	HTuple hvWindowID;                    //显示窗口句柄
	vector<CString> detectmethods;        //所有区域使用的算法（依次推入该容器）
	vector<HObject> hv_single_XldList;    //所有新建的xld（依次推入该容器）
	vector<HObject> hv_singleRegionList;  //所有新建的region（依次推入该容器）
	vector<bool> b_reduceList;            //轮廓在list control中是否被勾选（即要减去的内部轮廓）, 

	bool m_isDrawing;
	double m_startX;
	double m_startY;
	double m_offsetX;
	double m_offsetY;
	bool m_bImgMove;
	//int m_operationType;//1：绘图
	bool m_isTypeChanged;

public:
	virtual BOOL OnInitDialog();

	void CreateImageWindow();
	void ReListData(int NumXld);
	void ShowImage();
	afx_msg void OnBnClickedButtonLoadimageXld();
	afx_msg void OnBnClickedButtonPlotxlds();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLvnItemchangedListXldin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedRegionRefresh();
	afx_msg void OnBnClickedRegionConfirm();
	afx_msg void OnBnClickedImagecut();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	CComboBox m_combo_regioninout;
	afx_msg void OnCbnEditupdateComboXldadded();
	afx_msg void OnCbnSelchangeComboRegioninout();
	afx_msg void OnCbnSelchangeComboDetectmethod();
	afx_msg void OnCbnSelchangeComboLightdark();
	afx_msg void OnCbnSelchangeComboXldadded();

private:
	void MoveImage(CPoint point/*, HImage	srcImg, HTuple hWindow*/);
	bool IsChild(int index);
	void Drawing();

public:
	afx_msg void OnCbnSelchangeComboPlottype();   //错误
	LPITEMIDLIST ParsePidlFromPath(LPCSTR path);
	////////////////////////////////////////////
	//HTuple m_hWnd; //显示窗口句柄
	HObject ho_ImageBG;
	//HObject m_hImage;

	HTuple m_hWidth;//图像宽

	HTuple m_hHeight;

	CRect m_rtImage;

	CString m_strImagePath;

	//double m_dDispImagePartRow0;

	//double m_dDispImagePartCol0;

	//double m_dDispImagePartRow1;

	//double m_dDispImagePartCol1;
	double m_dScale;//缩放倍数
	int m_nHeightOffset;//偏移量
	int m_nWidthOffset;
	CPoint m_ptStart;//鼠标拖动的起点
	CPoint m_ptEnd;//鼠标拖动的终点
	CStatic m_staticImage;
	//void CreateImageWindow();
	//BOOL PreTranslateMessage(MSG* pMsg);
	//BOOL InitHalconWindow();
	//void ShowImage();
	void InitConsoleWindow();
	//afx_msg void OnBnClickedButton1();
	//afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	HObject ho_Contours, ho_ContoursScaled, ho_ModelTrans;
	//afx_msg void OnBnClickedButton2();
	void DisPlayImage(HObject hImageSrc, HTuple hWindow);//显示图片
	//double dpi;
	//double angle;
	//double mousex;
	//double mousey;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};

int SplitCString(const CString str, char split, CStringArray &strArray);
