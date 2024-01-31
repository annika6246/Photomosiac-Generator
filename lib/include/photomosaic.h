
#ifndef PHOTOMOSAIC_PHOTOMOSAIC_H
#define PHOTOMOSAIC_PHOTOMOSAIC_H
#include <string>
#include <filesystem>
#include "Image.h"
#include "kdTree.h"

namespace fs = std::filesystem;

class photomosaic {
private:
    Image ogImage;
    Image photoImage;
    KDtree<Image> tree;
    int squareSize {0};
public:
    explicit photomosaic(Image input) : ogImage(input), photoImage(Image(input.getX(), input.getY(), input.getComps())), tree(KDtree<Image>())  {}
    void buildTree(std::string filePath);
    void buildMosaic();
    void writeMosaic(std::string type);
    void setSquareSize(int size) {
        squareSize = size;
    }
};


#endif //PHOTOMOSAIC_PHOTOMOSAIC_H
