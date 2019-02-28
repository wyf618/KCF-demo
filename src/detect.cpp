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

bool HOG = true; // 是否使用hog特征
bool FIXEDWINDOW = true;// 是否使用修正窗口
bool MULTISCALE = true;// 是否使用多尺度   //bool SILENT = false;// 是否不做显示
bool LAB = false;// 是否使用LAB颜色

void on_MouseHandle(int event, int x, int y, int flags, void* param);
void DrawRectangle( cv::Mat& img, cv::Rect box );

Rect g_rectangle;
bool g_bDrawingBox = false;//是否进行绘制
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
        //鼠标移动消息
        case EVENT_MOUSEMOVE:
        {
            if( g_bDrawingBox )//如果是否进行绘制的标识符为真，则记录下长和宽到RECT型变量中
            {
                g_rectangle.width = x-g_rectangle.x;
                g_rectangle.height = y-g_rectangle.y;
            }
        }
            break;

            //左键按下消息
        case EVENT_LBUTTONDOWN:
        {
            g_bDrawingBox = true;
            g_rectangle =Rect( x, y, 0, 0 );//记录起始点
        }
            break;

            //左键抬起消息
        case EVENT_LBUTTONUP:
        {
            g_bDrawingBox = false;//置标识符为false
            //对宽和高小于0的处理
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
            //调用函数进行绘制
            DrawRectangle( image, g_rectangle );
        }
            break;
    }
}
void DrawRectangle( cv::Mat& img, cv::Rect box )
{
    cv::rectangle(img,box.tl(),box.br(),cv::Scalar(g_rng.uniform(0, 255), g_rng.uniform(0,255), g_rng.uniform(0,255)));//随机颜色
}