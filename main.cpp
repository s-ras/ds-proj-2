#include <iostream>
#include "include/tree.h"
#include "include/filehandling.h"
#include "include/io.h"
#include "include/interface.h"

const std::string FILE_NAME = "data.txt";

int main(){

    Tree t;

    File f(FILE_NAME);
    if (f.is_new_file()){
        create_main_region(t);
    } else {
        build_tree(f, t);
    }

    menu(t);

    t.write(f);

    return 0;

}
