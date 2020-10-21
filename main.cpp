#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int structElementSize = 3;

int main()
{
	// ------------------------- Exercise 1 -------------------------

	Mat srcMat = imread("C:Users\\STAR ZHANG\\Pictures\\5.jpg");
	Mat grayMat,elementMat,binMat;
	Mat erodeMat, dilateMat, openMat, closeMat;
	//ת��Ϊ�Ҷ�ͼ
	cvtColor(srcMat, grayMat, COLOR_BGR2GRAY);
	//����ͼ���ֵ��
	threshold(grayMat,binMat,85,255,THRESH_BINARY);
	imshow("bin", binMat);
	elementMat = getStructuringElement(MORPH_ELLIPSE,Size(structElementSize * 2 + 1, structElementSize * 2 + 1));
	//��ʴ
	erode(binMat,erodeMat,elementMat);
	//����
	dilate(binMat,dilateMat,elementMat);
	//������
	morphologyEx(binMat, openMat,MORPH_OPEN,elementMat);
	//������
	morphologyEx(binMat,closeMat,MORPH_CLOSE,elementMat);

	imshow("src", srcMat);
	imshow("erode", erodeMat);
	imshow("dilate", dilateMat);
	imshow("open", openMat);
	imshow("close", closeMat);
	imshow("gray", grayMat);

	//// ------------------------- Exercise 2 -------------------------
	//Mat srcMat = imread("C:Users\\STAR ZHANG\\Pictures\\5.jpg");
	//Mat grayMat,binMat;
	////ת��Ϊ�Ҷ�ͼ
	//cvtColor(srcMat, grayMat, COLOR_BGR2GRAY);
	////����ͼ���ֵ��
	//threshold(grayMat, binMat, 85, 255, THRESH_BINARY);

	waitKey(0);
	return 0;
}