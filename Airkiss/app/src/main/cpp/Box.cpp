//
// Created by Wesker on 2020/5/25.
//

#include "include/Box.h"
#include "include/logUtils.h"

double Box::sumBox() {
        return Box::getBreadth() + Box::getHeight() + Box::getLength();
}

double Box::getLength() const {
        return length;
}

void Box::setLength(double length) {
        Box::length = length;
}

double Box::getBreadth() const {
        return breadth;
}

void Box::setBreadth(double breadth) {
        Box::breadth = breadth;
}

double Box::getHeight() const {
        return height;
}

void Box::setHeight(double height) {
        Box::height = height;
}

Box::Box() {
        LOGI("Box object was create");
}

Box::Box(double height, double breadth, double length) {
        LOGI("Box1 object was create");
        Box::height = height;
        Box::breadth = breadth;
        Box::length = length;
        ptr = new double;
        *ptr = length;
}

Box::~Box() {
        LOGI("Box object was delete");
}

Box::Box(const Box &box) {
        LOGI("Box copy object was create");
         ptr = new double;
        *ptr = *box.ptr;
}

double friendSum(Box &box, Box &box1) {
        return box.height+box1.breadth;
}


