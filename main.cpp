#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

// ------------------------- Exercise 1 -------------------------
// Canny边缘检测
void Canny_Detect()
{
	int threshold1 = 10;
	int threshold2 = 60;
	Mat src = imread("C:\\Users\\STAR ZHANG\\Pictures\\cat.jpg");
	// 转换为灰度图
	Mat gray, dst;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	Canny(gray, dst, threshold1, threshold2);
	imshow("[原图]", src);
	imshow("[Canny边缘检测]", dst);
	waitKey(0);
}
// ------------------------- Exercise 2 -------------------------
// 仿射变化 自定义仿射矩阵
int Rotate()
{
	Mat dst;
	Mat src = imread("C:\\Users\\STAR ZHANG\\Pictures\\cat.jpg");
	if (src.empty())
		return -1;
	//旋转-40°，缩放尺寸1
	float angle = -10.0, scale = 1;
	//旋转中心为图像中心
	Point2f center(src.cols*0.5,src.rows*0.5);
	//获得变换矩阵
	const Mat affine_matrix = getRotationMatrix2D(center, angle, scale);
	
	warpAffine(src, dst, affine_matrix, src.size());
	imshow("[原图]", src);
	imshow("[旋转-40°]", dst);
	waitKey(0);
}
// ------------------------- Exercise 3 -------------------------
// 仿射变换
int Affine_Transformation()
{
	Mat src = imread("C:\\Users\\STAR ZHANG\\Pictures\\cat.jpg");
}
int main()
{
	// ------------------------- Exercise 1 -------------------------
	// Canny边缘检测

	//Canny_Detect();

	// ------------------------- Exercise 2 -------------------------
	// 仿射变换

	//Rotate();

	// ------------------------- Exercise 3 -------------------------
	// 仿射变换

	return 0;

}