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
//bool tracking=false;//跟踪标志位
//bool select_show=false;
//Point origin;
//Mat image,hsv;
//int after_select_frames=0;//选择矩形区域完后的帧计数
///************************************************************************************************************************/
///****                            如果采用这个onMouse()函数的话，则可以画出鼠标拖动矩形框的4种情形                        ****/
///************************************************************************************************************************/
//void onMouse(int event,int x,int y,int,void*)
//{
//    //Point origin;//不能在这个地方进行定义，因为这是基于消息响应的函数，执行完后origin就释放了，所以达不到效果。
//    if(select_flag)
//    {
//        select.x=MIN(origin.x,x);//不一定要等鼠标弹起才计算矩形框，而应该在鼠标按下开始到弹起这段时间实时计算所选矩形框
//        select.y=MIN(origin.y,y);
//        select.width=abs(x-origin.x);//算矩形宽度和高度
//        select.height=abs(y-origin.y);
//        select&=Rect(0,0,image.cols,image.rows);//保证所选矩形框在视频显示区域之内
//
//        //rectangle(image,select,Scalar(0,0,255),3,8,0);//显示手动选择的矩形框
//    }
//    if(event==CV_EVENT_LBUTTONDOWN)
//    {
//        select_flag=true;//鼠标按下的标志赋真值
//        tracking=false;
//        select_show=true;
//        after_select_frames=0;//还没开始选择，或者重新开始选择，计数为0
//        origin=Point(x,y);//保存下来单击是捕捉到的点
//        select=Rect(x,y,0,0);//这里一定要初始化，因为在opencv中Rect矩形框类内的点是包含左上角那个点的，但是不含右下角那个点。
//    }
//    else if(event==CV_EVENT_LBUTTONUP)
//    {
//        select_flag=false;
//        tracking=true;
//        select_show=false;
//        after_select_frames=1;//选择完后的那一帧当做第1帧
//    }
//}
/////////////////////////////////
//
//int main(int argc, char* argv[]){
//
//	bool HOG = true; // 是否使用hog特征
//	bool FIXEDWINDOW = true;// 是否使用修正窗口
//	bool MULTISCALE = true;// 是否使用多尺度  
//	//bool SILENT = false;// 是否不做显示 
//	bool LAB = false;// 是否使用LAB颜色
//
//	//////////////////////////////
//	VideoCapture cam(0);
//    if (!cam.isOpened())
//        return -1;
//
//    /****读取一帧图像****/
//    cam>>image;
//    if(image.empty())
//        return -1;
//	/****建立窗口****/
//    namedWindow("camera",1);//显示视频原图像的窗口
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
//		/****读取一帧图像****/
//        cam>>image;
//        if(image.empty())
//            return -1;
//		if(after_select_frames==1)
//		{
//			tracker.init( Rect(select.x, select.y, select.width, select.height), image );
//			after_select_frames=2;
//			printf("目标跟踪中......\n\n");
//		}
//		if(after_select_frames==2)
//		{
//			result = tracker.update(image);
//			rectangle( image, Point( result.x, result.y ), Point( result.x+result.width, result.y+result.height), Scalar( 0, 0, 200 ), 2, 8 );
//			//printf("%f\n",tracker.trustable);
//			if(tracker.trustable<0.25)
//			{
//				after_select_frames=0;
//				printf("目标丢失，请重新选择目标！\n\n");
//			}
//		}
//		if(select_show)
//            rectangle(image,select,Scalar(0,0,255),3,8,0);//显示手动选择的矩形框
//		imshow("camera",image);
//		waitKey(2);
//	}
//}
