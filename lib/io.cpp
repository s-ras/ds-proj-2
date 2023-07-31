#include "../include/io.h"

Point read_point(){
    double x, y;
    do {
        std::cout << "X:?\t";
        std::cin >> x;
        std::cin.ignore();
        if (x < 0.0){
            std::cout << "Negative numbers are not accepted!" << std::endl;
        }
    } while (x < 0.0);
    do {
        std::cout << "Y:?\t";
        std::cin >> y;
        std::cin.ignore();
        if (y < 0.0){
            std::cout << "Negative numbers are not accepted!" << std::endl;
        }
    } while (y < 0);
    return Point(x, y);
}

Node* read_point_by_name(Tree& t, std::string n){
    return t.find_point_by_name(to_upper(n));
}

Point select_point(Tree& t){
    int choice;
    do {
        std::cout << "1- Select point by coordinates\n2- Select point by name\nOptions?\t";
        std::cin >> choice;
        std::cin.ignore();
        if (choice > 2 || choice < 1){
            std::cout << "Invalid option! Try again." << std::endl;
        }
    } while (choice > 2 || choice < 1);
    if (choice == 1){
        return read_point();
    }
    P_Node* found = NULL;
    while (! found){
        found = (P_Node*) read_point_by_name(t, read_name());
        if (! found){
            std::cout << "A point with that name doesn't exist." << std::endl;
        }
    }
    return found->get_p();
}

std::string read_name(){
    std::string nm;
    std::cout << "Name of the point?\t";
    std::cin >> nm;
    std::cin.ignore();
    return to_upper(nm);
}

Region read_region(){
    std::cout << "Top left corner of the region:" << std::endl;
    Point tl = read_point();
    Point br;
    bool is_invalid = true;
    do {
        std::cout << "Bottom right corner of the region:" << std::endl;
        br = read_point();
        if (br.get_y() <= tl.get_y() || br.get_y() <= tl.get_y()){
            std::cout << "Bottom right corner is invalid and does not specify a correct region." << std::endl;
        } else {
            is_invalid = false;
        }
    } while (is_invalid);
    return Region(tl, br);
}

void create_main_region(Tree& t){
    if (t.is_empty()){
        std::cout << "Initialize the main region:" << std::endl;
        std::cout << "Top left corner of the region:" << std::endl;
        Point tl = read_point();
        Point br;
        bool is_invalid = true;
        do {
            std::cout << "Bottom right corner of the region:" << std::endl;
            br = read_point();
            if (br.get_y() <= tl.get_y() || br.get_y() <= tl.get_y()){
                std::cout << "Bottom right corner is invalid and does not specify a correct region." << std::endl;
            } else {
                is_invalid = false;
            }
        } while (is_invalid);
        t.init(tl, br);
    } else {
        std::cout << "Main region already exists!" << std::endl;
    }
}

void build_tree(File& f, Tree& t){
    f.changeMode("read");
    double p1_x, p1_y, p2_x, p2_y;
    std::string rd, nm;
    std::getline(f.expose(), rd, ' ');
    p1_x = std::stod(rd);
    std::getline(f.expose(), rd, ' ');
    p1_y = std::stod(rd);
    std::getline(f.expose(), rd, ' ');
    p2_x = std::stod(rd);
    std::getline(f.expose(), rd, '\n');
    p2_y = std::stod(rd);
    t.init(Point(p1_x, p1_y), Point(p2_x, p2_y));
    if (t.is_empty()){
        std::cout << "Database file is corrupted! Termination program ..." << std::endl;
        exit(1);
    }
    while (std::getline(f.expose(), rd, ' ')){
        nm = rd;
        std::getline(f.expose(), rd, ' ');
        p1_x = std::stod(rd);
        std::getline(f.expose(), rd, '\n');
        p1_y = std::stod(rd);
        t.insert_point(Point(p1_x, p1_y), to_upper(nm));
    }
}

