
#include <stdexcept>
#include "Pixel.h"

// constructors
Pixel::Pixel() = default;

// constructor with numC
Pixel::Pixel(int numC) {
    if (numC < 1 || numC > 4) {
        throw std::invalid_argument("Invalid argument.");
    }
    numComponents = numC;
}

// destructor
Pixel::~Pixel() = default;

// copy constructor
Pixel::Pixel(const Pixel &arg) {
    this->numComponents = arg.numComponents;
    if (numComponents >= 1) {
        comp1 = arg.comp1;
    }
    if (numComponents >= 2) {
        comp2 = arg.comp2;
    }
    if (numComponents >= 3) {
        comp3 = arg.comp3;
    }
    if (numComponents == 4) {
        comp4 = arg.comp4;
    }
}

// get pixel element
unsigned char Pixel::getElement(int nComp) {
    if (nComp == 1) {
        return comp1;
    }
    else if (nComp == 2) {
        return comp2;
    }
    else if (nComp == 3) {
        return comp3;
    }
    else if (nComp == 4) {
        return comp4;
    }
    else {
        return 0;
    }
}

// set pixel element
void Pixel::setElement(int nComp, unsigned char val) {
    if (nComp == 1) {
        comp1 = val;
    }
    else if (nComp == 2) {
        comp2 = val;
    }
    else if (nComp == 3) {
        comp3 = val;
    }
    else if (nComp == 4) {
        comp4 = val;
    }
    else {
        throw std::invalid_argument("Invalid argument.");
    }
}