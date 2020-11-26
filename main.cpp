#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
using namespace cv;
using namespace std;

// 计算输入图片的HOG
int calcHOG(Mat src,float * hist,int nAngle,int cellSize)
{
	// 计算各个像素的梯度强度和方向
	// 计算梯度和角度
	Mat gx, gy;
	Mat mag, angle;
	Sobel(src, gx, CV_32F, 1, 0, 1);
	Sobel(src, gy, CV_32F, 0, 1, 1);
	// x方向梯度，y方向梯度，梯度，角度，决定输出弧度/角度
	// 默认是弧度radians，可以选择角度degrees
	cartToPolar(gx, gy, mag, angle, true);

	//图像划分为16 * 16的cell
	int nX = src.cols / cellSize;
	int nY = src.rows / cellSize;

	int binAngle = 360 / nAngle;

	cv::Rect roi;
	roi.width  = cellSize;
	roi.height = cellSize;

	//图像分割为cell，按照cell分别计算直方图
	for (int i = 0;i < nY;++i)
		for (int j = 0; j < nX; ++j)
		{
			cv::Mat roiMat, roiMag, roiAgl;
			roi.x = j * cellSize;
			roi.y = i * cellSize;
			//赋值图像
			roiMat = src(roi);
			roiMag = mag(roi);
			roiAgl = angle(roi);
			//当前cell第一个元素在数组中的位置
			int head = (i * nX + j) * nAngle;

			for (int n = 0; n < roiMat.rows;++n)
				for (int m = 0; m < roiMat.cols; ++m)
				{
					int pos = (int)(roiAgl.at<float>(n, m) / binAngle);
					hist[head + pos] += roiMag.at<float>(n, m);
				}
		}

	return 1;
}

int main()
{
	cv::Mat hogTemplate = imread("hogTemplate.jpg",0);
	cv::Mat Img1 = imread("D:/!Study!/大三/大三上/数字图像处理DIP/Projects/Exercise 4/img1.jpg",0);
	cv::Mat Img2 = imread("img2.jpg",0);

	imshow("1", hogTemplate);
	imshow("2", Img1);
	imshow("3", Img2);


	// 角度量化为8
	int nAngle = 8;
	// cell尺寸为16 * 16
	int blockSize = 16;
	int nX = hogTemplate.cols / blockSize;
	int nY = hogTemplate.rows / blockSize;

	int bins = nX * nY * nAngle;

	//开辟内存存放直方图
	float * ref_hist = new float[bins];
	memset(ref_hist, 0, sizeof(float) * bins);
	float * pl_hist = new float[bins];
	memset(pl_hist, 0, sizeof(float) * bins);
	float * bg_hist = new float[bins];
	memset(bg_hist, 0, sizeof(float) * bins);

	//计算输入图片的HOG和直方图
	calcHOG(hogTemplate, ref_hist, nAngle, blockSize);
	calcHOG(Img1, pl_hist, nAngle, blockSize);
	calcHOG(Img2, bg_hist, nAngle, blockSize);

	//计算直方图距离
	float dis1 = sqrt(normL2Sqr(ref_hist,pl_hist,bins));
	float dis2 = sqrt(normL2Sqr(ref_hist, bg_hist, bins));

	std::cout << "The distance from Template to Img1 is " << dis1 << std::endl;
	std::cout << "The distance from Template to Img2 is " << dis2 << std::endl;

	(dis1 <= dis2) ? (std::cout << "img1 is similar" << std::endl) : (std::cout << "img2 is similar" << std::endl);

	//程序结束释放内存
	delete[] ref_hist;
	delete[] pl_hist;
	delete[] bg_hist;

	waitKey(0);
	return 0;
}