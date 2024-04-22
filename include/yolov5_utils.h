#pragma once
#include<iostream>
#include <numeric>
#include<opencv2/opencv.hpp>
#ifdef _WIN32
    #include <io.h>
#elif __linux__
    #include <inttypes.h>
    #include <unistd.h>
    #define __int64 int64_t
    #define _close close
    #define _read read
    #define _lseek64 lseek64
    #define _O_RDONLY O_RDONLY
    #define _open open
    #define _lseeki64 lseek64
    #define _lseek lseek
    #define stricmp strcasecmp
#endif
#define ORT_OLD_VISON 13  //ort1.12.0 ֮ǰ�İ汾Ϊ�ɰ汾API

struct OutputSeg {
	int id;             //������id
	float confidence;   //������Ŷ�
	cv::Rect box;       //���ο�
	cv::Mat boxMask;       //���ο���mask����ʡ�ڴ�ռ�ͼӿ��ٶ�
};
struct MaskParams {
	//int segChannels = 32;
	//int segWidth = 160;
	//int segHeight = 160;
	int netWidth = 640;
	int netHeight = 640;
	float maskThreshold = 0.5;
	cv::Size srcImgShape;
	cv::Vec4d params;

};
bool CheckModelPath(std::string modelPath);
bool CheckParams(int netHeight, int netWidth, const int* netStride, int strideSize); 
void DrawPred(cv::Mat& img,
	std::vector<OutputSeg> result,
	std::vector<std::string> classNames,
	std::vector<cv::Scalar> color,
	bool isVideo = false
);
void LetterBox(const cv::Mat& image, cv::Mat& outImage,
	cv::Vec4d& params, //[ratio_x,ratio_y,dw,dh]
	const cv::Size& newShape = cv::Size(640, 640),
	bool autoShape = false,
	bool scaleFill = false,
	bool scaleUp = true,
	int stride = 32,
	const cv::Scalar& color = cv::Scalar(114, 114, 114));
void GetMask(const cv::Mat& maskProposals, const cv::Mat& maskProtos, std::vector<OutputSeg>& OutputSeg, const MaskParams& maskParams);
void GetMask2(const cv::Mat& maskProposals, const cv::Mat& maskProtos, OutputSeg& output, const MaskParams& maskParams);



