/*
 * Copyright (c) ghgltggamer 2024
 * Written by ghgltggamer
 * LICENSED under the MIT License
 * Written for accessing files from a single file or a virtalised disk. GID stands for Global Injectable Disk
 * This project comes with absolutely no warranty
 * Check out the README.md file for more information
*/
// GID is defined here
// Source
// C++ STL
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// GID class for defining the GID datatype
class GID {
    private: std::string file;
    public:
        std::vector <std::string> gid_files = {}; std::vector <std::string> file_data = {};
        GID (std::string file_name) {
            file = file_name;
        };
        // main methods
        int add_File(std::vector <std::string> files){
            size_t status = 0;
            for (size_t i = 0;i < files.size();i++){
                std::ifstream open_file(files[i]);
                if (open_file.is_open()){
                    gid_files.push_back(files[i]);
                    status = 1;
                }
                else {
                    status = 0;
                    break;
                }
            }

            return status;
        }

        void print_files (){
            std::cout<<"\ngid file 1.0 - File list\n\n";
            for (size_t i = 0;i < gid_files.size();i++){
                std::cout<<gid_files[i]<<"\n";
            }
        }

        void print_files_data (){
            std::cout<<"\ngid file 1.0 - File Data list\n\n";
            for (size_t i = 0;i < file_data.size();i++){
                std::cout<<file_data[i]<<"\n";
            }
        }

        void make(){
            std::ofstream gid_file(file);
            std::string temp, temp_file;
            for (size_t i = 0;i < gid_files.size();i++){
                std::ifstream input_file_open(gid_files[i]);
                while (std::getline(input_file_open, temp)){
                    temp_file += temp + "\n";
                }
                gid_file<<"gid-include-file:"<<gid_files[i]<<".start:"<<temp_file<<gid_files[i]<<".gid-include-file-end;\n";
                temp = "";
                temp_file = temp;
            }
        }

        int open(){
            int status = 0;
            std::ifstream open_file(file);
            std::string temp, temp_file, current_working_file;
            bool can_fetch = false, can_emit = false;
            if (open_file.is_open()){
                while (std::getline(open_file, temp)){
                    if (temp.find("gid-include-file:") != std::string::npos){
                        std::string file_name = temp.substr(temp.find("gid-include-file:") + std::string("gid-include-file:").length(), (temp.find(".start:") - (temp.find("gid-include-file:") + std::string("gid-include-file:").length())));
                        gid_files.push_back(file_name);
                        can_fetch = true;
                        current_working_file = file_name;
                        status = 1;
                    }
                    if (temp.find(current_working_file + ".gid-include-file-end;") != std::string::npos){
                        can_fetch = false;
                        can_emit = true;
                    }
                    if (can_fetch){
                        temp_file += temp + "\n";
                    }
                    if (can_emit){
                        std::string file_main_data = temp_file.substr(temp_file.find("gid-include-file:") + std::string ("gid-include-file:").length()+current_working_file.length()+std::string(".start:").length());
                        file_data.push_back(file_main_data);
                        can_emit = false;
                        can_fetch = false;
                        temp = "";
                        temp_file = temp;
                    }
                }
            }
            else {
                status = 0;
            }
            return status;
        }

        size_t parallel(){
            size_t status = 0;
            if (gid_files.size() == file_data.size()){
                status = 1;
            }
            return status;
        }

        int make_from_open(std::string path=""){
            size_t status = 0;
            if (parallel()){
                for (size_t i = 0;i < gid_files.size();i++){
                    std::ofstream make_file(path+"/"+gid_files[i]);
                    make_file<<file_data[i];
                }
                status = 1;
            }
            return status;
        }

        // These are experinmental functions which has some bugs and will be available later
        // std::string get_content(std::string file_name_content){
        //     std::string content;
        //     if (parallel()){
        //         for (size_t i = 0;i < gid_files.size();i++){
        //             if (gid_files[i].find(file_name_content) != std::string::npos){
        //                 content = file_data[i];
        //                 break;
        //             }
        //         }
        //     }
        //     return content;
        // }

        // std::vector <std::string> get_file(std::string file_name_content){
        //     std::vector <std::string> file_meta = {};
        //     if (parallel()){
        //         for (size_t i = 0;i < gid_files.size();i++){
        //             if (gid_files[i] == file_name_content){
        //                 // content = file_data[i];
        //                 file_meta.push_back(gid_files[i]);
        //                 file_meta.push_back(file_data[i]);
        //                 break;
        //             }
        //             else {
        //                 continue;
        //             }
        //         }
        //     }
        //     return file_meta;
        // }

        // std::vector <std::string> get_file_from_index(size_t index){
        //     std::vector <std::string> file_meta = {};
        //     if (parallel()){
        //         if (index <= gid_files.size()){
        //             file_meta.push_back(gid_files[index]);
        //             file_meta.push_back(file_data[index]);
        //         }
        //     }
        //     return file_meta;
        // }
};