
// CircuitDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Circuit.h"
#include "CircuitDlg.h"
#include "afxdialogex.h"
#include "Windows.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace cv;


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


// CCircuitDlg 对话框




CCircuitDlg::CCircuitDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCircuitDlg::IDD, pParent)
	, m_rect_size(0)
	, m_stNumber(0)
	, m_outPut(_T(""))
{
	//rectNumber = 0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCircuitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_rect_size);
	DDX_Text(pDX, IDC_EDIT2, m_stNumber);
	DDX_Text(pDX, IDC_EDIT3, m_outPut);
}

BEGIN_MESSAGE_MAP(CCircuitDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN, &CCircuitDlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_JC, &CCircuitDlg::OnBnClickedBtnJc)
//	ON_EN_CHANGE(IDC_EDIT1, &CCircuitDlg::OnEnChangeEdit1)

ON_BN_CLICKED(IDC_BTN_SET, &CCircuitDlg::OnBnClickedBtnSet)
END_MESSAGE_MAP()


// CCircuitDlg 消息处理程序

BOOL CCircuitDlg::OnInitDialog()
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCircuitDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCircuitDlg::OnPaint()
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
HCURSOR CCircuitDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCircuitDlg::OnBnClickedBtnOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE,_T(".bmp"),_T("*.bmp"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("位图文件 (*.bmp)|*.bmp|JPEG文件 (*.jpg)|*.jpg|PNG文件 (*.png)|*.png||"));//选择图片
	if (IDOK==dlg.DoModal())//打开选择的图片
	{
		string filename=dlg.GetPathName();//获取图片的路径及文件名
		m_srcImg = imread(filename);//将图片保存至全局变量theImage对象中
	}
	ShowImage(m_srcImg, IDC_SRC_IMG);
	rectNumber=0;
	SetDlgItemText(IDC_EDIT3,NULL);

}
void CCircuitDlg::ShowImage(Mat& img, int nID)//在图片控件中显示一张图片
{
	CWnd* pimgShowCtrl = this->GetDlgItem(nID); //获得nID控件的句柄
	CRect ctrlRect;		//定义变量用以保存picture控件的大小
	pimgShowCtrl->GetClientRect(&ctrlRect); //获得picture控件的大小

	CDC* pDC = pimgShowCtrl->GetDC(); //获得设备上下文，因为后面显示函数的参数中需要它

	//初始化一个位图信息头
	BITMAPINFOHEADER BHEADER = {40, 0, 0, 1, 0, BI_RGB, 0, 0, 0, 0};

	//获得传入图像的相关信息（赋值给位图信息头）
	int width, height, depth, channel, width1;
	width = img.cols;
	height = img.rows;
	depth = img.depth();
	channel = img.channels();

	int bits, colors, i;
	bits = ( 8<< (depth/2) )*channel;//8左移0、1、2、3分别代表8、16、32、64，每个像素所占的位数
	if(bits > 8)
	{
		colors = 0;//真彩色位图没有颜色表
	}
	else
	{
		colors = ( 1<<bits );//非真彩色的位图有相应的颜色表
	}

	//当真彩色图像时，让每个像素占四个字节，这样就解决了真彩色图像的4字节边界对齐问题
	if (bits == 24)
	{
		bits = 32;
	}

	//给位图信息头赋值
	//当灰度图像时，由于每个像素占一个字节，所以让每行像素（即图像的宽度）进行4字节边界对齐
	if(bits == 8)
	{
		width1 = (width*8 + 31)/32 * 4; //4字节边界对齐后的图像的宽度
		BHEADER.biWidth = width1;
	}
	else
	{
		BHEADER.biWidth = width;//真彩色图像时，图像的像素宽度还是原来图像的像素宽度
	}
	BHEADER.biHeight = height;			
	BHEADER.biBitCount = bits;

	LPBITMAPINFO lpBitsInfo = (LPBITMAPINFO) malloc(40 + 4*colors);//创建位图信息指针变量并分配内存

	memcpy(lpBitsInfo, &BHEADER, 40);//将位图信息头的数据复制到位图信息里

	//对位图信息进行颜色表的赋值
	if(colors == 256)
	{
		RGBQUAD* colorsTab = lpBitsInfo->bmiColors;
		for(i=0; i<256; i++)
		{	
			colorsTab[i].rgbBlue = colorsTab[i].rgbGreen = colorsTab[i].rgbRed = (BYTE)i;
			colorsTab[i].rgbReserved = 0;
		}	
	}

	//======颠倒数据
	//======Mat 中从上往下存，而bitmap中从下往上存。  都是从左往右，并且bitmap每一个点多占一个保留字节（针对真彩色图像，为了4字节对齐），
	//		默认255，灰度图像则不用这种对齐方法
	unsigned char *m_pDibBits;//存储图像中的数据，从下向上，从左向右
	//x行 * Y列
	int x,y; 
	unsigned char * bmpdata; // 负责行搬运
	unsigned char * imgData = img.data;
	if (bits == 8)
	{	
		m_pDibBits = new unsigned char[width1 * height];//注意此处用的是width1（对齐后的图像的像素宽度）而不是width

		//把imgData中的第一行复制到  m_pDibBits 的最后一行,依次颠倒
		for (x=0;  x<height;  x++ )
		{
			bmpdata = m_pDibBits + (height-1-x)*width1;
			memcpy(bmpdata,imgData,width); // Mat中拷贝width个字节，不是width1
			imgData = imgData + width; // Mat中拷贝width个字节，不是width1
		}
	} 
	else if (bits == 32)
	{
		m_pDibBits = new unsigned char[ width * height*4 ];

		//把imgData中的第一行复制到  m_pDibBits 的最后一行,依次颠倒
		for (x=0;  x<height;  x++ )
		{
			bmpdata = m_pDibBits + (height-1-x)*width*4;
			for (y = 0; y<width; y++)
			{
				memcpy(bmpdata,imgData,3);
				bmpdata[3] = 255;   // 注释掉 没有影响
				bmpdata = bmpdata+4;
				imgData = imgData+3;
			}    
		}
	}

	//显示图像部分
	SetStretchBltMode(pDC->GetSafeHdc(), COLORONCOLOR);
	int w = min(img.cols,ctrlRect.Width());
	int h = min(img.rows,ctrlRect.Height());

	StretchDIBits(pDC->GetSafeHdc(),
		0,
		0,
		w,
		h,
		0,
		0,
		width,
		height,
		m_pDibBits,
		lpBitsInfo,
		DIB_RGB_COLORS,
		SRCCOPY);

	//释放相关资源
	pimgShowCtrl->ReleaseDC(pDC);
	free(lpBitsInfo);
	delete []m_pDibBits;
}
//////////////////////////////////////////////////////////////////////////
//Otsu1Binary功能：大津法二值化
//参数：   src：输入灰度图像   
//		   dst：二值化图像
//返回值：无
void CCircuitDlg::Otsu2Threshold(Mat src, Mat& dst)
{
	Mat img = src;
	dst.create(src.size(), src.type());
	CV_Assert(1 == img.channels());

	int height = img.rows;
	int width  = img.cols;
	int Threshold1 = 0;//阈值
	int Threshold2 = 0;//阈值
	double gSum_object;//第一类,前景灰度总值
	double gSum_middle;
	double gSum_blackground;//第二类，背景灰度总值

	double N_object = 0;//前景像素数
	double N_middle = 0;
	double N_blackground = 0;//背景像素数

	double u0 = 0;//前景像素平均灰度
	double u1 = 0;
	double u2 = 0;//背景像素平均灰度
	double w0 = 0;//前景像素点数占整幅图像的比例为ω0
	double w1 = 0;
	double w2 = 0;//背景像素点数占整幅图像的比例为ω1
	double u = 0;//总平均灰度
	double tempg = -1;//临时类间方差
	double g = -1;//类间方差
	double Histogram[256]={0};//灰度直方图
	double N_allpixel = width * height;//总像素数
	for(int k = 0; k < height; k++)
	{
		//计算直方图
		uchar* data = img.ptr<uchar>(k);
		for(int n = 0; n < width; n++)
		{
			Histogram[data[n]]++;
		} 
	}


	//计算阈值
	double tmpBlack = 0;
	double tmpMiddle = 0;
	for (int i = 0; i < 256; i++)
	{
		N_object += Histogram[i];
		N_blackground = 0;
		for (int k = i+10; k < 256; k++)
		{
			N_blackground += Histogram[k];
		}
		//if(0 == N_object) continue;//没有前景跳出循环
		for (int j = i+10; j < 256; j++)
		{
			gSum_object = 0;
			gSum_middle = 0;
			gSum_blackground = 0;

			N_middle = N_allpixel - N_object - N_blackground;
			w0 = N_object / N_allpixel;
			w2 = N_blackground / N_allpixel;
			w1 = 1 - w0 - w2;

			//求u0
			for (int k = 0; k <= i; k++)
			{
				gSum_object += k*Histogram[k];
			}
			u0 = gSum_object / N_object;

			//求u1
			for (int k = i+1; k <= j; k++)
			{
				gSum_middle += k*Histogram[k] ;
			}
			u1 = gSum_middle / N_middle;

			//求u2
			for(int k = j+1; k < 256; k++)
			{
				gSum_blackground += k*Histogram[k];
			}
			u2 = gSum_blackground / N_blackground;

			u = w0*u0 + w1*u1 + w2*u2;
			g = w0*(u - u0)*(u - u0) + w1*(u - u1)*(u - u1) + w2*(u - u2)*(u - u2); 

			if (tempg < g)//通过类间方差来修改阈值
			{
				tempg = g;
				Threshold1 = (int)i;
				Threshold2 = (int)j;
				tmpBlack = N_object;
				tmpMiddle = N_middle;
			}

			N_blackground -= Histogram[j];

		}
	}

	// 	int MiddlePixel = 255;
	// 	if (tmpBlack > tmpMiddle)
	// 	{
	// 		MiddlePixel = 0;
	// 	}


	for (int y=0; y < height; y++)
	{ 
		uchar* dstdata = dst.ptr<uchar>(y);
		uchar* srcdata = src.ptr<uchar>(y);
		for (int x=0; x < width; x++)
		{ 

			if ((int)srcdata[x] >= (Threshold2)) 
				dstdata[x] = 0; 
			// 			if ((int)srcdata[x] > Threshold1 && (int)srcdata[x] <= Threshold2) 
			// 				dstdata[x] = MiddlePixel;
			// 			if ((int)srcdata[x] <= Threshold1) 
			else
				dstdata[x] = 255;
		} 
	}


}
//////////////////////////////////////////////////////////////////////////
// _GetRotationAngle_功能：获取旋转角度方法2，用该方法实现，角度更准确
// 参数：binaryImg：输入为二值图像
//返回值：旋转角度
double CCircuitDlg::_GetRotationAngle_(Mat binaryImg)
{
	///清除上次直线
	//lines.clear();

	///边缘检测
	Mat edgeImg;

	//Mat NewBinaryImg;
	Canny(binaryImg, edgeImg,0, 200, 3);
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;

	vector< vector<Point> > Newcontours;
	//findContours(binaryImg, contours,CV_RETR_LIST,CV_CHAIN_APPROX_NONE);
	findContours( edgeImg, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
	for (int i = 0; i < (int)contours.size(); i++)
	{
		double area=contourArea(contours[i]);
		if (area > 50)
		{
			Newcontours.push_back(contours[i]);
		}

	}

	Mat NewBinaryImg = Mat::zeros( binaryImg.size(), CV_8UC1 );
	NewBinaryImg += 255;
	for( int i = 0; i< (int)Newcontours.size(); i++ )
	{
		Scalar color = Scalar( 0 );
		drawContours( NewBinaryImg, Newcontours, i, color, 1, 4, hierarchy, 0, Point() );
	}





	// 	Mat Kernel_Close  =  Mat::ones(2,  7, CV_8UC1);
	// 	Mat Kernel_Open  =  Mat::ones(2, 15, CV_8UC1);
	// 
	// 	morphologyEx(binaryImg, binaryImg, MORPH_CLOSE, Kernel_Close, Point(-1,-1), 1, BORDER_DEFAULT, 0);  	
	// 	morphologyEx(binaryImg, binaryImg, MORPH_OPEN ,  Kernel_Open , Point(-1,-1), 1, BORDER_DEFAULT, 0);
	// 	imwrite("Close_Open.bmp", binaryImg);


	edgeImg = NewBinaryImg;
	//Canny(binaryImg, edgeImg,0, 200, 3);

	vector<Point> Pointset;

	//上半图像第一条直线
	int widthleft  = edgeImg.cols/8;
	int widthright = edgeImg.cols * 7 / 8;
	int heightMid  = edgeImg.rows / 4;
	for (int j = widthleft; j < widthright; j++)	
	{
		for (int i = 0; i < heightMid; i++)
		{
			if (edgeImg.ptr<uchar>(i)[j] != 0)
			{
				Pointset.push_back(Point(j, i));
				break;//只取一行，防止取多行
			}
		}
	}

	double nDegree = 0;
	if ( Pointset[0].y > edgeImg.rows/5 )
	{  //若图像翻转，则翻转图像
		flip(edgeImg, edgeImg, 0);
		imwrite("flip.bmp", edgeImg);
		nDegree += 180;
		Pointset.clear();

		//重采集第一行数据
		for (int j = widthleft; j < widthright; j++)	
		{
			for (int i = 0; i < heightMid; i++)
			{
				if (edgeImg.ptr<uchar>(i)[j] != 0)
				{
					Pointset.push_back(Point(j, i));
					break;//只取一行，防止取多行
				}
			}
		}
	}





	//储存拟合直线
	Vec4f line;

	//直线拟合函数
	fitLine(Mat(Pointset), line, CV_DIST_L2, 0, 0.01, 0.01);

	///角度值
	double l_fitAngle = atan((line[0]/line[1]))*180/CV_PI;
	l_fitAngle > 0 ? (l_fitAngle = 90 - l_fitAngle) : (l_fitAngle < 0 ? (l_fitAngle = (90 + l_fitAngle)) : (l_fitAngle = 0) );

	nDegree += l_fitAngle;


	return nDegree;
}
//////////////////////////////////////////////////////////////////////////
// RotateTo功能：旋转至某一角度
// 参数：grayImg：输入为原始图像的灰度图像
//       angle: 需要旋转的角度
//返回值：旋转后的图像，已做二值化处理
Mat CCircuitDlg::RotateTo(Mat grayImg, double angle)
{
	/// 图像旋转(任意角度)
	float m[6];
	Mat M(2,3,CV_32F,m);
	Point center(static_cast<int>(grayImg.cols/2),static_cast<int>(grayImg.rows/2));
	M = getRotationMatrix2D(center, angle, 1);

	Mat dst(grayImg.size(), grayImg.type());
	warpAffine(grayImg, dst, M, grayImg.size(), CV_INTER_CUBIC, 0, Scalar(0));

	/// 将插值后的图像二值化
	Otsu2Threshold(dst, dst);

	return dst;
}
//////////////////////////////////////////////////////////////////////////
// GetRec功能：获取间隔小块，共8×2=16块
// 参数：Img：输入为二值图像
//       FilterRectVector: 16块矩形
//返回值：在输入图像的16块矩形上，画出包围的矩形
Mat CCircuitDlg::GetRec(Mat Img, vector<Rect>& FilterRectVector)
{
	Mat threshold_output(Img.rows, Img.cols, CV_8UC1);
	//threshold_output = Img;
	Img.copyTo(threshold_output);
	vector<vector<Point> > contours; 
	vector<Vec4i> hierarchy;

	/// 使用Threshold检测边缘
	//GaussianBlur( Img, Img, Size(3,3), 0, 0, BORDER_DEFAULT );
	//medianBlur(Img, Img, 3);
	//blur( Img, Img, Size(3,3) );
	//threshold( Img, threshold_output, 250, 255, THRESH_BINARY );
	//threshold_output = Img;

	//  找到轮廓
	findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

	// 获取矩形
	vector<vector<Point> > contours_poly( contours.size() );
	vector<Rect> boundRect( contours.size() );
	
	for( int i = 0; i < (int)contours.size(); i++ )
	{ 
		approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
		boundRect[i] = boundingRect( Mat(contours_poly[i]) );
		
	}
		
	//画包围的矩形框
	Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
	double Width = 0, Hight = 0;
	for( int i = 0; i< (int)contours.size(); i++ )
	{
		Scalar color = Scalar(0);	
		if (boundRect[i].area()< 12000 && boundRect[i].area() > 500 )
		{
			Width = (double)boundRect[i].width;
			Hight = (double)boundRect[i].height;
			if (Hight>20  && Hight<60 && Width>/*120*/80 && Width</*160*/200 )
			{
				//按照实际修改边框，严丝合缝
				boundRect[i].x++;
				boundRect[i].y++;
				boundRect[i].width -= 3;         
				boundRect[i].height -= 3;
				FilterRectVector.push_back(boundRect[i]);
				rectangle( Img, boundRect[i].tl(), boundRect[i].br(), color,3, 4, 0 );
				rectNumber++;
			}
			
		}
		
	}

	return Img;//加框包围的图像
}
Mat CCircuitDlg::FindDefective(Mat Img, vector<Rect>& FilterRectVector)
{
	vector<Rect> VecRec1;
	vector< int> VecX1;
	vector<Rect> VecRec2;
	vector< int> VecX2;

	int l_tmp = FilterRectVector[0].y;
	for (int i = 0; i < (int)FilterRectVector.size(); i++)
	{
		if (FilterRectVector[i].y > l_tmp*0.5 && FilterRectVector[i].y < l_tmp*1.5)
		{/// 其中一行的8个块
			VecRec1.push_back(FilterRectVector[i]);
			VecX1.push_back(FilterRectVector[i].x);

		} 
		else
		{ /// 另外一行的8个块
			VecRec2.push_back(FilterRectVector[i]);
			VecX2.push_back(FilterRectVector[i].x);

		}
	}

	return Img;

}

void CCircuitDlg::OnBnClickedBtnJc()
{
	// TODO: 在此添加控件通知处理程序代码
	Mat src = m_srcImg;

	stNumber=GetDlgItemInt(IDC_EDIT2);
	cvtColor(src, src, CV_RGB2GRAY);
	//imwrite("gray.bmp", src);

	//CCircuitDlg pcb;
	Mat BinaryImg;
	Otsu2Threshold(src,BinaryImg); 
	//imwrite("BinaryImg.bmp", BinaryImg);

	//double RotationAnlge1 = pcb.GetRotationAngle(BinaryImg);
	double RotationAnlge2 = _GetRotationAngle_(BinaryImg);
	Mat AfterRotationImg = RotateTo(src, RotationAnlge2);
	//imwrite("rotation.bmp", AfterRotationImg);

	vector<Rect> filter1RectPoint;
	GetRec(AfterRotationImg, filter1RectPoint);
	//m_rect_size=int * contours.size();
    m_rect_size=rectNumber;
	SetDlgItemInt(IDC_EDIT1,m_rect_size,0);
	//imwrite("Contours.bmp", AfterRotationImg);
	if (rectNumber!=stNumber)
	{
		m_outPut="不合格";
	}
	else
	{
		m_outPut="合格";
	}
	SetDlgItemText(IDC_EDIT3,m_outPut);
	ShowImage(AfterRotationImg, IDC_SRC_IMG1 );

}


void CCircuitDlg::OnBnClickedBtnSet()
{
	// TODO: 在此添加控件通知处理程序代码
	stNumber=GetDlgItemInt(IDC_EDIT2);
}
