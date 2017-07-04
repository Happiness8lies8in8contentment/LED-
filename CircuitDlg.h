
// CircuitDlg.h : 头文件
//

#pragma once
#include "opencv2/opencv.hpp"


using namespace cv;

// CCircuitDlg 对话框
class CCircuitDlg : public CDialogEx
{
// 构造
public:
	CCircuitDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CIRCUIT_DIALOG };

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
	afx_msg void OnBnClickedBtnOpen();
	Mat m_srcImg,m_srcImg1;

	void ShowImage(Mat& img, int nID);
	void Otsu2Threshold(Mat src, Mat& dst);
	double _GetRotationAngle_(Mat binaryImg);
	Mat RotateTo(Mat grayImg, double angle);
	Mat GetRec(Mat Img, vector<Rect>& FilterRectVector);
	Mat FindDefective(Mat Img, vector<Rect>& FilterRectVector);

	Mat src, src_gray;
	Mat dst, detected_edges;
	afx_msg void OnBnClickedBtnJc();
	//afx_msg void OnEnChangeEdit1();
	int m_rect_size;
    int rectNumber; 
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedBtnSet();
	int m_stNumber;
	int stNumber;
	CString m_outPut;
};
