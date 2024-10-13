# Photomosiac-Generator

### Summary
This program creates a photomosiac of a single input image by compiling images from a source library and exports it as a desired format. It uses a 3-dimensional k-d tree to store the source images, with Pixel objects containing their average RGB values as keys and Image objects containing their paths and pixel arrays as values. 

### Kd-tree structure
When inserting images into the tree, the program cycles through using one of the color values every level to sort image data, so a certain color value will be used every 3 levels to align nodes. When creating the photomosiac, for each pixel in the input image, the program searches the binary tree by similarly iterating through color values at each level, comparing the input pixel to the pixel object at the current node based on that color value, then recursively searching the appropriate subtree.

### Usage
The program takes three command line arguments, the first being the input path of the image file, the second being the path for the source image library, and the third being the output path of the output file.
