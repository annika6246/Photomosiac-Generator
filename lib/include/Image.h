
#ifndef PHOTOMOSAIC_IMAGE_H
#define PHOTOMOSAIC_IMAGE_H

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION

#include "Pixel.h"
#include <string>
#include <string.h>

class Image {
private:
    char const* inPath;
    char const* outPath;
    int x;                  // width
    int y;                  //height
    int comps;              // number of components
    int size {0};
    unsigned char *data = nullptr;
    Pixel **pix_arr = nullptr;
public:

    // constructor
    explicit Image(char const* inP);
    Image(char const* inP, char const* outP);

    // constructor for new empty image
    Image(int x, int y, int comps);

    // destructor
    ~Image();

    // copy constructor
    Image(const Image&);

    // copy assignment operator
    Image& operator=(const Image&);

    // reading images to 2d array
    bool read_image(int force_comps = 0);

    // writing images to 1d array
    bool write_image(std::string type);

    // get width
    int getX() {return x;}

    // get height
    int getY() {return y;}

    // get comps
    int getComps() {return comps;}

    // 1. flipping images on the vertical axis
    Image& flipV();

    // 2. flipping images on the horizontal axis
    Image& flipH();

    // rotate 90 degrees right
    Image& rotate90();

    // rotate 90 degrees left (270 degrees right)
    Image& rotate270();

    Image& add_border();

    void fill_circle(int row, int col, int radius, Pixel color);

    Image& pointalize();

    Image& resize(double scale);

    Image& crop();

    Pixel calcRGB();

    Image& fillPix(Image& img, bool startZero, int startX, int startY, int endX, int endY);

    Image& copyPaths(Image& img);
};


#endif //PHOTOMOSAIC_IMAGE_H
