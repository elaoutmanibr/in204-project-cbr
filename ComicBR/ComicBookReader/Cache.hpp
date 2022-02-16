
#ifndef cache_hpp
#define cache_hpp
#include "imageProcess.hpp"
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include "unarr.h"
#include "Archive.hpp"
#include <opencv2/opencv.hpp>






class Cache {
public:
    
    Cache(){}
    Cache(Cache &cache){
        images = cache.images;
    }
    ~Cache(){
        images.clear();
    }
    bool isloaded(int num){
        for(Image image:images){
            if(image.get_num()==num){
                return true;
            }
        }
        return false;
    }
    
    void add(Image img){
        images.push_back(img);
    }
    
    
    sf::Image getpage(int num){
        for(Image image:images){
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
    std::vector<Image> images;
};

void load_one(int page, Archive arch, Image * sf_image);

#endif /* cache_hpp */
