
#ifndef PHOTOMOSAIC_KDTREE_H
#define PHOTOMOSAIC_KDTREE_H

#include "Image.h"
#include <iostream>
#include <cmath>
#include <cfloat>

template <typename V>
class KDtree {
private:
    // node structure
    struct KDnode {
        Pixel key;
        V val;
        int height{0};
        KDnode *left{nullptr};
        KDnode *right{nullptr};

        KDnode(Pixel px, V value, int h) : key(px), val(value), height(h), left(nullptr), right(nullptr) {}
    };

    // initialize root
    KDnode *root{nullptr};

    // insert helper function
    void insertHelper(KDnode*& node, Pixel& px, V& newVal, int level) {
        if (px.getElement((level % 3) + 1) < node->key.getElement((level % 3) + 1)) {
            if (node->left == nullptr) {
                node->left = new KDnode(px, newVal, 0);
                updateH(node);
            } else {
                insertHelper(node->left, px, newVal, level + 1);
                updateH(node);
            }
        } else {
            if (node->right == nullptr) {
                node->right = new KDnode(px, newVal, 0);
                updateH(node);
            } else {
                insertHelper(node->right, px, newVal, level + 1);
                updateH(node);
            }
        }
    }

    // find helper function
    void findHelper(KDnode*& node, Pixel& px, int level, double &minDist, KDnode *&closest) {
        if (node == nullptr || level > getH()) {
            return;
        }

        double distance = sqrt(std::pow(static_cast<double>(px.getElement(1) - node->key.getElement(1)), 2) +
                               std::pow(static_cast<double>(px.getElement(2) - node->key.getElement(2)), 2) +
                               std::pow(static_cast<double>(px.getElement(3) - node->key.getElement(3)), 2));

        if (distance < minDist) {
            minDist = distance;
            closest = node;
        }

        if (px.getElement((level % 3) + 1) < node->key.getElement((level % 3) + 1)) {
            findHelper(node->left, px, level + 1, minDist, closest);
        } else {
            findHelper(node->right, px, level + 1, minDist, closest);
        }
    }

public:
    KDtree() : root(nullptr) {}

    // get height of tree
    int getH() { return root->height; }

    // update tree height
    void updateH(KDnode*& node) {
        int leftHeight = 0;
        if(node->left != nullptr) {
            leftHeight = node->left->height;
        }

        int rightHeight = 0;
        if(node->right != nullptr) {
            rightHeight = node->right->height;
        }

        node->height = std::max(leftHeight, rightHeight) + 1;}

    // insert function
    void insert(Pixel& px, V& newVal) {
        if (root == nullptr) {
            root = new KDnode(px, newVal, 0);
        }
        else {
            return insertHelper(root, px, newVal, 0);
        }
        }

    // find function
    V& find(Pixel& px) {
        double minDist = DBL_MAX;
        KDnode* closest = root;

        findHelper(root, px, 0, minDist, closest);
        return closest->val;
    }
};

#endif //PHOTOMOSAIC_KDTREE_H
