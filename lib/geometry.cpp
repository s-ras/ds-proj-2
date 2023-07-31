#include "../include/geometry.h"

//* point class implementations

Point::Point(){
    x = 0.0;
    y = 0.0;
}

Point::Point(double inp_x, double inp_y){
    x = inp_x;
    y = inp_y;
}

std::string Point::to_str(){
    std::string res = dl_to_str(x) + " " + dl_to_str(y);
    return res;
}

double Point::get_x(){
    return x;
}

double Point::get_y(){
    return y;
}

bool Point::is_equal(Point a, Point b){
    return (a.x == b.x) && (a.y == b.y);
}

//* region class implementations

Region::Region(){
    top_left = Point();
    bottom_right = Point();
}

Region::Region(Point tl, Point br){
    top_left = Point(tl);
    bottom_right = Point(br);
}

std::string Region::to_str(){
    std::string res = top_left.to_str() + " " + bottom_right.to_str();
    return res;
}

Point Region::get_tl(){
    return top_left;
}

Point Region::get_br(){
    return bottom_right;
}

bool Region::is_equal(Region a, Region b){
    return Point::is_equal(a.top_left, b.top_left) && Point::is_equal(a.bottom_right, b.bottom_right);
}

//! functions

std::string dl_to_str(double inp){
    std::ostringstream temp;
    temp << inp;
    return temp.str();
}

std::string to_upper(std::string str){
    std::string res = str;
    for (int i = 0; i < res.length(); i++){
        res[i] = toupper(str[i]);
    }
    return res;
}
