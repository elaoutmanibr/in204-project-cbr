

#ifndef imageprocess_hpp
#define imageprocess_hpp

#include "unarr.h"
#include "Archive.hpp"
#include <opencv2/opencv.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class Cv_image {
public:
    Cv_image(int n, cv::Mat img){
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
    void cv_resize();
private:
    int num;
    cv::Mat image;
};

class Image {
public:
    Image(){};
    Image(int n, sf::Image img){
        num = n;
        image = img;
    }
    Image(Cv_image img){
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


#endif
