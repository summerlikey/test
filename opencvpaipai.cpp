// opencvpaipai.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include<io.h>
#include<direct.h>//创建文件夹头文件
#include<opencv.hpp>
#include<opencv2\opencv.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>
#include<stdio.h>
#include <time.h>


#include <stdlib.h>
#define TIME_MAX 256
using namespace cv;
using namespace std;
string get_time()
{
	time_t now;
	time(&now);
	// 定义两个变量，存储转换结果
	struct tm tmTmp;
	char stTmp[TIME_MAX];
	// 转换为tm结构
	localtime_s(&tmTmp, &now);
	// 转换为字符串并输出
	asctime_s(stTmp, &tmTmp);
	FILE *fp = NULL;
	char fname[256] = { 0 };
	sprintf_s(fname, "%d%d%d%d%d%d_", 1900 + tmTmp.tm_year, 1 + tmTmp.tm_mon, tmTmp.tm_mday, tmTmp.tm_hour, tmTmp.tm_min, tmTmp.tm_sec);//获取本地时间
//	printf_s("%s\n", fname);
//	cout << "11215" << endl;


//	printf("Current time is: %s\n", stTmp);
	return fname;
}

int main(int argc, char* argv)
{ 
	time_t t= time(0);
	char tmp[64];
	VideoCapture  capture(0);
	Mat frame;
	if (!capture.isOpened())
	{
		cout << "摄像头打开失败！" << endl;
		return -1;
	}
	char key;
	char filename[200];
	int count = 0;
	namedWindow("【视频】", 1);
	namedWindow("【图片】", 1);
	while (1)
	{
		key = waitKey(50);
		capture >> frame;
		imshow("【视频】", frame);

		if (key == 27)
			break;//按ESC键退出程序
		if (key == 32)//按空格键进行拍照
		{
			get_time();
			sprintf_s(filename, "Picture %s%d.jpg", get_time(),++count);
			string sname = ".//photo//Picture " + get_time()+to_string(count);//直接将储存位置string到名称中，to_string()将int数据变为string数据,保存在photo文件夹，没加创建文件夹命令，需要自己创photo文件夹，与源文件同级
			sname = sname + ".jpg";
			imwrite(sname, frame);//图片保存到本工程目录中
			imshow("【图片】", frame);
		}
	}
	return 0;
}
