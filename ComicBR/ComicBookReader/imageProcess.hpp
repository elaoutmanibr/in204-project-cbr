#include <opencv2/opencv.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "unarr.h"

#ifndef imageprocess_hpp
#define imageprocess_hpp


class CV_IMAGE {
public:
    CV_IMAGE(int n, cv::Mat img){
        num = n;
        image = img;
    }
    int get_num(){
        return num;
    }
    cv::Mat get_img(){
        return image;
    }
    sf::Image to_sfml(){
        sf::Image img;
        cv::Mat frameRGBA;
        cv::cvtColor(image, frameRGBA, cv::COLOR_BGR2RGBA);
        img.create(frameRGBA.cols, frameRGBA.rows, frameRGBA.ptr());
        return img;
    }
    void cv_resize(){
        cv::Mat resized;
        //std::cout<<num<<"empty"<<image.empty()<<"\n";
        cv::resize(image, resized, cv::Size(), 0.9, 0.9, cv::INTER_LINEAR);
        image = resized;
    }
private:
    int num;
    cv::Mat image;
};


#endif
