#include "../include/tree.h"

//* Tree class implementation

Tree::Tree(){
    root = NULL;
}

Tree::Tree(Point tl, Point br){
    root = NULL;
    init(tl, br);
}

void Tree::init(Point tl, Point br){
    if (root != NULL){
        std::cout << "Can't initialize this tree, it has already been initialized." << std::endl;
        return;
    }
    if (tl.get_x() >= br.get_y() || tl.get_y() >= br.get_y()){
        std::cout << "Values for top left corner and bottom right corner are unaccaptable" << std::endl;
        return;
    }
    R_Node* new_root = new R_Node(Region(tl, br), NULL, NULL, NULL, 0);
    root = new_root;
}

Node* Tree::expose(){
    return root;
}

bool Tree::is_empty(){
    return root == NULL;
}

void Tree::insert_point(Point p, std::string n){
    if (is_empty()){
        std::cout << "Can not add points to a non-initialized tree." << std::endl;
        return;
    }
    if (find_point(p)){
        std::cout << "Point already exists in the tree." << std::endl;
        return;
    }
    if (find_point_by_name(n)){
        std::cout << "Can not add a point with a duplicate name." << std::endl;
        return;
    }
    R_Node* r = (R_Node*) root;
    if (!r->in_bound(p)){
        std::cout << "Can not add a point that is bigger than the original region." << std::endl;
        return;
    }
    R_Node* found_reg = locate_region(r, p);
    while (found_reg->child_type() == "point"){
        P_Node* temp = (P_Node*) found_reg->get_lmc();
        found_reg->set_lmc(NULL);
        found_reg->divide_region();
        R_Node* temp_found = locate_region(found_reg, temp->get_p());
        temp_found->set_lmc(temp);
        temp->set_parent(temp_found);
        found_reg = locate_region(found_reg, p);
    }
    P_Node* new_point = new P_Node(p, found_reg, NULL, to_upper(n));
    found_reg->set_lmc(new_point);
}

void Tree::clear_canvas(){
    clean(root, root);
    delete root;
    root = NULL;
}

void Tree::clear_points(){
    clean(root, root);
}

void Tree::clear_region(Region rg){
    R_Node* found = search_for_region((R_Node*) root, rg);
    if (! found){
        std::cout << "The region you have selected does not exist." << std::endl;
    } else {
        clean(found, found);
        purge_empty_regions(found);
    }
}

void Tree::remove_point(Point p){
    P_Node* pn = find_point(p);
    if (pn){
        delete_point(pn);
    } else {
        std::cout << "Point doesn't exist!" << std::endl;
    }
}

P_Node* Tree::find_point(Point p){
    if (((R_Node*) root)->in_bound(p)){
        R_Node* reg = locate_region((R_Node*) root, p);
        if (reg->child_type() == "point"){
            if (Point::is_equal(((P_Node*) reg->get_lmc())->get_p(), p)){
                return (P_Node*) reg->get_lmc();
            }
        }
    }
    return NULL;
}

P_Node* Tree::find_point_by_name(std::string n){
    return (P_Node*) locate_point_by_name(root, n);
}

R_Node* Tree::find_region(Region r){
    R_Node* found = search_for_region((R_Node*) root, r);
    if (found){
        return found;
    }
    return NULL;
}

void Tree::print(){
    list(root);
}

void Tree::print_point(Point p){
    Node* found = find_point(p);
    if (! found){
        std::cout << "Point doesn't exist!" << std::endl;
        return;
    }
    trace_point(found);
}

void Tree::print_region(Region r){
    R_Node* found = find_region(r);
    if (found){
        list(found);
    } else {
        std::cout << "The region you selected does not exist." << std::endl;
    }
}

void Tree::draw(){
    if (is_empty()){
        std::cout << "Tree is empty. There is nothing to show." << std::endl;
        return;
    }
    display(root);
}

void Tree::draw_point(Point p){
    Node* found = find_point(p);
    if (! found){
        std::cout << "Point doesn't exist!" << std::endl;
        return;
    }
    display_traverse(root, found);
}

void Tree::draw_region(Region r){
    R_Node* found = find_region(r);
    if (found){
        display(found);
    } else {
        std::cout << "The region you selected does not exist." << std::endl;
    }
}

void Tree::write(File& f){
    f.changeMode("write");
    output(root, f.expose());
}

//! function implementations

R_Node* locate_region(R_Node* root, Point p){
    if (root == NULL){
        return NULL;
    }
    Node* child = root->get_lmc();
    if (child == NULL){
        return root;
    }
    if (child->get_type() == "point"){
        return root;
    }
    R_Node* child_reg = (R_Node*) child;
    while (child_reg != NULL){
        if (child_reg->in_bound(p)){
            break;
        }
        child_reg = (R_Node*) child_reg->get_rs();
    }
    return locate_region(child_reg, p);
}

void list(Node* r){
    static int indent = 0;
    if (r == NULL){
        return;
    }
    if (r->get_type() == "point"){
        std::cout << make_indent(indent) << "POINT: " << ((P_Node*) r)->get_name() << " " << ((P_Node*) r)->get_p().to_str() << std::endl;
        return;
    }
    if (r->get_type() == "region"){
        std::cout << make_indent(indent) << "REGION: " << ((R_Node*) r)->get_r().to_str() << " (zone "<< ((R_Node*) r)->get_zone() << ")" << std::endl;
        Node* p = ((R_Node*) r)->get_lmc();
        while (p != NULL){
            indent++;
            list(p);
            indent--;
            p = p->get_rs();
        }
    }
}

void output(Node* r, std::ostream& out){
    if (r == NULL){
        return;
    }
    if (r->get_type() == "point"){
        out << ((P_Node*) r)->get_name() << " " << ((P_Node*) r)->get_p().to_str() << std::endl;
        return;
    }
    if (r->get_type() == "region"){
        if (((R_Node*) r)->get_zone() == 0){
            out << ((R_Node*) r)->get_r().to_str() << std::endl;
        }
        Node* p = ((R_Node*) r)->get_lmc();
        while (p != NULL){
            output(p, out);
            p = p->get_rs();
        }
    }
}

void delete_point(P_Node* pn){
    R_Node* par = (R_Node*) pn->get_parent();
    par->set_lmc(NULL);
    delete pn;
    purge_empty_regions(par);
}

P_Node* point_under_region(Node* r){
    if (r == NULL){
        return NULL;
    }
    if (r->get_type() == "point"){
        return (P_Node*) r;
    }
    if (r->get_type() == "region"){
        Node* p = ((R_Node*) r)->get_lmc();
        while (p != NULL){
            P_Node* fnd = point_under_region(p);
            if (fnd != NULL){
                return fnd;
            }
            p = p->get_rs();
        }
    }
    return NULL;
}

void clean(Node* r, Node* r2){
    if (r2 == NULL){
        return;
    }
    if (r2->get_type() == "point"){
        ((R_Node*) r2->get_parent())->set_lmc(NULL);
        delete r2;
        return;
    }
    if (r2->get_type() == "region"){
        Node* p = ((R_Node*) r2)->get_lmc();
        while (p != NULL){
            Node* temp = p;
            p = p->get_rs();
            clean(r, temp);
        }
        if (r != r2){
            ((R_Node*) r2->get_parent())->set_lmc(NULL);
            delete r2;
        }
    }
}

void purge_empty_regions(R_Node* rn){
    R_Node* par = rn;
    while (par != NULL){
        R_Node* grandpa = (R_Node*) par->get_parent();
        if (grandpa == NULL){
            break;
        }
        if (count_points(grandpa) == 0){
            Node* empty_reg = grandpa->get_lmc();
            par = grandpa;
            while (empty_reg != NULL){
                Node* temp = empty_reg;
                empty_reg = empty_reg->get_rs();
                delete temp;
            }
            grandpa->set_lmc(NULL);
        } else if (count_points(grandpa) == 1){
            Node* empty_reg = grandpa->get_lmc();
            P_Node* p_temp = point_under_region(grandpa);
            par = grandpa;
            while (empty_reg != NULL){
                Node* temp = empty_reg;
                empty_reg = empty_reg->get_rs();
                delete temp;
            }
            grandpa->set_lmc(p_temp);
            p_temp->set_parent(grandpa);
        } else {
            break;
        }
    }
}

R_Node* search_for_region(R_Node* r, Region a){
    if (r == NULL){
        return r;
    }
    if (Region::is_equal(r->get_r(), a)){
        return r;
    }
    if (r->child_type() == "region"){
        R_Node* p = (R_Node*) r->get_lmc();
        R_Node* found = NULL;
        while (p != NULL){
            found = search_for_region(p, a);
            if (found){
                return found;
            }
            p = (R_Node*) p->get_rs();
        }
    }
    return NULL;
}

std::string make_indent(int n){
    std::string res = "";
    for (int i = 0; i < n; i++){
        res += "\t";
    }
    return res;
}

void trace_point(Node* p){
    static int indent = -1;
    if (p == NULL){
        return;
    }
    if (p->get_type() == "point"){
        trace_point(p->get_parent());
        indent++;
        std::cout << make_indent(indent) << "POINT: " << ((P_Node*) p)->get_name() << " " << ((P_Node*) p)->get_p().to_str() << std::endl;
    } else if (p->get_type() == "region"){
        trace_point(p->get_parent());
        indent++;
        std::cout << make_indent(indent) << "REGION: " << ((R_Node*) p)->get_r().to_str() << " (zone "<< ((R_Node*) p)->get_zone() << ")" << std::endl;
    }
}

Node* locate_point_by_name(Node* r, std::string n){
    if (r == NULL){
        return r;
    }
    if (r->get_type() == "point"){
        if (((P_Node*) r)->get_name() == n){
            return r;
        }
    }
    if (r->get_type() == "region"){
        Node* p = ((R_Node*) r)->get_lmc();
        Node* found = NULL;
        while (p != NULL){
            found = locate_point_by_name(p, n);
            if (found){
                return found;
            }
            p = p->get_rs();
        }
    }
    return NULL;
}