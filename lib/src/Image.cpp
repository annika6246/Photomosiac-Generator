
#include <iostream>
#include "Image.h"
#include "../stb/stb_image.h"
#include "../stb/stb_image_write.h"
#include "../stb/stb_image_resize2.h"


// constructor from file paths
Image::Image(char const* inP, char const* outP) {
    inPath = inP;
    outPath = outP;
    bool read = read_image();
    if (!read) {
        std::cout << "Error reading image." << std::endl;
    }
}

// constructor with input path
Image::Image(char const* inP) {
    inPath = inP;
    bool read = read_image();
    if (!read) {
        std::cout << "Error reading image." << std::endl;
    }
}

// constructor from size
Image::Image(int x, int y, int comps) : x(x), y(y), comps(comps) {
    size = x*y*comps;
    data = new unsigned char [size];
    pix_arr = new Pixel* [x*y];
    for (int i=0; i < y; i++) {
        pix_arr[i] = new Pixel[x];
    }
}

// destructor
Image::~Image() {
    stbi_image_free(data);
    data = nullptr;

    for (int i=0; i < y; i++) {
        delete[] pix_arr[i];
    }
    delete[] pix_arr;
    pix_arr = nullptr;
}

// copy constructor, uses constructor 2 to initialize blank image then copies data/pixels and file names
Image::Image(const Image &arg) : Image(arg.x, arg.y, arg.comps) {
    this->inPath = arg.inPath;
    this->outPath = arg.outPath;

    for (int i=0; i < arg.size; i++) {
        data[i] = arg.data[i];
    }

    for (int i=0; i < arg.y; i++) {
        for (int j=0; j < arg.x; j++) {
            this->pix_arr[i][j] = arg.pix_arr[i][j];
        }
    }
}

// overload copy assignment operator
Image& Image::operator=(const Image& arg) {
    if (this != &arg) {
        delete[] this->data;
        for (int i=0; i < y; i++) {
            delete[] this->pix_arr[i];
        }
        delete[] this->pix_arr;

        this->inPath = arg.inPath;
        this->outPath = arg.outPath;
        this->y = arg.y;
        this->x = arg.x;
        this->comps = arg.comps;

        for (int i=0; i < arg.size; i++) {
            this->data[i] = arg.data[i];
        }

        for (int i=0; i < arg.y; i++) {
            for (int j=0; j < arg.x; j++) {
                this->pix_arr[i][j] = arg.pix_arr[i][j];
            }
        }
    }
    return *this;
}


// reads image, returns true if read image correctly
bool Image::read_image(int force_comps) {
    data = stbi_load(inPath, &x, &y, &comps, force_comps);
    size = x*y*comps;
    pix_arr = new Pixel*[y];

    for (int i=0; i < y; i++)
        pix_arr[i] = new Pixel[x];

    // read char values from data into pixel objects in 2d array
    int dataIndex = 0;
    for (int i=0; i < y; i++) {
        for (int j=0; j < x; j++) {
            pix_arr[i][j] = Pixel(comps);
            for (int k=0; k < comps; k++) {
                pix_arr[i][j].setElement(k+1, data[dataIndex]);
                dataIndex++;
            }

        }
    }
    return (data != nullptr);
}

// writes image, returns true if image written successfully
bool Image::write_image(std::string type) {
    int dataIndex = 0;
    int result {0};
    for (int i=0; i < y; i++) {
        for (int j=0; j < x; j++) {
            for (int k=0; k < comps; k++) {
                data[dataIndex] = pix_arr[i][j].getElement(k+1);
                dataIndex++;
            }

        }
    }
    if (type == "jpg") {
        result = stbi_write_jpg(outPath, x, y, comps, data, 100);
    }
    if (type == "png") {
        result = stbi_write_png(outPath, x, y, comps, data, x*comps);
    }
    if (type == "bmp") {
        result = stbi_write_bmp(outPath, x, y, comps, data);
    }
    return (result != 0);
}

// flip image on vertical axis
Image& Image::flipV() {
    for (int i=0; i < y; i++) {
        for (int j=0; j < x/2; j++) {
            Pixel px1 = pix_arr[i][j];
            Pixel px2 = pix_arr[i][x-j-1];
            pix_arr[i][x-j-1] = px1;
            pix_arr[i][j] = px2;
        }
    }
    return *this;
}

// flip image on horizontal axis
Image& Image::flipH() {
    for (int i=0; i < y/2; i++) { // for half rows
        for (int j=0; j < x; j++) { // for every column
            Pixel px1 = pix_arr[i][j];
            Pixel px2 = pix_arr[y-i-1][j];
            pix_arr[y-i-1][j] = px1;
            pix_arr[i][j] = px2;
        }
    }
    return *this;
}

// rotate image 90 degrees
Image& Image::rotate90() {
    Image* temp = new Image(y, x, comps);

    for (int i=0; i < x; i++) {
        for (int j=0; j < y; j++) {
            Pixel px = pix_arr[j][i]; // pixel in row j and col i
            temp->pix_arr[i][y-j-1] = px;
        }
    }

    std::swap(x, temp->x);
    std::swap(y, temp->y);
    std::swap(pix_arr, temp->pix_arr);

    delete temp;

    return *this;
}

// rotate image 270 degrees
Image& Image::rotate270() {
    Image* temp = new Image(y, x, comps);

    for (int i=0; i < x; i++) {
        for (int j=0; j < y; j++) {
            Pixel px = pix_arr[j][i]; // pixel in row j and col i
            temp->pix_arr[x-i-1][j] = px;
        }
    }

    // swap widths, heights, and pixel arrays so temporary image can be deleted
    std::swap(x, temp->x);
    std::swap(y, temp->y);
    std::swap(pix_arr, temp->pix_arr);

    delete temp;

    return *this;

}

// adds border to image
Image& Image::add_border() {
    int r, g, b;
    int border_size;

    std::cout << "Enter rgb values (space delimited): ";
    std::cin >> r >> g >> b;
    std::cout << "Enter border size: " << std::endl;
    std::cin >> border_size;


    Pixel px(3);
    px.setElement(1, (unsigned char)r);
    px.setElement(2, (unsigned char)g);
    px.setElement(3, (unsigned char)b);

    Image* temp = new Image(x+(2*border_size), y+(2*border_size), comps);
    for (int i=0; i < temp->x; i++) {       // for every column
        for (int j=0; j < temp->y; j++) {       // for every row
            if (i < border_size || i > temp->x - border_size - 1 || j < border_size || j > temp->y - border_size - 1) {
                temp->pix_arr[j][i] = px;
            }
            else {
                temp->pix_arr[j][i] = pix_arr[j-border_size][i-border_size];
            }
        }
    }

    // swap sizes, data, and pixel arrays so temp can be deleted
    std::swap(x, temp->x);
    std::swap(y, temp->y);
    std::swap(pix_arr, temp->pix_arr);
    std::swap(data, temp->data);
    std::swap(size, temp->size);

    delete temp;
    return *this;
}

// function to fill color of pixels surrounding a certain pixel if within circular distance
void Image::fill_circle(int row, int col, int radius, Pixel value) {
    // define boundaries of surrounding square
    int start_row = std::max(row-radius, 0);
    int end_row = std::min(row+radius, row-1);

    int start_col = std::max(col-radius, 0);
    int end_col = std::min(col+radius, col-1);

    // iterate through values in surrounding square
    for (int i=start_row; i<end_row+1; i++) {
        for (int j=start_col; j<end_col+1; j++) {
            int xval = i - row;
            int yval = j - col;

            // use formula of a circle to check if point is within bounds
            if(xval*xval + yval*yval <= radius*radius) {
                pix_arr[i][j] = value;
            }
        }
    }
}

// pointalize an image
Image& Image::pointalize() {
    srand((unsigned) time(NULL));
    for (int i=0; i < y; i++) { // for every row
        for (int j=0; j < x; j++) { // for every column
            int radius = 5 + rand() % 10;
            // skip pixels 98% of the time
            int skip = rand() % 50;
            if (radius > 0 && skip > 48) {
                Pixel og_px = pix_arr[i][j];
                fill_circle(i, j, radius, og_px);
            }
        }
    }
    return *this;
}

// resize an image
Image& Image::resize(double scale) {
    int newX = round(x*scale);
    int newY = round(y*scale);
    Image* temp = new Image(newX, newY, comps);
    stbir_resize_uint8_linear(data, x, y, 0, temp->data, newX, newY, 0, static_cast<stbir_pixel_layout>(comps));

    int dataIndex = 0;
    for (int i=0; i < temp->y; i++) {
        for (int j=0; j < temp->x; j++) {
            temp->pix_arr[i][j] = Pixel(comps);
            for (int k=0; k < comps; k++) {
                temp->pix_arr[i][j].setElement(k+1, temp->data[dataIndex]);
                dataIndex++;
            }
        }
    }

    std::swap(x, temp->x);
    std::swap(y, temp->y);
    std::swap(pix_arr, temp->pix_arr);
    std::swap(data, temp->data);
    std::swap(size, temp->size);

    delete temp;
    return *this;
}

// crop image to min of height/width
Image& Image::crop() {
    int z = std::min(x, y);
    Image* temp = new Image(z, z, comps);
    int startI = round((x-z)/2);
    int startJ = round((y-z)/2);
    for (int i=startI; i < round((x+z)/2); i++) {
        for (int j=startJ; j < round((y+z)/2); j++) {
            temp->pix_arr[j-startJ][i-startI] = pix_arr[j][i];
        }
    }
    std::swap(x, temp->x);
    std::swap(y, temp->y);
    std::swap(pix_arr, temp->pix_arr);
    std::swap(data, temp->data);
    std::swap(size, temp->size);

    delete temp;
    return *this;
}

// calculate average RBG values of an image
Pixel Image::calcRGB() {
    unsigned long r = 0, g = 0, b = 0;
    for (int i=0; i < y; i++) { // for every row
        for (int j = 0; j < x; j++) { // for every column
            r += pix_arr[i][j].getElement(1);
            g += pix_arr[i][j].getElement(2);
            b += pix_arr[i][j].getElement(3);
        }
    }
    Pixel avgRGB(3);
    avgRGB.setElement(1, (unsigned char)(r/(x*y)));
    avgRGB.setElement(2, (unsigned char)(g/(x*y)));
    avgRGB.setElement(3, (unsigned char)(b/(x*y)));
    return avgRGB;
}

// replace pixel array with that from another image
Image& Image::fillPix(Image& img, bool startZero, int startX, int startY, int endX, int endY) {
    for (int i=startY; i < endY; i++) {
        for (int j=startX; j < endX; j++) {
            if (startZero)
                this->pix_arr[i-startY][j-startX] = img.pix_arr[i][j];
            else
                this->pix_arr[i][j] = img.pix_arr[i-startY][j-startX];
        }
    }
    return *this;
}

// copy image input and output file paths
Image& Image::copyPaths(Image &img) {
    this->inPath = img.inPath;
    this->outPath = img.outPath;
    return *this;
}