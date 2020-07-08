#include <set>
#include <vector>
#include "point.hpp"
#include <iostream>
#include <cmath>
#include <iterator>
#include <algorithm>
#include <limits>

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

void printPointSet(std::pair<point, point> set){
    std::cout<<"the set of points contains the first point"<<std::endl;
    std::cout<<" with x coordinate: "<<set.first.x<<" and y coordinate: "<<set.first.y<<std::endl;
    std::cout<<"and the second point"<<std::endl;
    std::cout<<" with x coordinate: "<<set.second.x<<" and y coordinate: "<<set.second.y<<std::endl;
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

void merge(std::vector<point> vec, int p, int q, int r){
    int n1 = q - p + 1; //length of subarray A[q+1...r]
    int n2 = r - q; //length of subarray A[p...q]
    int i,j,k;

    std::vector<point> left_vec(n1+1); //creating array left with length n1+1
    std::vector<point> right_vec(n2+1);//creating array right with length n1+1

    //copies subarray vec[p..q] into left_vec[1..n1]
    for(i = 0; i<=n1; i++){
        left_vec[i] = vec[p+i-1];
    }
    //copies subarray vec[q+1..r] into right_vec[1..n2]
    for(j = 0; j<n2; j++){
        right_vec[j] = vec[q+j];
    }
    //entinels at the ends of the arrays
    //left_vec[n1+1](std::numeric_limits<int>::max());
    //right_vec[n2+1](std::numeric_limits<int>::max());
    i = 1;
    j = 1;
    for(k=p;k<=r;k++){
        if((left_vec[i].x <= right_vec[j].x) && (left_vec[i].y <= right_vec[j].y)){
            vec[k] = left_vec[i];
            i++;
        }
        else{
            vec[k] = right_vec[j];
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
    std::cout<<"how many points would you like in your array?"<<std::endl;
    int point_number;
    std::vector<point> point_vec;
    std::cin>>point_number;
    point p;
    for(int i=0;i<=point_number;i++){
        p.x = std::rand()%101;
        p.y = std::rand()%101;
        point_vec.push_back(p);
    }

    for (int i = 0; i < point_vec.size(); i++) {
    std::cout << point_vec[i].x << " | " << point_vec[i].y << std::endl;
    }

    mergeSort(point_vec,1,point_vec.size());

    
    return 0;
}