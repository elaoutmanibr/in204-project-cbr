

#include "display.hpp"
void CACHE::clean(int page){
    std::vector<IMAGE> nv_images;
    for(IMAGE image:images){
        if (image.get_num()<(page+3) && image.get_num()>(page-3)){
            nv_images.push_back(image);
        }
    }
    images.clear();
    images = nv_images;
}

void load_one(int page, Archive arch, IMAGE * sf_image){
        cv::Mat a_image;
        arch.loadOneImage(page,a_image);
        CV_IMAGE image = CV_IMAGE(page,a_image);
        image.cv_resize();
        sf::Image sf_img = image.to_sfml();
        *sf_image = IMAGE(page,sf_img);
}

void CACHE::load(int page, Archive arch){
    clean(page);

    IMAGE current; IMAGE next; IMAGE previous;
    load_one(page, arch, &current);
    if(page>1 && !isloaded(page-1)) load_one(page-1, arch, &previous);
    if(page<arch.getPageNumTotal() && !isloaded(page+1)) load_one(page+1, arch, &next);

    add(current); add(next); add(previous);
}

