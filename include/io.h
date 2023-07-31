#ifndef IO_H
#define IO_H

#include "tree.h"
#include "geometry.h"
#include "filehandling.h"

Point read_point();
Node* read_point_by_name(Tree&, std::string);
Point select_point(Tree&);
std::string read_name();
Region read_region();
void create_main_region(Tree&);
void build_tree(File&, Tree&);


#endif