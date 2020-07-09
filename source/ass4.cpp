#include <set>
#include <vector>
#include "point.hpp"
#include <iostream>
#include <cmath>
#include <iterator>
#include <algorithm>
#include <list>
#include <limits>

//method to compare points of x coordinate
int comparePoints_x(point const& a, point const& b){
    return a.x - b.x;
}
//method to compare points of y coordinate
int comparePoints_y(point const& a, point const& b){
    return a.y - b.y;
}
//methods to calculate distance
float distance(point const& a, point const& b){
    return sqrt(pow(comparePoints_x(a,b),2)+ pow(comparePoints_y(a,b),2));
}

void printPointSet(std::pair<point, point> set){
    std::cout<<"the set of points contains the first point"<<std::endl;
    std::cout<<" with x coordinate: "<<set.first.x<<" and y coordinate: "<<set.first.y<<std::endl;
    std::cout<<"and the second point"<<std::endl;
    std::cout<<" with x coordinate: "<<set.second.x<<" and y coordinate: "<<set.second.y<<std::endl;
}

//naive algorithm
std::pair<point,point> naive_alg(std::vector<point> vec){
    if(vec.size() < 2){
        throw "try with more points";
    }
    auto pair = std::make_pair(vec[0],vec[1]);
    for(int i = 0;i<vec.size();i++){
        
        for(int j = i+1; i<vec.size();j++){
            std::pair<point,point> closest;
            if(distance(vec[i],vec[j]) < distance(pair.first,pair.second)){
                pair = std::make_pair(vec[i],vec[j]);
            }
        }
    }
    return pair;
}

std::pair<point,point> combine(std::vector<point> y_vec, int l_x, std::pair<point,point> left_pair,std::pair<point,point> right_pair){
    //calculating distances of points
    float d1 = distance(left_pair.first,left_pair.second);
    float d2 = distance(right_pair.first,right_pair.second);
    float d;
    std::pair<point,point> combined_pair;
    //if distance of left_pair is larger than right_pair
    if(d1<d2){
        //new set ist left pair
        combined_pair = left_pair;
        //distance of combined pair is distance of left_pair
        d = d1;
    }
    else{
        //else combined_pair is right_pair
        combined_pair = right_pair;
        //gets distance of right_pair
        d = d2;
    }
    //creating Y’ -> empty array(vector)
    std::vector<point> y_vec2;
    for(int i = 0; i<=y_vec.size(); i++){
        //for each point in y_vec
        if(l_x-d <= y_vec[i].x<l_x+d){
            //add y_vec at position i in y_vec2
            y_vec2.push_back(y_vec[i]);
        }
    }
    //iterating through y_vec2
    for(int i=0; i<=y_vec2.size();i++){
        int j = 1;
        //as long as size of y_vec >= j
        //and y_vec2 >= i+j
        while (j<=y_vec.size() && (i+j)<=y_vec2.size()){
            //calculate distance of y_vec2 at pos. i and y_vec2 at pos. i+j
            float d3 = distance(y_vec2[i],y_vec2[i+j]);
            //if dist. of left_pair is smaller than right_pair
            if(d1<d){
                //combined_pair is new set of points
                combined_pair = std::pair<point, point>(y_vec2[i],y_vec2[i+j]);
                d=d1;
            }
            //increase j
            j++;
        }
    }
    return combined_pair;
}
//method to find closest pair
std::pair<point,point> find_closest_pair(std::vector<point> x_vec, std::vector<point> y_vec){
    if(x_vec.size()==2){
        std::pair<point,point> closest(x_vec[0],x_vec[1]);
        return closest;
    }
    if(x_vec.size()==3){
        return naive_alg(x_vec);
    }
    //m = median of array
    int m = floor(x_vec.size()/2);
    int l_x=(x_vec[m].x+ x_vec[m+1].x)/2;
    //creating two empty subarrays
    std::vector<point> x_lvec;
    std::vector<point> x_rvec;
    //push elements into left array that are in the first half of x_vec
    for(int i=0; i<m; i++){
        x_lvec.push_back(x_vec[i]);
    }
    //push second half
    for(int j = m+1; j<x_vec.size();j++){
        x_rvec.push_back(x_vec[j]);
    }
    //recursive call of find closest_pair
    //for left and right side
    std::pair<point,point> left_pair = find_closest_pair(x_lvec,y_vec);
    std::pair<point,point> right_pair = find_closest_pair(x_rvec,y_vec);
    //combine to subarrays
    std::pair<point,point> combined_pair = combine(y_vec, l_x,left_pair,right_pair);
    //calculating distances
    float d1 = distance(left_pair.first,left_pair.second);
    float d2 = distance(right_pair.first,right_pair.second);
    float d3 = distance(combined_pair.first,combined_pair.second);
    //comparing distances and returning the closest pair
    if(d1<=d2 && d1<=d3){
        return left_pair;
    }
    else if(d2<=d1 && d2 <= d3){
        return right_pair;
    }
    else return combined_pair;
    
}  

//merge sort and merge funktion to sort a vector of points by the x value
void merge_x(std::vector<point> vec, int p, int q, int r){
    int n1 = q - p + 1; //length of subarray A[q+1...r]
    int n2 = r - q; //length of subarray A[p...q]
    int i,j,k;

    std::vector<point> left_vec(n1 + 1); //creating array left with length n1+1
    std::vector<point> right_vec(n2 + 1);//creating array right with length n1+1

    //copies subarray vec[p..q] into left_vec[1..n1]
    for(i = 0; i <= n1; i++){
        left_vec[i] = vec[p + i - 1];
    }
    //copies subarray vec[q+1..r] into right_vec[1..n2]
    for(j = 0; j < n2; j++){
        right_vec[j] = vec[q + j];
    }
    //entinels at the ends of the arrays
    //left_vec[n1 + 1](std::numeric_limits<int>::max());
    //right_vec[n2 + 1](std::numeric_limits<int>::max());
    i = 1;
    j = 1;
    for(k=p; k<=r; k++){
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

//merge sort and merge funktion to sort a vector of points by the y value
//mergesort method
void mergeSort_x(std::vector<point> vec, int p, int r){
    if(p < r){
        int q = ((p+r)/2);
        //recursive call
        mergeSort_x(vec,p,q);
        mergeSort_x(vec,q+1,r);
        //call mergesort
        merge_x(vec, p, r, q);
    }
}

void merge_y(std::vector<point> vec, int p, int q, int r) {
    int n1 = q - p + 1; //length of subarray A[q+1...r]
    int n2 = r - q; //length of subarray A[p...q]
    int i, j, k;

    std::vector<point> left_vec(n1 + 1); //creating array left with length n1+1
    std::vector<point> right_vec(n2 + 1);//creating array right with length n1+1

    //copies subarray vec[p..q] into left_vec[1..n1]
    for (i = 0; i <= n1; i++) {
        left_vec[i] = vec[p + i - 1];
    }
    //copies subarray vec[q+1..r] into right_vec[1..n2]
    for (j = 0; j < n2; j++) {
        right_vec[j] = vec[q + j];
    }
    //entinels at the ends of the arrays
    //left_vec[n1 + 1](std::numeric_limits<int>::max());
    //right_vec[n2 + 1](std::numeric_limits<int>::max());
    i = 1;
    j = 1;
    for (k = p; k <= r; k++) {
        if ((left_vec[i].x <= right_vec[j].x) && (left_vec[i].y <= right_vec[j].y)) {
            vec[k] = left_vec[i];
            i++;
        }
        else {
            vec[k] = right_vec[j];
            j++;
        }
    }
}
//mergesort method
void mergeSort_y(std::vector<point> vec, int p, int r) {
    if (p < r) {
        int q = ((p + r) / 2);
        //recursive call
        mergeSort_y(vec, p, q);
        mergeSort_y(vec, q + 1, r);
        //call mergesort
        merge_y(vec, p, r, q);
    }
}


int main(){
    std::cout<<"how many points would you like in your array?"<<std::endl;
    int point_number;
    std::vector<point> point_vec;
    std::cin>>point_number;
    point p;
    for(int i=0; i<point_number;i++){
        p.x = std::rand()%101;
        p.y = std::rand()%101;
        point_vec.push_back(p);
    }
    
    std::cout << "This is your array of random Points:" << std::endl;
    for (int i = 0; i < point_vec.size(); i++) {
    std::cout << point_vec[i].x << " | " << point_vec[i].y << std::endl;
    }

//tried doing our own sorting method since mergesort gives a stackoverflow
//turns out find_closest_points also gives a stackoverflow
//and i know..no lists..it was just a test  
    std::list<point> pointList_x;
    std::list<point> pointList_y;

    auto sorting_x = [](point p1, point p2)-> bool {return p1.x < p2.x;};
    auto sorting_y = [](point p1, point p2)-> bool {return p1.y < p2.y;};

    std::copy(point_vec.begin(),point_vec.end(),std::back_inserter(pointList_x));
    std::copy(point_vec.begin(),point_vec.end(),std::back_inserter(pointList_y));

    pointList_x.sort(sorting_x);
    pointList_y.sort(sorting_y);

    std::vector<point> point_vec_x;
    std::vector<point> point_vec_y;

    std::copy(pointList_x.begin(),pointList_x.end(),std::back_inserter(point_vec_x));
    std::copy(pointList_y.begin(),pointList_y.end(),std::back_inserter(point_vec_y)); */

    mergeSort_x(point_vec,1,point_vec.size());
    printPointSet(find_closest_pair(point_vec_x,point_vec_y));            

    return 0;
}
//Stackoverflow :/