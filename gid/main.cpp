#include "gid.hpp"

int main(){
    GID gid("new.gid");
    gid.add_File({"main.cpp"});
    // gid.print_files();
    gid.make();

    gid.open();
    // gid.print_files();
    // gid.print_files_data();
    gid.make_from_open("file");
    // std::vector <std::string> file = gid.get_file("main.cpp");
    // std::cout<<gid.file_data[0]<<"\n";
}