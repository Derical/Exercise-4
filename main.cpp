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

}



int main()
{
	// ------------------------- Exercise 1 -------------------------
	Exercise1();



	waitKey(0);
	return 0;
}