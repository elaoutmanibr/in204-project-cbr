//
//  display.cpp
//  ComicBookReader
//
//  Created by Youssef Ben Cheikh on 20/1/2022.
//  Copyright © 2022 Youssef Ben Cheikh. All rights reserved.
//

#include "display.hpp"
#include "imageProcess.hpp"

void IMAGE::load_to(int page, Archive arch){
    cv::Mat a_image;
    arch.loadOneImage(page,a_image);
    CV_IMAGE image = CV_IMAGE(page,a_image);
    image.cv_resize();
    sf::Image sf_img = image.to_sfml();
    IMAGE img = IMAGE(page,sf_img);
}
void CACHE::clean(int page){
    std::vector<IMAGE> nv_images;
    for(IMAGE image:images){
        if (image.get_num()<(page+2) && image.get_num()>(page-2)){
            nv_images.push_back(image);
        }
    }
    images.clear();
    images = nv_images;
}

IMAGE load_one(int page, Archive arch){
        cv::Mat a_image;
        arch.loadOneImage(page,a_image);
        CV_IMAGE image = CV_IMAGE(page,a_image);
        image.cv_resize();
        sf::Image sf_img = image.to_sfml();
        IMAGE img = IMAGE(page,sf_img);
        return img;
}

void CACHE::load(int page, Archive arch){
    clean(page);
    IMAGE current; IMAGE previous; IMAGE next;
    auto future = std::async(load_one,page,arch);
    current = future.get();
    current = load_one(page, arch);
    if (page+1<arch.getPageNumTotal()){
        auto nfuture = std::async(load_one,page+1,arch);
        next = nfuture.get();
        //next = load_one(page+1, arch);
    }
    if (page-1>0){
        auto pfuture = std::async(load_one,page-1,arch);
        previous = pfuture.get();
        //previous = load_one(page-1, arch);
    }
    add(current); add(next); add(previous);
}

