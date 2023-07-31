#include "../include/interface.h"

int print_options(){
    int choice;
    do {
        std::cout << "1- List all points(CLI)\n2- Trace point (CLI)\n3- List all points in a region (CLI)\n4- Insert point\n5- Remove point\n6- Clear all points in a region\n7- Clear all points in canvas\n8- Clear canvas and create a new canvas\n9- Display canvas (GUI)\n10- Display a point (GUI)\n11- Display a region (GUI)\n12- exit\nOptions?\t";
        std::cin >> choice;
        std::cin.ignore();
        if (choice > 12 || choice < 1){
            std::cout << "Invalid option! Try again." << std::endl;
        }
    } while (choice > 12 || choice < 1);
    return choice;
}

void menu(Tree& t){
    while (true){
        int choice = print_options();
        std::cout << "--------------------------------------------------------------------" << std::endl;
        switch (choice){
            case 1:
                t.print();
                break;
            case 2:
                t.print_point(select_point(t));
                break;
            case 3:
                t.print_region(read_region());
                break;
            case 4:
                t.insert_point(read_point(), read_name());
                std::cout << "Done!" << std::endl;
                break;
            case 5:
                t.remove_point(select_point(t));
                std::cout << "Done!" << std::endl;
                break;
            case 6:
                t.clear_region(read_region());
                std::cout << "Done!" << std::endl;
                break;
            case 7:
                t.clear_points();
                std::cout << "Done!" << std::endl;
                break;
            case 8:
                t.clear_canvas();
                create_main_region(t);
                std::cout << "Done!" << std::endl;
                break;
            case 9:
                t.draw();
                break;
            case 10:
                t.draw_point(select_point(t));
                break;
            case 11:
                t.draw_region(read_region());
                break;
            case 12:
                return;
                break;
            default:
                break;
        }
        std::cout << "--------------------------------------------------------------------" << std::endl;
    }
}