#include "GradientFilter.h"

double evaluate(cv::Mat img1, cv::Mat img2);

int main(void)
{
	cv::String path1 = "../input/synth_21.jpg";
	cv::String path2 = "../input/synth_21_r.jpg";
	cv::Mat img1 = cv::imread(path1);
	cv::Mat img2 = cv::imread(path2);
	cv::imshow("img1", img1);
	cv::imshow("img2", img2);
	double MAE = evaluate(img1, img2);

	std::cout<<"path1 : "<<path1<<"\npath2 : "<<path2<<"\nMAE : "<<MAE<<std::endl;

	cv::waitKey();
	return 0;
}

double evaluate(cv::Mat img1, cv::Mat img2)
{
	cv::Mat img1_sh, img2_sh;
	GradientFilter gf1, gf2;
	
	gf1.init(img1);
	gf1.optimize().convertTo(img1_sh,  CV_8UC1, 255);
	gf2.init(img2);
	gf2.optimize().convertTo(img2_sh,  CV_8UC1, 255);

	cv::imshow("img1_sh", img1_sh);
	cv::imshow("img2_sh", img2_sh);


	cv::Mat absDiff;
	cv::absdiff(img1_sh, img2_sh, absDiff);

	return cv::mean(absDiff).val[0];
}