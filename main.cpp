#include <iostream>
#include "photomosaic.h"

int main(int argc, char* argv[]) {
    // initialize string variables
    std::string inputFile, dirStr, outputFile;
    int sSize {0};

    // 3 command line arguments
    if (argc==4) {
        inputFile = argv[1];
        dirStr = argv[2];
        outputFile = argv[3];
    }

    // test command
    else if (argc == 2 && std::string(argv[1]) == "-t") {
        inputFile = "sampleImages/mountains.jpg";
        dirStr = "small_imgs";
        outputFile = "sampleImages/out.jpg";
    }

    // interactive execution environment
    else {
        std::cout << "Enter your input file path: " << std::endl;
        std::cin >> inputFile;
        std::cout << "Enter your source image directory path: " << std::endl;
        std::cin >> dirStr;
        std::cout << "Enter your output file name: " << std::endl;
        std::cin >> outputFile;
        std::cout << "Enter your square size: " << std::endl;
        std::cin >> sSize;
    }

    // initialize image object
    Image img(inputFile.c_str(), outputFile.c_str());
    photomosaic photo(img);
    if (sSize != 0)
        photo.setSquareSize(sSize);
    photo.buildTree(dirStr);
    photo.buildMosaic();

    // write image to correct type
    size_t length = strlen(outputFile.c_str());
    std::string type(outputFile.c_str() + length - 3, 3);
    photo.writeMosaic(type);


    return 0;
}