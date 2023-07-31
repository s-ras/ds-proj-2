#include "../include/graphics.h"

const int OFFSET = 50;
const int WINDOW_SIZE = 800;
float sc;
double x_off, y_off;
Node* rt, * tp;
bool region_mode;

void calculate_canvas(Region r, double& width, double& height, float& sc, double& x_off, double& y_off){
    x_off = r.get_tl().get_x();
    y_off = r.get_tl().get_y();
    width = r.get_br().get_x() - r.get_tl().get_x();
    height = r.get_br().get_y() - r.get_tl().get_y();
    if (width > height){
        sc = WINDOW_SIZE / width;
    } else {
        sc = WINDOW_SIZE / height;
    }
    height *= sc;
    width *= sc;
}

void draw_square(Region r){
    double width, height, tl_x, tl_y;
    width = r.get_br().get_x() - r.get_tl().get_x();
    height = r.get_br().get_y() - r.get_tl().get_y();
    tl_x = ((r.get_tl().get_x() - x_off) * sc) + OFFSET;
    tl_y = ((r.get_tl().get_y() - y_off) * sc) + OFFSET;
    fill(255, 255, 255);
    stroke(0, 0, 0);
    strokeWeight(0.5);
    rect(tl_x, tl_y, width * sc, height * sc);
}

void draw_canvas(Region r){
    double width, height, tl_x, tl_y;
    width = r.get_br().get_x() - r.get_tl().get_x();
    height = r.get_br().get_y() - r.get_tl().get_y();
    tl_x = OFFSET;
    tl_y = OFFSET;
    fill(255, 255, 255);
    stroke(0,0,0);
    strokeWeight(0.5);
    rect(tl_x, tl_y, width * sc, height * sc);
}

void draw_dot(Point p, std::string n){
    double x, y;
    x = ((p.get_x() - x_off) * sc) + OFFSET;
    y = ((p.get_y() - y_off) * sc) + OFFSET;
    fill(218, 81, 81);
    ellipse(x, y, 1 * sc, 1 * sc);
    fill(228, 19, 0);
    stroke(0,0,0);
    textSize(sc * 3);
    text(p.to_str(), x - (5 * sc), y - (5 * sc));
    fill(15,15,185);
    text(n, x + (5 * sc), y + (5 * sc));
}

void draw_tree(Node* r, Node* r2){
    if (r2 == NULL){
        return;
    }
    if (r2->get_type() == "point"){
        draw_dot(((P_Node*) r2)->get_p(), ((P_Node*) r2)->get_name());
        return;
    }
    if (r2->get_type() == "region"){
        if (r2 == r){
            draw_canvas(((R_Node*) r2)->get_r());
        } else {
            draw_square(((R_Node*) r2)->get_r());
        }
        Node* p = ((R_Node*) r2)->get_lmc();
        while (p != NULL){
            draw_tree(r, p);
            p = p->get_rs();
        }
    }
}

void draw_traverse(Node* r, Node* p){
    if (p == NULL){
        return;
    }
    if (p->get_type() == "point"){
        draw_traverse(r, p->get_parent());
        draw_dot(((P_Node*) p)->get_p(), ((P_Node*) p)->get_name());
    } else if (p->get_type() == "region"){
        draw_traverse(r, p->get_parent());
        if (r == p){
            draw_canvas(((R_Node*) p)->get_r());
        } else {
            draw_square(((R_Node*) p)->get_r());
        }
    }
}

void display(Node* root){
    Region canvas = ((R_Node*) root)->get_r();
    double w_x, w_y;
    calculate_canvas(canvas, w_x, w_y, sc, x_off, y_off);
    rt = root;
    region_mode = true;
    run(w_x + 2 * OFFSET, w_y + 2 * OFFSET, "Displaying Region");
}

void display_traverse(Node* root, Node* point){
    Region canvas = ((R_Node*) root)->get_r();
    double w_x, w_y;
    calculate_canvas(canvas, w_x, w_y, sc, x_off, y_off);
    rt = root;
    tp = point;
    region_mode = false;
    run(w_x + 2 * OFFSET, w_y + 2 * OFFSET, "Displaying Point");
}

void p8g::keyPressed(){}
void p8g::keyReleased(){}
void p8g::mouseMoved(){}
void p8g::mousePressed(){}
void p8g::mouseReleased(){}
void p8g::mouseWheel(float delta){}

void p8g::draw(){
    background(183,183,183);
    if (region_mode){
        draw_tree(rt, rt);
    } else {
        draw_traverse(rt, tp);
    }
}
