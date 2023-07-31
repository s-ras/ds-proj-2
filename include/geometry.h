#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <string>
#include <sstream>

//* class prototypes

class Point{
    private:
        double x;
        double y;
    public:
        Point();
        Point(double, double);
        std::string to_str();
        double get_x();
        double get_y();
        static bool is_equal(Point, Point);
};

class Region{
    private:
        Point top_left;
        Point bottom_right;
    public:
        Region();
        Region(Point, Point);
        std::string to_str();
        Point get_tl();
        Point get_br();
        static bool is_equal(Region, Region);
        friend Point read_point();
};

//! functions

std::string dl_to_str(double);
std::string to_upper(std::string);

#endif