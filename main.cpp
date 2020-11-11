#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

// ------------------------- Exercise 1 -------------------------
void Exercise1()
{
	Mat src = imread("C:\\Users\\STAR ZHANG\\Pictures\\cat.jpg");
	Mat dst;
	//旋转-40°，缩放尺寸1
	float angle = -10.0, scale = 1;
	cv::Point2f center(src.cols / 2.0, src.rows / 2.0);							// 获取中心坐标
	cv::Mat rot = cv::getRotationMatrix2D(center, angle, scale);				// 获得旋转变换矩阵
	cv::Rect bbox = cv::RotatedRect(center, src.size(), angle).boundingRect();	// 获取外接四边形
	// 调整仿射矩阵参数
	rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
	rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;
	// 仿射变换
	cv::warpAffine(src, dst, rot, bbox.size());
	imshow("[原图]", src);
	imshow("[变换后]", dst);
	waitKey(0);
}
// ------------------------- Exercise 2 -------------------------
// 霍夫变换
void Exercise2()
{
	Mat src = imread("C:\\Users\\STAR ZHANG\\Pictures\\18.jpg");
	imshow("[原图]", src);
	Mat mid;
	Mat dst;
	Mat gray;
	cvtColor(src,gray, COLOR_BGR2GRAY);
	Canny(gray,mid,50,200,3);
	// 进行边缘检测
	// ----- 选择用line承载直线参数 -----
	std::vector<cv::Vec2f> lines;
	HoughLines(mid,lines,1,CV_PI/180,100);
	//绘制直线
	std::vector<cv::Vec2f>::iterator it = lines.begin();
	for (; it != lines.end(); ++it)
	{
		float rho = (*it)[0], theta = (*it)[1];
		cv::Point pt1, pt2;
		double a = cos(theta);
		double b = sin(theta);
		double x0 = a * rho;
		double y0 = b * rho;
		pt1.x = cv::saturate_cast<int>(x0 + 1000 * (-b));
		pt1.y = cv::saturate_cast<int>(y0 + 1000 * (a));
		pt2.x = cv::saturate_cast<int>(x0 - 1000 * (-b));
		pt2.y = cv::saturate_cast<int>(y0 - 1000 * (a));
		cv::line(src, pt1, pt2, cv::Scalar(0, 0, 255), 1);
	}

	imshow("[绘制直线后]", src);
	waitKey();
}
int main()
{
	// ------------------------- Exercise 1 -------------------------
	//Exercise1();

	// ------------------------- Exercise 2 -------------------------
	Exercise2();

	waitKey(0);
	return 0;
}