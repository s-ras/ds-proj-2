#ifndef TREE_H
#define TREE_H

#include "nodes.h"
#include "geometry.h"
#include "filehandling.h"
#include "graphics.h"
#include <iostream>
#include <sstream>

//* class prototypes

class Tree{
    private:
        Node* root;
    public:
        Tree();
        Tree(Point, Point);
        void init(Point, Point);
        Node* expose();
        bool is_empty();
        void insert_point(Point, std::string);
        void clear_canvas();
        void clear_points();
        void clear_region(Region);
        void remove_point(Point);
        P_Node* find_point(Point);
        P_Node* find_point_by_name(std::string);
        R_Node* find_region(Region);
        void print();
        void print_point(Point);
        void print_region(Region);
        void draw();
        void draw_point(Point);
        void draw_region(Region);
        void write(File&);
};

//! function prototypes

R_Node* locate_region(R_Node*, Point);
void list(Node*);
void output(Node*, std::ostream&);
void delete_point(P_Node* pn);
void clean(Node*, Node*);
P_Node* point_under_region(Node*);
void purge_empty_regions(R_Node*);
R_Node* search_for_region(R_Node*, Region);
std::string make_indent(int);
void trace_point(Node*);
Node* locate_point_by_name(Node*, std::string);

#endif