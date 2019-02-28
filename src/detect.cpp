#include <iostream>
#include<stdio.h>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include "kcftracker.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
//#include"batch_cutting.h"
using namespace cv;
using namespace std;

bool HOG = true; // �Ƿ�ʹ��hog����
bool FIXEDWINDOW = true;// �Ƿ�ʹ����������
bool MULTISCALE = true;// �Ƿ�ʹ�ö�߶�   //bool SILENT = false;// �Ƿ�����ʾ
bool LAB = false;// �Ƿ�ʹ��LAB��ɫ

void on_MouseHandle(int event, int x, int y, int flags, void* param);
void DrawRectangle( cv::Mat& img, cv::Rect box );

Rect g_rectangle;
bool g_bDrawingBox = false;//�Ƿ���л���
RNG g_rng(12345);
int flag=0;
int main()
{
    VideoCapture cap(0);
    Mat src;
    KCFTracker tracker(HOG, FIXEDWINDOW, MULTISCALE, LAB);
    KCFTracker tracker2(HOG, FIXEDWINDOW, MULTISCALE, LAB);
    namedWindow("track");
    setMouseCallback("track",on_MouseHandle,(void*)&src);


    while(1)
    {
        cap>>src;

        DrawRectangle(src, g_rectangle );
        cout<<g_rectangle.area()<<endl;

        if(flag==1)
        {
            flag=0;
            Rect result1 =g_rectangle;
            tracker.init(result1, src);

            while(1)
            {
                cap>>src;
                result1 = tracker.update(src);
                DrawRectangle(src, result1);
                if (tracker.trustable < 0.30||flag==1)
                    break;
                imshow ("track",src);
                waitKey(1);
                if(flag == 2)
                {
                    Rect result2 =g_rectangle;
                    tracker.init(result2, src);
                    flag = 2;

                }
            }
        }

        imshow ("track",src);
        waitKey(1);

    }
}


void on_MouseHandle(int event, int x, int y, int flags, void* param)
{

    Mat& image = *(cv::Mat*) param;
    switch( event)
    {
        //����ƶ���Ϣ
        case EVENT_MOUSEMOVE:
        {
            if( g_bDrawingBox )//����Ƿ���л��Ƶı�ʶ��Ϊ�棬���¼�³��Ϳ�RECT�ͱ�����
            {
                g_rectangle.width = x-g_rectangle.x;
                g_rectangle.height = y-g_rectangle.y;
            }
        }
            break;

            //���������Ϣ
        case EVENT_LBUTTONDOWN:
        {
            g_bDrawingBox = true;
            g_rectangle =Rect( x, y, 0, 0 );//��¼��ʼ��
        }
            break;

            //���̧����Ϣ
        case EVENT_LBUTTONUP:
        {
            g_bDrawingBox = false;//�ñ�ʶ��Ϊfalse
            //�Կ�͸�С��0�Ĵ���
            if( g_rectangle.width < 0 )
            {
                g_rectangle.x += g_rectangle.width;
                g_rectangle.width *= -1;
            }

            if( g_rectangle.height < 0 )
            {
                g_rectangle.y += g_rectangle.height;
                g_rectangle.height *= -1;
            }
            if(EVENT_LBUTTONUP)
            {
                cout<<"left buttin were raise"<<endl;
                flag=1;
            }
            //���ú������л���
            DrawRectangle( image, g_rectangle );
        }
            break;
    }
}
void DrawRectangle( cv::Mat& img, cv::Rect box )
{
    cv::rectangle(img,box.tl(),box.br(),cv::Scalar(g_rng.uniform(0, 255), g_rng.uniform(0,255), g_rng.uniform(0,255)));//�����ɫ
}