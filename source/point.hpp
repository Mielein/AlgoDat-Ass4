#ifndef POINT_HPP
#define POINT_HPP
#include <iostream>
#include <string>

struct point{
    //point struct with x and y coordinates 
    //point should be initialized with a random number from 0 to 100
    int x = rand()%101;
    int y = rand()%101;

};

#endif