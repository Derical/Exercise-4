#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;

// ------------------------- Exercise1 -------------------------
void Exercise1( )
{
	cv::Mat src = imread("C:\\Users\\STAR ZHANG\\Pictures\\cv81.png");
	cv::Mat disMat;
	src.copyTo(disMat);
	imshow("[原图]",src);

	// 转换为单通道灰度图
	cv::Mat gray;
	cvtColor(src,gray,COLOR_BGR2GRAY);

	// 二值化
	cv::Mat tmp;
	threshold(gray,tmp,100, 255,THRESH_OTSU);
	imshow("[二值化后的图像]",tmp);

	// 反色
	tmp = 255 - tmp;
	imshow("[反色后的图像]", tmp);

	// 利用findContours函数寻找轮廓
	std::vector<vector<Point>> contours;
	std::vector<Vec4i> hierarchy;
	findContours(tmp,contours,hierarchy,RETR_EXTERNAL,CHAIN_APPROX_NONE);
	cout << contours.size() << endl;

	// 获得最小外接四边形
	for (int i = 0; i < contours.size(); ++i)
	{
		RotatedRect rbox = minAreaRect(contours[i]);
		int height = rbox.size.height;
		int width  = rbox.size.width;

		//限制宽长比和区域大小
		if (height != 0 && width != 0)
		{
			float wdrat = (float)width / height;
			if (wdrat > 0.98 && wdrat < 1.02 && width > 40 && height > 40)
			{
				cout << "The width is " << rbox.size.width << endl;
				cout << "The height is " << rbox.size.height << endl;
				cout << "The width divided by the height is " << wdrat << endl;
				drawContours(disMat,contours,i,Scalar(0,255,255),-1,8);
			}
		}
	}
	imshow("[效果图]", disMat);
	waitKey(0);
}
// ------------------------- Exercise2 -------------------------
void Exercise2()
{
	cv::Mat src = imread("C:\\Users\\STAR ZHANG\\Pictures\\cv82.jpg");
	imshow("[原图]", src);
	cv::Mat gray, bin;
	cv::Mat disMat;
	src.copyTo(disMat);

	// 转换为灰度图
	cvtColor(src,gray,COLOR_BGR2GRAY);

	// 转换为二值图
	threshold(gray,bin,150,255,THRESH_BINARY);
	imshow("[二值图]",bin);

	// 寻找轮廓
	std::vector<vector<Point>> contours;
	std::vector<Vec4i> hierarchy;
	findContours(bin, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	cout << "轮廓的个数为 :" << contours.size() << std::endl;
	// 获得最小外接四边形
	for (int i = 0; i < contours.size(); ++i)
	{
		RotatedRect rbox = minAreaRect(contours[i]);
		int height = rbox.size.height;
		int width = rbox.size.width;

		//限制宽长比
		if (height != 0 && width != 0)
		{
			float wdrat = (float)width / height;
			if (wdrat > 0.9 && wdrat < 1.1)
			{
				cout << "The width is " << rbox.size.width << endl;
				cout << "The height is " << rbox.size.height << endl;
				cout << "The width divided by the height is " << wdrat << endl;

				//绘制轮廓
				cv::Point2f vtx[4];
				rbox.points(vtx);
				for (int i = 0; i < 4; ++i)
					cv::line(disMat, vtx[i], vtx[i < 3 ? i + 1 : 0], cv::Scalar(0, 255, 255), 2);
			}
		}
	}
	imshow("[效果图]",disMat);
	waitKey(0);
}
// ------------------------- Exercise3 -------------------------

void Exercise3()
{
	//设置可调整图片大小的窗口来显示原图
	cv::Mat src = imread("C:\\Users\\STAR ZHANG\\Pictures\\cv83.jpg");
	//namedWindow("[原图]",WINDOW_NORMAL);
	//imshow("[原图]",src);
	cv::Mat disMat;
	src.copyTo(disMat);
	
	/* ---------------------------- 分离RGB三通道 -----------------------------
	*		在Image Watch中观察发现效果并不好
	*		换用HSV空间
	*/
	//定义vector作为三个通道的容器
	//std::vector<cv::Mat> channels;
	//cv::split(src, channels);
	//cv::Mat Blue = channels.at(0);
	//cv::Mat Green = channels.at(1);
	//cv::Mat Red = channels.at(2);

	// ------------------------------------------------------------------------

	// 转换为HSV
	int iLowH = 156;			
	int iHighH = 180;
	int iLowS = 43;
	int iHighS = 255;
	int iLowV = 46;
	int iHighV = 255;
	cv::Mat hsvMat;
	vector<Mat> hsvSplit;
	cvtColor(src,hsvMat,COLOR_BGR2HSV);
	split(hsvMat, hsvSplit);

	// 直方图均值化，增强图像亮度及对比度
	equalizeHist(hsvSplit[2], hsvSplit[2]);
	merge(hsvSplit, hsvMat);
	
	// 二值化
	Mat thresholdedMat;
	inRange(hsvMat, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), thresholdedMat);

	// 闭运算
	Mat tmp;
	Mat kernel = getStructuringElement(MORPH_ELLIPSE,Size(5,5));
	morphologyEx(thresholdedMat,tmp,MORPH_CLOSE,kernel,Point(-1,-1),16);
	//namedWindow("tmp",WINDOW_NORMAL);
	//imshow("tmp", tmp);


	// 寻找轮廓
	std::vector<vector<Point>> contours;
	std::vector<Vec4i> hierarchy;
	findContours(tmp, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	cout << "轮廓的个数为 :" << contours.size() << std::endl;

	// 获得最小外接四边形
	for (int i = 0; i < contours.size(); ++i)
	{
		RotatedRect rbox = minAreaRect(contours[i]);
		int height = rbox.size.height;
		int width = rbox.size.width;

		//限制宽长比
		if (height != 0 && width != 0)
		{
			float wdrat = (float)width / height;
			if (wdrat >= 0.8 && wdrat <= 1.2)
			{
				cout << "The width is " << rbox.size.width << endl;
				cout << "The height is " << rbox.size.height << endl;
				cout << "The width divided by the height is " << wdrat << endl;

				//绘制轮廓
				cv::Point2f vtx[4];
				rbox.points(vtx);
				for (int i = 0; i < 4; ++i)
					cv::line(disMat, vtx[i], vtx[i < 3 ? i + 1 : 0], cv::Scalar(0, 255, 255), 4);
			}
		}
	}
	namedWindow("[效果图]", WINDOW_GUI_NORMAL);
	imshow("[效果图]",disMat);
	waitKey(0);
}

int main()
{
	// 练习一
	//Exercise1();
	// 练习二
	//Exercise2();
	// 练习三
	Exercise3();
	waitKey(0);
}