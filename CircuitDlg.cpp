
// CircuitDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CCircuitDlg �Ի���




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


// CCircuitDlg ��Ϣ�������

BOOL CCircuitDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCircuitDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCircuitDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCircuitDlg::OnBnClickedBtnOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE,_T(".bmp"),_T("*.bmp"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("λͼ�ļ� (*.bmp)|*.bmp|JPEG�ļ� (*.jpg)|*.jpg|PNG�ļ� (*.png)|*.png||"));//ѡ��ͼƬ
	if (IDOK==dlg.DoModal())//��ѡ���ͼƬ
	{
		string filename=dlg.GetPathName();//��ȡͼƬ��·�����ļ���
		m_srcImg = imread(filename);//��ͼƬ������ȫ�ֱ���theImage������
	}
	ShowImage(m_srcImg, IDC_SRC_IMG);
	rectNumber=0;
	SetDlgItemText(IDC_EDIT3,NULL);

}
void CCircuitDlg::ShowImage(Mat& img, int nID)//��ͼƬ�ؼ�����ʾһ��ͼƬ
{
	CWnd* pimgShowCtrl = this->GetDlgItem(nID); //���nID�ؼ��ľ��
	CRect ctrlRect;		//����������Ա���picture�ؼ��Ĵ�С
	pimgShowCtrl->GetClientRect(&ctrlRect); //���picture�ؼ��Ĵ�С

	CDC* pDC = pimgShowCtrl->GetDC(); //����豸�����ģ���Ϊ������ʾ�����Ĳ�������Ҫ��

	//��ʼ��һ��λͼ��Ϣͷ
	BITMAPINFOHEADER BHEADER = {40, 0, 0, 1, 0, BI_RGB, 0, 0, 0, 0};

	//��ô���ͼ��������Ϣ����ֵ��λͼ��Ϣͷ��
	int width, height, depth, channel, width1;
	width = img.cols;
	height = img.rows;
	depth = img.depth();
	channel = img.channels();

	int bits, colors, i;
	bits = ( 8<< (depth/2) )*channel;//8����0��1��2��3�ֱ����8��16��32��64��ÿ��������ռ��λ��
	if(bits > 8)
	{
		colors = 0;//���ɫλͼû����ɫ��
	}
	else
	{
		colors = ( 1<<bits );//�����ɫ��λͼ����Ӧ����ɫ��
	}

	//�����ɫͼ��ʱ����ÿ������ռ�ĸ��ֽڣ������ͽ�������ɫͼ���4�ֽڱ߽��������
	if (bits == 24)
	{
		bits = 32;
	}

	//��λͼ��Ϣͷ��ֵ
	//���Ҷ�ͼ��ʱ������ÿ������ռһ���ֽڣ�������ÿ�����أ���ͼ��Ŀ�ȣ�����4�ֽڱ߽����
	if(bits == 8)
	{
		width1 = (width*8 + 31)/32 * 4; //4�ֽڱ߽������ͼ��Ŀ��
		BHEADER.biWidth = width1;
	}
	else
	{
		BHEADER.biWidth = width;//���ɫͼ��ʱ��ͼ������ؿ�Ȼ���ԭ��ͼ������ؿ��
	}
	BHEADER.biHeight = height;			
	BHEADER.biBitCount = bits;

	LPBITMAPINFO lpBitsInfo = (LPBITMAPINFO) malloc(40 + 4*colors);//����λͼ��Ϣָ������������ڴ�

	memcpy(lpBitsInfo, &BHEADER, 40);//��λͼ��Ϣͷ�����ݸ��Ƶ�λͼ��Ϣ��

	//��λͼ��Ϣ������ɫ��ĸ�ֵ
	if(colors == 256)
	{
		RGBQUAD* colorsTab = lpBitsInfo->bmiColors;
		for(i=0; i<256; i++)
		{	
			colorsTab[i].rgbBlue = colorsTab[i].rgbGreen = colorsTab[i].rgbRed = (BYTE)i;
			colorsTab[i].rgbReserved = 0;
		}	
	}

	//======�ߵ�����
	//======Mat �д������´棬��bitmap�д������ϴ档  ���Ǵ������ң�����bitmapÿһ�����ռһ�������ֽڣ�������ɫͼ��Ϊ��4�ֽڶ��룩��
	//		Ĭ��255���Ҷ�ͼ���������ֶ��뷽��
	unsigned char *m_pDibBits;//�洢ͼ���е����ݣ��������ϣ���������
	//x�� * Y��
	int x,y; 
	unsigned char * bmpdata; // �����а���
	unsigned char * imgData = img.data;
	if (bits == 8)
	{	
		m_pDibBits = new unsigned char[width1 * height];//ע��˴��õ���width1��������ͼ������ؿ�ȣ�������width

		//��imgData�еĵ�һ�и��Ƶ�  m_pDibBits �����һ��,���εߵ�
		for (x=0;  x<height;  x++ )
		{
			bmpdata = m_pDibBits + (height-1-x)*width1;
			memcpy(bmpdata,imgData,width); // Mat�п���width���ֽڣ�����width1
			imgData = imgData + width; // Mat�п���width���ֽڣ�����width1
		}
	} 
	else if (bits == 32)
	{
		m_pDibBits = new unsigned char[ width * height*4 ];

		//��imgData�еĵ�һ�и��Ƶ�  m_pDibBits �����һ��,���εߵ�
		for (x=0;  x<height;  x++ )
		{
			bmpdata = m_pDibBits + (height-1-x)*width*4;
			for (y = 0; y<width; y++)
			{
				memcpy(bmpdata,imgData,3);
				bmpdata[3] = 255;   // ע�͵� û��Ӱ��
				bmpdata = bmpdata+4;
				imgData = imgData+3;
			}    
		}
	}

	//��ʾͼ�񲿷�
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

	//�ͷ������Դ
	pimgShowCtrl->ReleaseDC(pDC);
	free(lpBitsInfo);
	delete []m_pDibBits;
}
//////////////////////////////////////////////////////////////////////////
//Otsu1Binary���ܣ���򷨶�ֵ��
//������   src������Ҷ�ͼ��   
//		   dst����ֵ��ͼ��
//����ֵ����
void CCircuitDlg::Otsu2Threshold(Mat src, Mat& dst)
{
	Mat img = src;
	dst.create(src.size(), src.type());
	CV_Assert(1 == img.channels());

	int height = img.rows;
	int width  = img.cols;
	int Threshold1 = 0;//��ֵ
	int Threshold2 = 0;//��ֵ
	double gSum_object;//��һ��,ǰ���Ҷ���ֵ
	double gSum_middle;
	double gSum_blackground;//�ڶ��࣬�����Ҷ���ֵ

	double N_object = 0;//ǰ��������
	double N_middle = 0;
	double N_blackground = 0;//����������

	double u0 = 0;//ǰ������ƽ���Ҷ�
	double u1 = 0;
	double u2 = 0;//��������ƽ���Ҷ�
	double w0 = 0;//ǰ�����ص���ռ����ͼ��ı���Ϊ��0
	double w1 = 0;
	double w2 = 0;//�������ص���ռ����ͼ��ı���Ϊ��1
	double u = 0;//��ƽ���Ҷ�
	double tempg = -1;//��ʱ��䷽��
	double g = -1;//��䷽��
	double Histogram[256]={0};//�Ҷ�ֱ��ͼ
	double N_allpixel = width * height;//��������
	for(int k = 0; k < height; k++)
	{
		//����ֱ��ͼ
		uchar* data = img.ptr<uchar>(k);
		for(int n = 0; n < width; n++)
		{
			Histogram[data[n]]++;
		} 
	}


	//������ֵ
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
		//if(0 == N_object) continue;//û��ǰ������ѭ��
		for (int j = i+10; j < 256; j++)
		{
			gSum_object = 0;
			gSum_middle = 0;
			gSum_blackground = 0;

			N_middle = N_allpixel - N_object - N_blackground;
			w0 = N_object / N_allpixel;
			w2 = N_blackground / N_allpixel;
			w1 = 1 - w0 - w2;

			//��u0
			for (int k = 0; k <= i; k++)
			{
				gSum_object += k*Histogram[k];
			}
			u0 = gSum_object / N_object;

			//��u1
			for (int k = i+1; k <= j; k++)
			{
				gSum_middle += k*Histogram[k] ;
			}
			u1 = gSum_middle / N_middle;

			//��u2
			for(int k = j+1; k < 256; k++)
			{
				gSum_blackground += k*Histogram[k];
			}
			u2 = gSum_blackground / N_blackground;

			u = w0*u0 + w1*u1 + w2*u2;
			g = w0*(u - u0)*(u - u0) + w1*(u - u1)*(u - u1) + w2*(u - u2)*(u - u2); 

			if (tempg < g)//ͨ����䷽�����޸���ֵ
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
// _GetRotationAngle_���ܣ���ȡ��ת�Ƕȷ���2���ø÷���ʵ�֣��Ƕȸ�׼ȷ
// ������binaryImg������Ϊ��ֵͼ��
//����ֵ����ת�Ƕ�
double CCircuitDlg::_GetRotationAngle_(Mat binaryImg)
{
	///����ϴ�ֱ��
	//lines.clear();

	///��Ե���
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

	//�ϰ�ͼ���һ��ֱ��
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
				break;//ֻȡһ�У���ֹȡ����
			}
		}
	}

	double nDegree = 0;
	if ( Pointset[0].y > edgeImg.rows/5 )
	{  //��ͼ��ת����תͼ��
		flip(edgeImg, edgeImg, 0);
		imwrite("flip.bmp", edgeImg);
		nDegree += 180;
		Pointset.clear();

		//�زɼ���һ������
		for (int j = widthleft; j < widthright; j++)	
		{
			for (int i = 0; i < heightMid; i++)
			{
				if (edgeImg.ptr<uchar>(i)[j] != 0)
				{
					Pointset.push_back(Point(j, i));
					break;//ֻȡһ�У���ֹȡ����
				}
			}
		}
	}





	//�������ֱ��
	Vec4f line;

	//ֱ����Ϻ���
	fitLine(Mat(Pointset), line, CV_DIST_L2, 0, 0.01, 0.01);

	///�Ƕ�ֵ
	double l_fitAngle = atan((line[0]/line[1]))*180/CV_PI;
	l_fitAngle > 0 ? (l_fitAngle = 90 - l_fitAngle) : (l_fitAngle < 0 ? (l_fitAngle = (90 + l_fitAngle)) : (l_fitAngle = 0) );

	nDegree += l_fitAngle;


	return nDegree;
}
//////////////////////////////////////////////////////////////////////////
// RotateTo���ܣ���ת��ĳһ�Ƕ�
// ������grayImg������Ϊԭʼͼ��ĻҶ�ͼ��
//       angle: ��Ҫ��ת�ĽǶ�
//����ֵ����ת���ͼ��������ֵ������
Mat CCircuitDlg::RotateTo(Mat grayImg, double angle)
{
	/// ͼ����ת(����Ƕ�)
	float m[6];
	Mat M(2,3,CV_32F,m);
	Point center(static_cast<int>(grayImg.cols/2),static_cast<int>(grayImg.rows/2));
	M = getRotationMatrix2D(center, angle, 1);

	Mat dst(grayImg.size(), grayImg.type());
	warpAffine(grayImg, dst, M, grayImg.size(), CV_INTER_CUBIC, 0, Scalar(0));

	/// ����ֵ���ͼ���ֵ��
	Otsu2Threshold(dst, dst);

	return dst;
}
//////////////////////////////////////////////////////////////////////////
// GetRec���ܣ���ȡ���С�飬��8��2=16��
// ������Img������Ϊ��ֵͼ��
//       FilterRectVector: 16�����
//����ֵ��������ͼ���16������ϣ�������Χ�ľ���
Mat CCircuitDlg::GetRec(Mat Img, vector<Rect>& FilterRectVector)
{
	Mat threshold_output(Img.rows, Img.cols, CV_8UC1);
	//threshold_output = Img;
	Img.copyTo(threshold_output);
	vector<vector<Point> > contours; 
	vector<Vec4i> hierarchy;

	/// ʹ��Threshold����Ե
	//GaussianBlur( Img, Img, Size(3,3), 0, 0, BORDER_DEFAULT );
	//medianBlur(Img, Img, 3);
	//blur( Img, Img, Size(3,3) );
	//threshold( Img, threshold_output, 250, 255, THRESH_BINARY );
	//threshold_output = Img;

	//  �ҵ�����
	findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

	// ��ȡ����
	vector<vector<Point> > contours_poly( contours.size() );
	vector<Rect> boundRect( contours.size() );
	
	for( int i = 0; i < (int)contours.size(); i++ )
	{ 
		approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
		boundRect[i] = boundingRect( Mat(contours_poly[i]) );
		
	}
		
	//����Χ�ľ��ο�
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
				//����ʵ���޸ı߿���˿�Ϸ�
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

	return Img;//�ӿ��Χ��ͼ��
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
		{/// ����һ�е�8����
			VecRec1.push_back(FilterRectVector[i]);
			VecX1.push_back(FilterRectVector[i].x);

		} 
		else
		{ /// ����һ�е�8����
			VecRec2.push_back(FilterRectVector[i]);
			VecX2.push_back(FilterRectVector[i].x);

		}
	}

	return Img;

}

void CCircuitDlg::OnBnClickedBtnJc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		m_outPut="���ϸ�";
	}
	else
	{
		m_outPut="�ϸ�";
	}
	SetDlgItemText(IDC_EDIT3,m_outPut);
	ShowImage(AfterRotationImg, IDC_SRC_IMG1 );

}


void CCircuitDlg::OnBnClickedBtnSet()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	stNumber=GetDlgItemInt(IDC_EDIT2);
}
