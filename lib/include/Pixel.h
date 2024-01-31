
#ifndef PHOTOMOSAIC_PIXEL_H
#define PHOTOMOSAIC_PIXEL_H


class Pixel {
private:
    unsigned char comp1 {0};
    unsigned char comp2 {0};
    unsigned char comp3 {0};
    unsigned char comp4 {0};
    int numComponents {0};
public:

    // constructors
    Pixel();

    Pixel(int numC);

    // use default destructor
    ~Pixel();

    // copy constructor
    Pixel(const Pixel&);

    // getter
    unsigned char getElement(int nComp);

    // setter
    void setElement(int nComp, unsigned char val);

};


#endif //PHOTOMOSAIC_PIXEL_H
