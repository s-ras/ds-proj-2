#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "../p8g/p8g.h"
#include "geometry.h"
#include "nodes.h"
#include "tree.h"

using namespace p8g;

void draw_canvas(Region);
void draw_square(Region);
void draw_dot(Point, std::string);
void calculate_canvas(Region);
void draw_tree(Node*, Node*);
void display(Node*);
void display_traverse(Node*, Node*);


void p8g::keyPressed();
void p8g::keyReleased();
void p8g::mouseMoved();
void p8g::mousePressed();
void p8g::mouseReleased();
void p8g::mouseWheel(float);
void p8g::draw();


#endif