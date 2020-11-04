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
	cv::waitKey(0);
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
	//获得旋转变换矩阵
	const Mat affine_matrix = getRotationMatrix2D(center, angle, scale);
	
	warpAffine(src, dst, affine_matrix, src.size());
	imshow("[原图]", src);
	imshow("[旋转-40°]", dst);
	cv::waitKey(0);
}
// ------------------------- Exercise 3 -------------------------
// 仿射变换
// 根据三组点求仿射变换矩阵
int Affine_Transformation()
{
	Mat dst;
	Mat src = imread("C:\\Users\\STAR ZHANG\\Pictures\\cat.jpg");
	if (src.empty())
		return -1;
	//变换前的三点坐标
	const Point2f src_pt[] =
	{
		Point2f(200,200),
		Point2f(250,250),
		Point2f(200,100)
	};
	//变换后的三点坐标
	const Point2f dst_pt[] =
	{
		Point2f(300,100),
		Point2f(300,50),
		Point2f(200,100)
	};
	//计算仿射变换举证
	const Mat affine_matrix = getAffineTransform(src_pt, dst_pt);
	//仿射变换
	warpAffine(src,dst,affine_matrix,src.size());
	imshow("[原图]",src);
	imshow("[仿射变换后]", dst);
	cv::waitKey();
}
// ------------------------- Exercise 4 -------------------------
// 投影变换
int Projection_Transformation()
{
	Mat dst;
	Mat src = imread("C:\\Users\\STAR ZHANG\\Pictures\\cat.jpg");
	if (src.empty())
		return -1;
	
	//变换前的四点坐标
	Point2f pts1[] =
	{
		Point2f(150,150),
		Point2f(150,300),
		Point2f(350,300),
		Point2f(350,150),
	};
	//变换后的四点坐标
	Point2f pts2[] =
	{
		Point2f(200,150),
		Point2f(200,300),
		Point2f(340,270),
		Point2f(340,180),
	};
	//计算透视变换矩阵
	Mat perspective_matrix = getPerspectiveTransform(pts1,pts2);
	//透视变换
	warpPerspective(src,dst,perspective_matrix,src.size());
	imshow("[原图]",src);
	imshow("[经投影变换后]",dst);
	cv::waitKey(0);
}
// ------------------------- Exercise 5 -------------------------
// 图像矫正
void Image_Rectification()
{
	Mat src = imread("C:\\Users\\STAR ZHANG\\Pictures\\lena.jpg");
	Mat dst,gray;
	//转换为单通道的灰度图方便寻找特征
	cvtColor(src,gray,COLOR_BGR2GRAY);
	/* 遍历边缘两行两列
	 * 找出灰度值最小的四个点
	 */
	int height = gray.rows;
	int weight = gray.cols;
	//遍历第一行
	int min = 0;
	for (int i = 1; i < weight; ++i)
	{
		if (gray.at<uchar>(0, i) < gray.at<uchar>(0, min))
			min = i;
	}
	//遍历最后一行
	int min2 = 0;
	for (int i = 0; i < weight; ++i)
	{
		if (gray.at<uchar>(height - 1, i) < gray.at<uchar>(height - 1, min2))
			min2 = i;
	}
	//遍历第一列
	int min3 = 0;
	for (int i = 0; i < height; ++i)
	{
		if (gray.at<uchar>(i, 0) < gray.at<uchar>(min3, 0))
			min3 = i;
	}
	//仿射变换前的点
	const Point2f src_pt[] =
	{
		Point2f(min,0),
		Point2f(min2,height - 1),
		Point2f(0,min3),
	};
	//仿射变换后的点
	const Point2f dst_pt[] =
	{
		Point2f(0,0),
		Point2f(weight - 1,height - 1),
		Point2f(0,height - 1),
	};
	//计算仿射变换矩阵
	const Mat affine_matrix = getAffineTransform(src_pt, dst_pt);
	//仿射变换
	warpAffine(src, dst, affine_matrix, src.size());
	imshow("[原图]", src);
	imshow("[图形矫正后]", dst);
	cv::waitKey(0);
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

	//Affine_Transformation();
	
	// ------------------------- Exercise 4 -------------------------
	// 投影变换

	//Projection_Transformation();

	// ------------------------- Exercise 5 -------------------------
	// 图像矫正

	Image_Rectification();

	return 0;

}