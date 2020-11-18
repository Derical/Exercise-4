#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;

void Exercise1( )
{
	cv::Mat src = imread("C:\\Users\\STAR ZHANG\\Pictures\\cv81.png");
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
				drawContours(src,contours,i,Scalar(0,255,255),-1,8);
			}
		}
	}
	imshow("[效果图]", src);
	waitKey(0);
}


int main()
{
	// 练习一
	Exercise1();

	waitKey(0); 
}