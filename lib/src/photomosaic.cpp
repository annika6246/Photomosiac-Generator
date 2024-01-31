#include <iostream>
#include "photomosaic.h"

void photomosaic::buildTree(std::string filePath) {
    if (squareSize == 0) {
        squareSize = round(std::max(ogImage.getX(), ogImage.getY())/100);
    }

    fs::path imageLoc(filePath);
    if (!fs::exists(imageLoc)) {
        std::cerr << "Path provided does not exist." << std::endl;
        return;
    }
    if (!fs::is_directory(imageLoc)) {
        std::cerr << "Path provided is not a directory." << std::endl;
        return;
    }

    // iterate recursively through subdirectories
    for(const auto& entry: fs::recursive_directory_iterator(imageLoc)) {
        if (entry.is_regular_file() && entry.path().filename().string() != "desktop.ini") {
            Image img(entry.path().string().c_str());
            int min = std::min(img.getX(), img.getY());
            double d = squareSize*(1.0/min);
            img.resize(d);
            img.crop();
            Pixel px = img.calcRGB();
            tree.insert(px, img);
        }
    }
}

void photomosaic::buildMosaic() {

    for (int i=0; i < ogImage.getY(); i+=squareSize) {
        for (int j=0; j < ogImage.getX(); j+=squareSize) {
            int xMin = std::min(ogImage.getX()-j, squareSize);
            int yMin = std::min(ogImage.getY()-i, squareSize);

            Pixel p(ogImage.getComps());

            // temp stores square segment from og image to get avg rgb
            Image temp = Image(xMin, yMin, ogImage.getComps());
            temp.fillPix(ogImage, true, j, i, j+xMin, i+yMin);
            p = temp.calcRGB();

            // result is the source image with closest rgb, fills photoImage with pix_arr from result
            Image result = tree.find(p);
            photoImage.fillPix(result, false, j, i, j+xMin, i+yMin);
        }
    }
}

void photomosaic::writeMosaic(std::string type) {
    photoImage.copyPaths(ogImage);
    photoImage.write_image(type);
}