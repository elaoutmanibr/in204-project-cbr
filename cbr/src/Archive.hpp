
#ifndef archive_hpp
#define archive_hpp

#include <stdio.h>
#include <string>
#include "unarr.h"
#include <vector>
#include <opencv2/opencv.hpp>


class Archive
{
// class for archiving file, unzip the image files
// Use OpenCV, format for image: "cv::Mat"
public:
    Archive();
    ~Archive();
    bool loadArchivedFiles(std::string file_path);
    bool loadOneImage(int num, cv::Mat &a_image);
    int getPageNumTotal(){
        return page_num_total;
    }
    std::vector<size_t> get_offset_cache(){
        return offset_cache;
    }
    
public:
    ar_archive * ar_open_any_archive(ar_stream *stream, const char *fileext);
    std::string archive_path;
    std::vector<unsigned char> read_buffer;
    ar_stream *stream = NULL;
    ar_archive *ar = NULL;
    int page_num_total;
    std::vector<size_t> offset_cache;
    
};

#endif /* archive_hpp */

