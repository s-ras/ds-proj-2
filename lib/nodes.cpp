#include "../include/nodes.h"

//* Node class implementation

Node::Node(){
    right_sibling = NULL;
    parent = NULL;
}

void Node::set_rs(Node* n){
    if (n == NULL){
        right_sibling = n;
        return;
    }
    if (this->get_type() == n->get_type()){
        right_sibling = n;
    } else {
        std::cout << "Can not assign a node of type " << n->get_type() << " as the right sibling of a node of type " << this->get_type() << "." << std::endl;
    }
}

Node* Node::get_rs(){
    return right_sibling;
}

void Node::set_parent(Node* par){
    if (par == NULL){
        parent = par;
        return;
    }
    if (this->get_type() == "region" && par->get_type() == "region"){
        parent = par;
    } else if (this->get_type() == "point" && par->get_type() == "region"){
        parent = par;
    } else {
        std::cout << "Can not assign a node of type " << par->get_type() << " as the parent of a node of type " << this->get_type() << "." << std::endl;
    }
}

Node* Node::get_parent(){
    return parent;
}

//* P_Node class implementation

P_Node::P_Node(){
    this->set_p(Point(0,0));
    this->set_parent(NULL);
    this->set_rs(NULL);
}

P_Node::P_Node(Point pnt, Node* par, Node* rs, std::string nm){
    this->set_p(pnt);
    this->set_parent(par);
    this->set_rs(rs);
    this->set_name(nm);
}

void P_Node::set_p(Point pnt){
    p = pnt;
}

Point P_Node::get_p(){
    return p;
}

void P_Node::set_name(std::string nm){
    name = nm;
}

std::string P_Node::get_name(){
    return name;
}

std::string P_Node::get_type(){
    return "point";
}

//* R_Node class implementation

R_Node::R_Node(){
    this->set_r(Region());
    this->set_parent(NULL);
    this->set_lmc(NULL);
    this->set_rs(NULL);
    this->set_zone(-1);
}

R_Node::R_Node(Region rg, Node* par, Node* lmc, Node* rs, int z){
    this->set_r(rg);
    this->set_parent(par);
    this->set_lmc(lmc);
    this->set_rs(rs);
    this->set_zone(z);
}

R_Node::~R_Node(){
    delete[] border;
}

void R_Node::set_r(Region rg){
    region = rg;
}

Region R_Node::get_r(){
    return region;
}

void R_Node::set_lmc(Node* lmc){
    left_most_child = lmc;
}

Node* R_Node::get_lmc(){
    return left_most_child;
}

void R_Node::set_zone(int z){
    if (z > 4 || z < 0){
        return;
    }
    if (z == 0){
        bool par_border[4] = {true};
        set_borders(par_border, this->border, z);
        this->zone = z;
        return;
    }
    if (this->get_parent() == NULL){
        std::cout << "Can't set zone for a parentless node." << std::endl;
        return;
    }
    R_Node* par = (R_Node*) this->get_parent();
    set_borders(par->border, this->border, z);
    this->zone = z;
}

int R_Node::get_zone(){
    return zone;
}

std::string R_Node::child_type(){
    if (left_most_child == NULL){
        return "empty";
    }
    return left_most_child->get_type();
}

bool R_Node::side(std::string s){
    if (s == "up"){
        return border[0];
    } else if (s == "down"){
        return border[1];
    } else if (s == "left"){
        return border[2];
    } else if (s == "right"){
        return border[3];
    }
    return false;
}

bool R_Node::is_empty(){
    if (child_type() == "empty"){
        return true;
    }
    return false;
}

bool R_Node::in_bound(Point p){
    bool res_x = false;
    bool res_y = false;
    Region r = this->get_r();
    if (p.get_x() == r.get_br().get_x() && p.get_y() == r.get_br().get_y()){
        return true;
    }
    if (side("left") && side("right")){
        res_x = p.get_x() >= r.get_tl().get_x() && p.get_x() <= r.get_br().get_x();
    } else if (side("left") && !side("right")){
        res_x = p.get_x() >= r.get_tl().get_x() && p.get_x() < r.get_br().get_x();
    } else if (!side("left") && side("right")){
        res_x = p.get_x() > r.get_tl().get_x() && p.get_x() <= r.get_br().get_x();
    } else {
        res_x = p.get_x() > r.get_tl().get_x() && p.get_x() < r.get_br().get_x();
    }
    if (side("up") && side("down")){
        res_y = p.get_y() >= r.get_tl().get_y() && p.get_y() <= r.get_br().get_y();
    } else if (side("up") && !side("down")){
        res_y = p.get_y() >= r.get_tl().get_y() && p.get_y() < r.get_br().get_y();
    } else if (!side("up") && side("down")){
        res_y = p.get_y() > r.get_tl().get_y() && p.get_y() <= r.get_br().get_y();
    } else {
        res_y = p.get_y() > r.get_tl().get_y() && p.get_y() < r.get_br().get_y();
    }
    return res_x && res_y;
}

bool R_Node::has_points(){
    if (count_points(this) == 0){
        return false;
    }
    return true;
}

void R_Node::divide_region(){
    if (this->child_type() == "region"){
        std::cout << "Can not divide this region." << std::endl;
        return;
    }
    double nx = region.get_tl().get_x() + ((region.get_br().get_x() - region.get_tl().get_x()) / 2);
    double ny = region.get_tl().get_y() + ((region.get_br().get_y() - region.get_tl().get_y()) / 2);
    Point p1(nx, ny), p2(nx, region.get_tl().get_y()), p3(region.get_br().get_x(), ny), p4(region.get_tl().get_x(), ny), p5(nx, region.get_br().get_y());
    R_Node* z_4 = new R_Node(Region(p4, p5), this, NULL, NULL, 4);
    R_Node* z_3 = new R_Node(Region(p1, this->get_r().get_br()), this, NULL, z_4, 3);
    R_Node* z_2 = new R_Node(Region(p2, p3), this, NULL, z_3, 2);
    R_Node* z_1 = new R_Node(Region(this->get_r().get_tl(), p1), this, NULL, z_2, 1);
    this->set_lmc(z_1);
}

std::string R_Node::get_type(){
    return "region";
}

//! function implementations

/* border array guide for zones
    zone 1: T, F, T, T
    zone 2: T, T, F, T
    zone 3: F, T, T, T
    zone 4: T, T, T, F
*/
void set_borders(bool par_border[], bool border[], int zone){
    if (zone == 0){
        for (int i = 0; i <= 4; i++){
            border[i] = true;
        }
        return;
    }
    for (int i = 0; i <= 4; i++){
        border[i] = par_border[i];
    }
    switch (zone){
        case 0:
            break;
        case 1:
            border[1] = false;
            break;
        case 2:
            border[2] = false;
            break;
        case 3:
            border[0] = false;
            break;
        case 4:
            border[3] = false;
            break;
        default:
            break;
    }
}

int count_points(Node* r){
    int res = 0;
    if (r == NULL){
        return res;
    }
    if (r->get_type() == "point"){
        res++;
        return res;
    }
    if (r->get_type() == "region"){
        Node* p = ((R_Node*) r)->get_lmc();
        while (p != NULL){
            res += count_points(p);
            p = p->get_rs();
        }
    }
    return res;
}