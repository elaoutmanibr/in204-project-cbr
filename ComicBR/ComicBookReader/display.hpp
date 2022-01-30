//
//  display.hpp
//  ComicBookReader
//
//  Created by Youssef Ben Cheikh on 20/1/2022.
//  Copyright © 2022 Youssef Ben Cheikh. All rights reserved.
//

#ifndef display_hpp
#define display_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include "unarr.h"

#include <opencv2/opencv.hpp>

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
    IMAGE(CV_IMAGE img){
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

class CACHE {
public:
    CACHE(int size){
        max_size = size;
        std::vector<sf::Image> images;
    }
    
    bool isloaded(int num){
        for(IMAGE image:images){
            if(image.get_num()==num){
                return true;
            }
        }
        return false;
    }
    
    void add(IMAGE img){
        images.push_back(img);
    }
    
    
    sf::Image getpage(int num){
        for(IMAGE image:images){
            if(image.get_num()==num){
                return image.get_img();
            }
        }
        sf::Image mg;
        mg.create(20, 20, sf::Color::Black);
        return mg  ;
    }
    
private:
    int max_size;
    std::vector<IMAGE> images;
};

#endif /* display_hpp */
