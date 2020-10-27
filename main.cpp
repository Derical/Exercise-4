#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int structElementSize = 2;

int main()
{
	// ------------------------- Exercise 1 -------------------------

	//Mat srcMat = imread("C:Users\\STAR ZHANG\\Pictures\\5.jpg");
	//Mat grayMat,elementMat,binMat;
	//Mat erodeMat, dilateMat, openMat, closeMat;
	////ת��Ϊ�Ҷ�ͼ
	//cvtColor(srcMat, grayMat, COLOR_BGR2GRAY);
	////����ͼ���ֵ��
	//threshold(grayMat,binMat,85,255,THRESH_BINARY);
	//imshow("bin", binMat);
	//elementMat = getStructuringElement(MORPH_ELLIPSE,Size(structElementSize * 2 + 1, structElementSize * 2 + 1));
	////��ʴ
	//erode(binMat,erodeMat,elementMat);
	////����
	//dilate(binMat,dilateMat,elementMat);
	////������
	//morphologyEx(binMat, openMat,MORPH_OPEN,elementMat);
	////������
	//morphologyEx(binMat,closeMat,MORPH_CLOSE,elementMat);

	//imshow("src", srcMat);
	//imshow("erode", erodeMat);
	//imshow("dilate", dilateMat);
	//imshow("open", openMat);
	//imshow("close", closeMat);
	//imshow("gray", grayMat);

	//// ------------------------- Exercise 2 -------------------------

	//Mat srcMat = imread("C:Users\\STAR ZHANG\\Pictures\\5.jpg");
	//Mat grayMat,binMat;
	//Mat labelsMat, statsMat, centroidsMat;
	////ת��Ϊ�Ҷ�ͼ
	//cvtColor(srcMat, grayMat, COLOR_BGR2GRAY);
	////����ͼ���ֵ��
	//threshold(grayMat, binMat, 85, 255, THRESH_BINARY);
	////��ͨ����
	//int Cnt = 0;
	//Cnt = connectedComponentsWithStats(binMat,labelsMat,statsMat,centroidsMat);
	////���ƾ���
	//--Cnt;
	////��ȡ��������
	//int height = statsMat.rows;
	//int width  = statsMat.cols;
	//cout << "height is " << height << "\n" << "width is " << width << endl;

	//for (int i = 1; i < Cnt + 1; ++i)
	//{
	//	int x = statsMat.at<int>(i, CC_STAT_LEFT);
	//	int y = statsMat.at<int>(i, CC_STAT_TOP);
	//	int width = statsMat.at<int>(i, CC_STAT_WIDTH);
	//	int height = statsMat.at<int>(i, CC_STAT_HEIGHT);
	//	cv::rectangle(binMat,Rect(x,y,width,height),Scalar(255,255,255));
	//}

	//cout << Cnt << "\n" << statsMat << endl;
	//imshow("connect", binMat);

	// ------------------------- Exercise 3 -------------------------

	Mat srcMat = imread("C:\\Users\\STAR ZHANG\\Pictures\\6.jpg");
	Mat dstMat, binMat, elementMat,grayMat;
	//ת��Ϊ�Ҷ�ͼ
	cvtColor(srcMat, grayMat, COLOR_BGR2GRAY);
	//��ֵ��
	threshold(grayMat, binMat, 0, 255, THRESH_BINARY|THRESH_OTSU);
	//��ɫ
	binMat = 255 - binMat;
	imshow("[��ֵ�����ͼ��]", binMat);
	//��ȡ�����
	elementMat = getStructuringElement(MORPH_RECT,Size(structElementSize * 2 + 1, structElementSize * 2 + 1));
	//��ʴ
	//�������
	morphologyEx(binMat,dstMat,MORPH_ERODE,elementMat,Point(-1,-1),5);
	imshow("[��ʴ���ͼ��]",dstMat);

	Mat statsMat, labelsMat, centroidsMat;
	//��ͨ����
	int Cnt = 0;
	Cnt = connectedComponentsWithStats(dstMat, labelsMat, statsMat, centroidsMat);
	cout << "����" << Cnt - 1 << "������" << endl;
	waitKey(0);
	return 0;
}