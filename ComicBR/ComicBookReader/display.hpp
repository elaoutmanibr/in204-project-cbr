
#ifndef display_hpp
#define display_hpp
#include "imageProcess.hpp"
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include "unarr.h"
#include "archivereader.hpp"
#include <opencv2/opencv.hpp>
#include <future>



class IMAGE {
public:
    IMAGE(){};
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
    void load_to(int page, Archive arch);
private:
    int num;
    sf::Image image;
};

class CACHE {
public:
    
    CACHE(){}
    CACHE(CACHE &cache){
        images = cache.images;
    }
    ~CACHE(){
        images.clear();
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
    void load(int page, Archive arch);
    void clean(int page);
    
private:
    std::vector<IMAGE> images;
};

void load_one(int page, Archive arch, IMAGE * sf_image);

#endif /* display_hpp */
