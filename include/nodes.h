#ifndef NODES_H
#define NODES_H

#include <iostream>
#include "geometry.h"

//* class prototypes

class Node{
    private:
        Node* right_sibling;
        Node* parent;
    public:
        Node();
        void set_rs(Node*);
        Node* get_rs();
        void set_parent(Node*);
        Node* get_parent();
        virtual std::string get_type() = 0;
};

class P_Node : public Node{
    private:
        Point p;
        std::string name;
    public:
        P_Node();
        P_Node(Point, Node*, Node*, std::string);
        void set_p(Point);
        Point get_p();
        void set_name(std::string);
        std::string get_name();
        virtual std::string get_type();
};

class R_Node : public Node{
    private:
        Region region;
        Node* left_most_child;
        int zone = -1;
        bool* border = new bool(4);
    public:
        R_Node();
        R_Node(Region, Node*, Node*, Node*, int);
        ~R_Node();
        void set_r(Region);
        Region get_r();
        void set_lmc(Node*);
        Node* get_lmc();
        void set_zone(int);    
        int get_zone();
        std::string child_type();
        bool side(std::string);
        bool is_empty();
        bool in_bound(Point);
        bool has_points();
        void divide_region();
        virtual std::string get_type();
};

//! functions prototypes

void set_borders(bool[], bool[], int);
int count_points(Node*);

#endif