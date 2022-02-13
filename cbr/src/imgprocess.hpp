//
//  imgprocess.hpp
//  ComicBookReader
//
//  Created by Youssef Ben Cheikh on 28/1/2022.
//  Copyright © 2022 Youssef Ben Cheikh. All rights reserved.
//

#ifndef imgprocess_hpp
#define imgprocess_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "unarr.h"

class ImageCV {
public:
    ImageCV(int n, cv::Mat img){
        num = n;
        image = img;
    }
    int get_num(){
        return num;
    }
    cv::Mat get_img(){
        return image;
    }
    
    
    sf::Image to_sfml();
    bool autoAdjustImage(cv::Mat& input_image, cv::Mat& output_image, int image_type_flag);
    bool autoAdjustImageText(cv::Mat& input_image, cv::Mat& output_image);
    bool autoAdjustImageGraphic(cv::Mat& input_image, cv::Mat& output_image);
    
private:
    int num;
    cv::Mat image;
};


class IMAGE {
public:
    IMAGE(int n, sf::Image img){
        num = n;
        image = img;
    }
    IMAGE(ImageCV img){
        num = img.get_num();
        image = img.to_sfml();
    }
    int get_num(){
        return num;
    }
    sf::Image get_img(){
        return image;
    }
private:
    int num;
    sf::Image image;
};


#endif /* imgprocess_hpp */
