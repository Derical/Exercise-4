#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int structElementSize = 3;

int main()
{
	// ------------------------- Exercise 1 -------------------------

	//Mat srcMat = imread("C:Users\\STAR ZHANG\\Pictures\\5.jpg");
	//Mat grayMat,elementMat,binMat;
	//Mat erodeMat, dilateMat, openMat, closeMat;
	////转换为灰度图
	//cvtColor(srcMat, grayMat, COLOR_BGR2GRAY);
	////进行图像二值化
	//threshold(grayMat,binMat,85,255,THRESH_BINARY);
	//imshow("bin", binMat);
	//elementMat = getStructuringElement(MORPH_ELLIPSE,Size(structElementSize * 2 + 1, structElementSize * 2 + 1));
	////腐蚀
	//erode(binMat,erodeMat,elementMat);
	////膨胀
	//dilate(binMat,dilateMat,elementMat);
	////开运算
	//morphologyEx(binMat, openMat,MORPH_OPEN,elementMat);
	////闭运算
	//morphologyEx(binMat,closeMat,MORPH_CLOSE,elementMat);

	//imshow("src", srcMat);
	//imshow("erode", erodeMat);
	//imshow("dilate", dilateMat);
	//imshow("open", openMat);
	//imshow("close", closeMat);
	//imshow("gray", grayMat);

	//// ------------------------- Exercise 2 -------------------------

	Mat srcMat = imread("C:Users\\STAR ZHANG\\Pictures\\5.jpg");
	Mat grayMat,binMat;
	Mat labelsMat, statsMat, centroidsMat;
	//转换为灰度图
	cvtColor(srcMat, grayMat, COLOR_BGR2GRAY);
	//进行图像二值化
	threshold(grayMat, binMat, 85, 255, THRESH_BINARY);
	//连通域标记
	int Cnt = 0;
	Cnt = connectedComponentsWithStats(binMat,labelsMat,statsMat,centroidsMat);
	//绘制矩阵
	--Cnt;
	//获取向量长度
	int height = statsMat.rows;
	int width  = statsMat.cols;
	cout << "height is " << height << "\n" << "width is " << width << endl;

	for (int i = 1; i < Cnt + 1; ++i)
	{
		int x = statsMat.at<int>(i, CC_STAT_LEFT);
		int y = statsMat.at<int>(i, CC_STAT_TOP);
		int width = statsMat.at<int>(i, CC_STAT_WIDTH);
		int height = statsMat.at<int>(i, CC_STAT_HEIGHT);
		cv::rectangle(binMat,Rect(x,y,width,height),Scalar(255,255,255));
	}

	cout << Cnt << "\n" << statsMat << endl;
	imshow("connect", binMat);

	waitKey(0);
	return 0;
}