#include <set>
#include <vector>
#include "point.hpp"
#include <iostream>
#include <cmath>
#include <iterator>
#include <algorithm>

//method to compare points of x coordinate
int comparePoints_x(point const& a, point const& b){
    return a.x - b.x;
}
//method to compare points of y coordinate
int comparePoints_y(point const& a, point const& b){
    return a.y - b.y;
}
float distance(point const& a, point const& b){
    return sqrt(pow(comparePoints_x(a,b),2)+ pow(comparePoints_y(a,b),2));
}

std::pair<point,point> combine(std::vector<point> y_vec, int l_x, std::pair<point,point> left_pair,std::pair<point,point> right_pair){
    float d1 = distance(left_pair.first,left_pair.second);
    float d2 = distance(right_pair.first,right_pair.second);
    float d;
    std::pair<point,point> combined_pair;
    if(d1<d2){
        combined_pair = left_pair;
        d = d1;
    }
    else{
        combined_pair = right_pair;
        d = d2;
    }
    std::vector<point> y_vec2;
    for(int i = 0; i<=y_vec.size(); i++){
        if(l_x-d <= y_vec[i].x<l_x+d){
            y_vec2.push_back(y_vec[i]);
        }
    }
    //vllt i=1 auch j
    for(int i=0; i<=y_vec2.size();i++){
        int j = 1;
        while (j<=y_vec.size() && (i+j)<=y_vec2.size()){
            float d3 = distance(y_vec2[i],y_vec2[i+j]);
            if(d1<d){
                combined_pair = std::pair<point, point>(y_vec2[i],y_vec2[i+j]);
                d=d1;
            }
            j++;
        }
    }
    return combined_pair;
}

std::pair<point,point> find_closest_pair(std::vector<point> x_vec, std::vector<point> y_vec){
    int m = floor(x_vec.size()/2);
    int l_x=(x_vec[m].x+ x_vec[m+1].x)/2;
    std::vector<point> x_lvec;
    std::vector<point> x_rvec;
    for(int i=0; i<m; i++){
        x_lvec.push_back(x_vec[i]);
    }
    for(int j = m+1; j<x_vec.size();j++){
        x_rvec.push_back(x_vec[j]);
    }
    std::pair<point,point> left_pair = find_closest_pair(x_lvec,y_vec);
    std::pair<point,point> right_pair = find_closest_pair(x_rvec,y_vec);
    std::pair<point,point> combined_pair = combine(y_vec, l_x,left_pair,right_pair);
    float d1 = distance(left_pair.first,left_pair.second);
    float d2 = distance(right_pair.first,right_pair.second);
    float d3 = distance(combined_pair.first,combined_pair.second);
    if(d1<=d2 && d1<=d3){
        return left_pair;
    }
    else if(d2<=d1 && d2 <= d3){
        return right_pair;
    }
    else return combined_pair;
    
}  




void merge(std::vector<point> vec, int p, int r, int q){
    int n1 = p - q + 2;
    int n2 = r - q + 1;
    int i,j,k;

    std::vector<int> left_vec{n1};
    std::vector<int> right_vec{n2};

    for(i = 0; i<n1; i++){
        left_vec[i]= vec[p+i-1];
    }
    //left_vec[n1] = infinite;
    for(j = 0; j<n2; j++){
        right_vec[i]= vec[q+j];
    }
    //left_vec[n2] = infinite;
    i = 1;
    j = 1;
    for(k=p;k<=r;k++){
        if(left_vec[i] <= right_vec[i]){
            vec[k]=left_vec[i];
            i++;
        }
        else{
            vec[k]=right_vec[j];
            j++;
        }
    }
}
//mergesort method
void mergeSort(std::vector<point> vec, int p, int r){
    if(p < r){
        int q = ((p+r)/2);
        mergeSort(vec,p,q);
        mergeSort(vec,q+1,r);
        merge(vec, p, r, q);
    }
}

int main(){

    point p1;
    point p2;
    point p3;
    point p4;
    point p5;
    point p6;
    point p7;
 
    std::vector<point> test{p1, p2, p3, p4, p5, p6, p7};


    for (int i = 0; i < test.size(); i++) {
        std::cout << test[i].x << " | " << test[i].y << std::endl;
    }

    fo

    
    
    return 0;
}