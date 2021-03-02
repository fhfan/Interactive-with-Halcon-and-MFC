
// MFCApplication1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication1Dlg::IDD, pParent)
	, dpi(3.38)
	, angle(0)
	//, mousex(0)
	//, mousey(0)
	, mousex(0)
	, mousey(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, dpi);
	DDX_Text(pDX, IDC_EDIT2, angle);
	//DDX_Text(pDX, IDC_EDIT3, mousex);
	//DDX_Text(pDX, IDC_EDIT4, mousey);
	DDX_Text(pDX, IDC_EDIT3, mousex);
	DDX_Text(pDX, IDC_EDIT4, mousey);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_WM_MOUSEWHEEL()
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	CreateImageWindow();
	//InitConsoleWindow();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::InitConsoleWindow()
{
	AllocConsole();
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long)handle, _O_TEXT);
	FILE *hf = _fdopen(hCrt, "w");
	*stdout = *hf;
}

void CMFCApplication1Dlg::CreateImageWindow()
{
	HTuple HWindowID;
	CRect Rect;
	CWnd* pWnd = GetDlgItem(IDC_PIC);
	HWindowID = (Hlong)pWnd->m_hWnd;
	pWnd->GetWindowRect(&Rect);
	OpenWindow(0, 0, Rect.Width(), Rect.Height(), HWindowID, "visible", "", &m_hWnd);
}
//显示图片函数

//void CMFCApplication1Dlg::ShowImage()
//
//{
//	if (m_hWnd != 0)
//
//	{
//		SetSystem("flush_graphic", "false");
//
//		ClearWindow(m_hWnd);
//
//		//显示
//
//		if (m_hImage.IsInitialized())
//
//		{
//			SetPart(m_hWnd, m_dDispImagePartRow0, m_dDispImagePartCol0, m_dDispImagePartRow1 - 1, m_dDispImagePartCol1 - 1);
//
//			DispObj(m_hImage, m_hWnd);
//
//		}
//
//		SetSystem("flush_graphic", "true");
//
//		HObject emptyObject;
//
//		emptyObject.GenEmptyObj();
//
//		DispObj(emptyObject, m_hWnd);
//
//	}
//
//}


void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void dxf_scale(void * hContours, double pixel_size, void *hContours_result, double *x_base, double *y_base)
{
	double scale = 1.0 / pixel_size;


	HTuple  hv_HomMat2DIdentity;
	HTuple  hv_Scale = scale;
	HTuple  hv_HomMat2DScale;
	HObject& ho_Contours = *(HObject*)hContours;
	HObject& ho_ContoursScaled = *(HObject*)hContours_result;
	HTuple  hv_PointOrder;

	UnionAdjacentContoursXld(ho_Contours, &ho_Contours, 1, 1, "attr_keep");
	HomMat2dIdentity(&hv_HomMat2DIdentity);
	hv_Scale = scale;
	HomMat2dScale(hv_HomMat2DIdentity, hv_Scale, hv_Scale, 0, 0, &hv_HomMat2DScale);
	AffineTransContourXld(ho_Contours, &ho_ContoursScaled, hv_HomMat2DScale);

	HTuple  hv_Area, hv_RowScaled, hv_ColScaled;

	AreaCenterXld(ho_Contours, &hv_Area, &hv_RowScaled, &hv_ColScaled, &hv_PointOrder);
	*x_base = hv_ColScaled[0];
	*y_base = hv_RowScaled[0];
}

void dxf_transform(void* hContours, double xp, double yp, double angle, void* hContours_result)
{
	HTuple  hv_HomMat2DIdentity;
	HTuple  hv_Area, hv_RowScaled, hv_ColScaled;
	HObject& ho_Contours = *(HObject*)hContours;
	HObject& ho_ContoursCenteredAndTranlated = *(HObject*)hContours_result;

	HTuple  hv_PointOrder;
	HTuple  hv_HomMat2D;

	AreaCenterXld(ho_Contours, &hv_Area, &hv_RowScaled, &hv_ColScaled, &hv_PointOrder);
	double x_center = hv_ColScaled[0];
	double y_center = hv_RowScaled[0];

	//double x_center = hv_ColScaled.TupleMean().D();
	//double y_center = hv_RowScaled.TupleMean().D();

	//printf("DXF mean center xy(%f,%f),at %s:%d\r\n", hv_ColScaled.TupleMean().D(), hv_RowScaled.TupleMean().D(), __FUNCTION__, __LINE__);
	//printf("DXF center 0: xy(%f,%f),at %s:%d\r\n", x_center, y_center, __FUNCTION__, __LINE__);

	VectorAngleToRigid(HTuple(hv_RowScaled[0]), HTuple(hv_ColScaled[0]), 0, yp,
		xp, (angle * 3.1415926) / 180, &hv_HomMat2D);
	AffineTransContourXld(ho_Contours, &ho_ContoursCenteredAndTranlated, hv_HomMat2D);

	HTuple  hv_Area_, hv_RowScaled_, hv_ColScaled_;
	HTuple  hv_PointOrder_;

	AreaCenterXld(ho_ContoursCenteredAndTranlated, &hv_Area_, &hv_RowScaled_, &hv_ColScaled_, &hv_PointOrder_);
	x_center = hv_ColScaled_[0];
	y_center = hv_RowScaled_[0];

	//printf("DXF mean center_ xy(%f,%f),at %s:%d\r\n", hv_ColScaled_.TupleMean().D(), hv_RowScaled_.TupleMean().D(), __FUNCTION__, __LINE__);
	//printf("DXF center_ 0: xy(%f,%f),at %s:%d\r\n", x_center, y_center, __FUNCTION__, __LINE__);
}


void CMFCApplication1Dlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	HTuple hv_Files, hv_DxfStatus;
	HTuple hv_ImagePath = "C:\\Users\\AI-009\\Desktop\\metal-parts-08.png";
	m_dScale = 0;//重置
	m_nHeightOffset = 0;
	m_nWidthOffset = 0;
	//HTuple hv_mouseR, hv_mouseC, hv_Button;
	//double angle = 0;
	ReadImage(&m_hImage, hv_ImagePath);
	//GetImagePointer1(hoImage, NULL, NULL, &m_ImageWidth, &m_ImageHeight);
	GetImageSize(m_hImage, &m_hWidth, &m_hHeight);
	SetPart(m_hWnd, 0, 0, m_hHeight - 1, m_hWidth - 1);
	//设置窗口

	/*float fImage = m_hWidth.D() / m_hHeight.D();

	float fWindow = (float)m_rtImage.Width() / m_rtImage.Height();

	float Row0 = 0, Col0 = 0, Row1 = m_hHeight - 1, Col1 = m_hWidth - 1;

	if (fWindow > fImage)

	{
		float w = fWindow * m_hHeight;

		Row0 = 0;

		Col0 = -(w - m_hWidth) / 2;

		Row1 = m_hHeight - 1;

		Col1 = m_hWidth + (w - m_hWidth) / 2;

	}

	else

	{
		float h = m_hWidth / fWindow;

		Row0 = -(h - m_hHeight) / 2;

		Col0 = 0;

		Row1 = m_hHeight + (h - m_hHeight) / 2;

		Col1 = m_hWidth - 1;

	}

	m_dDispImagePartRow0 = Row0;

	m_dDispImagePartCol0 = Col0;

	m_dDispImagePartRow1 = Row1;

	m_dDispImagePartCol1 = Col1;

	ShowImage();*/
	ReadContourXldDxf(&ho_Contours, "C:\\Users\\AI-009\\Desktop\\metal-part-03.dxf", HTuple(),
		HTuple(), &hv_DxfStatus);
	//dxf_scale(&ho_Contours, pixel_size, &ho_ContoursScaled, &x_base, &y_base);

	HDevWindowStack::Push(m_hWnd);
	if (HDevWindowStack::IsOpen())
	{
		DispObj(m_hImage, HDevWindowStack::GetActive());
		//DispObj(ho_ContoursScaled, HDevWindowStack::GetActive());
		//while (true)
		//{
		//	/*GetMposition(hvWindowID, &hv_mouseR, &hv_mouseC, &hv_Button);
		//	cout << "R:" << hv_mouseR.I() << endl;
		//	cout << "C:" << hv_mouseC.I() << endl;*/
		//	dxf_transform(&ho_ContoursScaled, hv_mouseC.I(), hv_mouseR.I(), angle, &ho_ModelTrans);
		//	DispObj(ho_ModelTrans, HDevWindowStack::GetActive());
		//}
	}
}


//图像显示
void CMFCApplication1Dlg::DisPlayImage(HObject hImageSrc, HTuple hWindow)
{
	//判断hImageSrc是否加载图片初始化
	if (!hImageSrc.IsInitialized())
	{
		return;
	}

	//HTuple hImageWidth; //图片原始宽度
	//HTuple hImageHeight;//图片原始高度
	GetImageSize(hImageSrc, &m_hWidth, &m_hHeight);

	int nImageHeight = m_hHeight.I();
	int nImageWidth = m_hWidth.I();

	double Row1 = nImageHeight*m_dScale - m_nHeightOffset;
	double Column1 = nImageWidth*m_dScale - m_nWidthOffset;
	double Row2 = nImageHeight - nImageHeight*m_dScale - m_nHeightOffset;
	double Column2 = nImageWidth - nImageWidth*m_dScale - m_nWidthOffset;

	//ClearWindow(hWindow);
	SetPart(hWindow, Row1, Column1, Row2, Column2);
	HDevWindowStack::Push(m_hWnd);
	if (HDevWindowStack::IsOpen())
	{
		DispObj(hImageSrc, HDevWindowStack::GetActive());
	}

}

BOOL CMFCApplication1Dlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	// 此功能要求 Windows Vista 或更高版本。

	// _WIN32_WINNT 符号必须 >= 0x0600。

	// TODO: 在此添加消息处理程序代码和/或调用默认值

	double dAddScal = 0.05;
	if (zDelta>0)
	{
		if (fabs(m_dScale + dAddScal - 0.5)>1e-6)
		{
			m_dScale += dAddScal;
			DisPlayImage(m_hImage, m_hWnd);
		}
	}
	else
	{
		if (fabs(m_dScale - dAddScal + 2)>1e-6)
		{
			m_dScale -= dAddScal;
			DisPlayImage(m_hImage, m_hWnd);
		}
	}

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}

//double angle = 0;
//double dpi = 3.38;
double x_base;
double y_base;
//int factor = 1;
BOOL CMFCApplication1Dlg::PreTranslateMessage(MSG* pMsg)
{
	POINT ptTmp;
	GetCursorPos(&ptTmp);//获取鼠标位置 
	CRect Rect;
	CRect rcPIC;
	CWnd *pPICWnd = GetDlgItem(IDC_PIC);
	CDC *pDCPIC = pPICWnd->GetDC();
	memset(Rect, 0, sizeof(CRect));
	pPICWnd->ClientToScreen(Rect);
	//UpdateData(TRUE);
	//坐标转换
	mousex = ptTmp.x - Rect.left;
	mousey = ptTmp.y - Rect.top;
	pPICWnd = GetDlgItem(IDC_PIC);
	pPICWnd->GetClientRect(&rcPIC);
	//判断鼠标是否在图像控件内 
	if (rcPIC.PtInRect(ptTmp))
	{
		if (pMsg->message == WM_LBUTTONDOWN)
		{
			m_ptStart = ptTmp;
			m_ptEnd = ptTmp;
			//鼠标单击事件代码 
			//HDevWindowStack::Push(m_hWnd);
			//if (HDevWindowStack::IsOpen())
			//{
			//	/*while (true)
			//	{*/
			//		/*GetMposition(hvWindowID, &hv_mouseR, &hv_mouseC, &hv_Button);
			//		cout << "R:" << hv_mouseR.I() << endl;
			//		cout << "C:" << hv_mouseC.I() << endl;*/
			//	DispObj(m_hImage, HDevWindowStack::GetActive());
			//	dxf_scale(&ho_Contours, 1/dpi, &ho_ContoursScaled, &x_base, &y_base);
			//	dxf_transform(&ho_ContoursScaled, ptTmp.x, ptTmp.y, angle, &ho_ModelTrans);
			//	DispObj(ho_ModelTrans, HDevWindowStack::GetActive());
			//	//}
			//}
		}
		else if (pMsg->message == WM_LBUTTONUP)
		{
			m_ptEnd = ptTmp;
			m_nWidthOffset += (m_ptEnd.x - m_ptStart.x);
			m_nHeightOffset += (m_ptEnd.y - m_ptStart.y);
			DisPlayImage(m_hImage, m_hWnd);
		}
		/*else if (pMsg->message == WM_KEYDOWN)
		{*/
		else if (pMsg->wParam == 'A')            //dxf逆时针旋转
		{
			DispObj(m_hImage, HDevWindowStack::GetActive());
			dxf_scale(&ho_Contours, 1 / dpi, &ho_ContoursScaled, &x_base, &y_base);
			angle++;
			dxf_transform(&ho_ContoursScaled, ptTmp.x, ptTmp.y, angle, &ho_ModelTrans);
			DispObj(ho_ModelTrans, HDevWindowStack::GetActive());
		}
		else if (pMsg->wParam == 'D')            //dxf顺时针旋转
		{
			DispObj(m_hImage, HDevWindowStack::GetActive());
			dxf_scale(&ho_Contours, 1 / dpi, &ho_ContoursScaled, &x_base, &y_base);
			angle--;
			dxf_transform(&ho_ContoursScaled, ptTmp.x, ptTmp.y, angle, &ho_ModelTrans);
			DispObj(ho_ModelTrans, HDevWindowStack::GetActive());
		}
		else if (pMsg->wParam == 'W')            //dxf放大
		{
			DispObj(m_hImage, HDevWindowStack::GetActive());
			dpi += 0.01;
			dxf_scale(&ho_Contours, 1 / dpi, &ho_ContoursScaled, &x_base, &y_base);
			dxf_transform(&ho_ContoursScaled, ptTmp.x, ptTmp.y, angle, &ho_ModelTrans);
			DispObj(ho_ModelTrans, HDevWindowStack::GetActive());
		}
		else if (pMsg->wParam == 'S')            //dxf缩小
		{
			DispObj(m_hImage, HDevWindowStack::GetActive());
			dpi -= 0.01;
			dxf_scale(&ho_Contours, 1 / dpi, &ho_ContoursScaled, &x_base, &y_base);
			dxf_transform(&ho_ContoursScaled, ptTmp.x, ptTmp.y, angle, &ho_ModelTrans);
			DispObj(ho_ModelTrans, HDevWindowStack::GetActive());
		}
		else if (pMsg->wParam == VK_SPACE)            //dxf平移
		{
			//HObject  ho_ContourCross, ho_PolygonsCross;
			DispObj(m_hImage, HDevWindowStack::GetActive());
			dxf_scale(&ho_Contours, 1 / dpi, &ho_ContoursScaled, &x_base, &y_base);
			dxf_transform(&ho_ContoursScaled, mousex, mousey, angle, &ho_ModelTrans);
			//GenCrossContourXld(&ho_ContourCross, mousey, mousex, 88, 0);
			//GenPolygonsXld(ho_ContourCross, &ho_PolygonsCross, "ramer", 2);
			//if (HDevWindowStack::IsOpen())
			//DispObj(ho_PolygonsCross, HDevWindowStack::GetActive());
			DispObj(ho_ModelTrans, HDevWindowStack::GetActive());
			return TRUE;
		}
		else if (pMsg->wParam == VK_RETURN)
		{
			WriteContourXldDxf(ho_ModelTrans, "C:\\Users\\AI-009\\Desktop\\result.dxf");
			return TRUE;
		}
		//}
		//else if (pMsg->message == WM_MOUSEWHEEL)
		//{
		//	CPoint pt;
		//	short zDelta = 1;
		//	// 此功能要求 Windows Vista 或更高版本。

		//	// _WIN32_WINNT 符号必须 >= 0x0600。

		//	// TODO: 在此添加消息处理程序代码和/或调用默认值

		//	CRect rtImage;

		//	GetDlgItem(IDC_PIC)->GetWindowRect(&rtImage);

		//	if (rtImage.PtInRect(pt) && m_hImage.IsInitialized())

		//	{
		//		Hlong ImagePtX, ImagePtY;

		//		Hlong Row0, Col0, Row1, Col1;

		//		double Scale = 0.1;

		//		if (zDelta>0)

		//		{
		//			ImagePtX = m_dDispImagePartCol0 + (pt.x - rtImage.left) / (rtImage.Width() - 1.0)*(m_dDispImagePartCol1 - m_dDispImagePartCol0);

		//			ImagePtY = m_dDispImagePartRow0 + (pt.y - rtImage.top) / (rtImage.Height() - 1.0)*(m_dDispImagePartRow1 - m_dDispImagePartRow0);

		//			Row0 = ImagePtY - 1 / (1 - Scale)*(ImagePtY - m_dDispImagePartRow0);

		//			Row1 = ImagePtY - 1 / (1 - Scale)*(ImagePtY - m_dDispImagePartRow1);

		//			Col0 = ImagePtX - 1 / (1 - Scale)*(ImagePtX - m_dDispImagePartCol0);

		//			Col1 = ImagePtX - 1 / (1 - Scale)*(ImagePtX - m_dDispImagePartCol1);

		//			m_dDispImagePartRow0 = Row0;

		//			m_dDispImagePartCol0 = Col0;

		//			m_dDispImagePartRow1 = Row1;

		//			m_dDispImagePartCol1 = Col1;

		//		}

		//		else

		//		{
		//			ImagePtX = m_dDispImagePartCol0 + (pt.x - rtImage.left) / (rtImage.Width() - 1.0)*(m_dDispImagePartCol1 - m_dDispImagePartCol0);

		//			ImagePtY = m_dDispImagePartRow0 + (pt.y - rtImage.top) / (rtImage.Height() - 1.0)*(m_dDispImagePartRow1 - m_dDispImagePartRow0);

		//			Row0 = ImagePtY - 1 / (1 + Scale)*(ImagePtY - m_dDispImagePartRow0);

		//			Row1 = ImagePtY - 1 / (1 + Scale)*(ImagePtY - m_dDispImagePartRow1);

		//			Col0 = ImagePtX - 1 / (1 + Scale)*(ImagePtX - m_dDispImagePartCol0);

		//			Col1 = ImagePtX - 1 / (1 + Scale)*(ImagePtX - m_dDispImagePartCol1);

		//			m_dDispImagePartRow0 = Row0;

		//			m_dDispImagePartCol0 = Col0;

		//			m_dDispImagePartRow1 = Row1;

		//			m_dDispImagePartCol1 = Col1;

		//		}

		//		ShowImage();

		//	}
		//}
	}
	UpdateData(FALSE);
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CMFCApplication1Dlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	HTuple hv_DxfStatus;
	HTuple hv_ImagePath = "C:\\Users\\AI-009\\Desktop\\metal-parts-08.png";
	m_dScale = 0;//重置
	m_nHeightOffset = 0;
	m_nWidthOffset = 0;
	ReadImage(&m_hImage, hv_ImagePath);
	GetImageSize(m_hImage, &m_hWidth, &m_hHeight);
	SetPart(m_hWnd, 0, 0, m_hHeight - 1, m_hWidth - 1);
	ReadContourXldDxf(&ho_Contours, "C:\\Users\\AI-009\\Desktop\\result.dxf", HTuple(),
		HTuple(), &hv_DxfStatus);
	HDevWindowStack::Push(m_hWnd);
	if (HDevWindowStack::IsOpen())
	{
		DispObj(m_hImage, HDevWindowStack::GetActive());
		DispObj(ho_Contours, HDevWindowStack::GetActive());
	}
}
