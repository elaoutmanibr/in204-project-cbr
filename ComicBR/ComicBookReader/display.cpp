//
//  display.cpp
//  ComicBookReader
//
//  Created by Youssef Ben Cheikh on 20/1/2022.
//  Copyright © 2022 Youssef Ben Cheikh. All rights reserved.
//

#include "display.hpp"
#include "imageProcess.hpp"
void CACHE::clean(int page){
    std::vector<IMAGE> nv_images;
    for(IMAGE image:images){
        if (image.get_num()<(page+6) && image.get_num()>(page-3)){
            nv_images.push_back(image);
        }
    }
    images = nv_images;
}

void CACHE::load_one(int page, Archive arch){
    cv::Mat a_image;
    arch.loadOneImage(page,a_image);
    CV_IMAGE image = CV_IMAGE(page,a_image);
    image.cv_resize();
    sf::Image sf_img = image.to_sfml();
    IMAGE img = IMAGE(page,sf_img);
    add(img);
}

void CACHE::load(int page, Archive arch){
    clean(page);
    load_one(page, arch);
}
