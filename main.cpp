#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;

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

int main()
{
	// 练习一
	//Exercise1();
	//练习二
	Exercise2();
	waitKey(0);
}