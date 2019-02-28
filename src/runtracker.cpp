//#include "stdafx.h"
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <algorithm>
//
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//
//#include "kcftracker.hpp"
//using namespace std;
//using namespace cv;
//
////////////////////////////////
//Rect select;
//bool select_flag=false;
//bool tracking=false;//���ٱ�־λ
//bool select_show=false;
//Point origin;
//Mat image,hsv;
//int after_select_frames=0;//ѡ�������������֡����
///************************************************************************************************************************/
///****                            ����������onMouse()�����Ļ�������Ի�������϶����ο��4������                        ****/
///************************************************************************************************************************/
//void onMouse(int event,int x,int y,int,void*)
//{
//    //Point origin;//����������ط����ж��壬��Ϊ���ǻ�����Ϣ��Ӧ�ĺ�����ִ�����origin���ͷ��ˣ����Դﲻ��Ч����
//    if(select_flag)
//    {
//        select.x=MIN(origin.x,x);//��һ��Ҫ����굯��ż�����ο򣬶�Ӧ������갴�¿�ʼ���������ʱ��ʵʱ������ѡ���ο�
//        select.y=MIN(origin.y,y);
//        select.width=abs(x-origin.x);//����ο�Ⱥ͸߶�
//        select.height=abs(y-origin.y);
//        select&=Rect(0,0,image.cols,image.rows);//��֤��ѡ���ο�����Ƶ��ʾ����֮��
//
//        //rectangle(image,select,Scalar(0,0,255),3,8,0);//��ʾ�ֶ�ѡ��ľ��ο�
//    }
//    if(event==CV_EVENT_LBUTTONDOWN)
//    {
//        select_flag=true;//��갴�µı�־����ֵ
//        tracking=false;
//        select_show=true;
//        after_select_frames=0;//��û��ʼѡ�񣬻������¿�ʼѡ�񣬼���Ϊ0
//        origin=Point(x,y);//�������������ǲ�׽���ĵ�
//        select=Rect(x,y,0,0);//����һ��Ҫ��ʼ������Ϊ��opencv��Rect���ο����ڵĵ��ǰ������Ͻ��Ǹ���ģ����ǲ������½��Ǹ��㡣
//    }
//    else if(event==CV_EVENT_LBUTTONUP)
//    {
//        select_flag=false;
//        tracking=true;
//        select_show=false;
//        after_select_frames=1;//ѡ��������һ֡������1֡
//    }
//}
/////////////////////////////////
//
//int main(int argc, char* argv[]){
//
//	bool HOG = true; // �Ƿ�ʹ��hog����
//	bool FIXEDWINDOW = true;// �Ƿ�ʹ����������
//	bool MULTISCALE = true;// �Ƿ�ʹ�ö�߶�  
//	//bool SILENT = false;// �Ƿ�����ʾ 
//	bool LAB = false;// �Ƿ�ʹ��LAB��ɫ
//
//	//////////////////////////////
//	VideoCapture cam(0);
//    if (!cam.isOpened())
//        return -1;
//
//    /****��ȡһ֡ͼ��****/
//    cam>>image;
//    if(image.empty())
//        return -1;
//	/****��������****/
//    namedWindow("camera",1);//��ʾ��Ƶԭͼ��Ĵ���
//	setMouseCallback("camera",onMouse,0);
//	///////////////////////////////////
//
//	// Create KCFTracker object
//	KCFTracker tracker(HOG, FIXEDWINDOW, MULTISCALE, LAB);
//
//	Rect result;
//
//	while(1)
//	{
//		/****��ȡһ֡ͼ��****/
//        cam>>image;
//        if(image.empty())
//            return -1;
//		if(after_select_frames==1)
//		{
//			tracker.init( Rect(select.x, select.y, select.width, select.height), image );
//			after_select_frames=2;
//			printf("Ŀ�������......\n\n");
//		}
//		if(after_select_frames==2)
//		{
//			result = tracker.update(image);
//			rectangle( image, Point( result.x, result.y ), Point( result.x+result.width, result.y+result.height), Scalar( 0, 0, 200 ), 2, 8 );
//			//printf("%f\n",tracker.trustable);
//			if(tracker.trustable<0.25)
//			{
//				after_select_frames=0;
//				printf("Ŀ�궪ʧ��������ѡ��Ŀ�꣡\n\n");
//			}
//		}
//		if(select_show)
//            rectangle(image,select,Scalar(0,0,255),3,8,0);//��ʾ�ֶ�ѡ��ľ��ο�
//		imshow("camera",image);
//		waitKey(2);
//	}
//}
