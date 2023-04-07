#include <iostream>
#include <fstream>
#include <exception>
#include <vector>
#include "compiler.hpp"

cmp323::cmp323(){
    std::ifstream in_file;
    in_file.open("finalp1.txt");
    std::ofstream output_file ("finalp2.txt", std::ofstream::trunc);
    clean_code(in_file, output_file);
}

cmp323::cmp323(std::string input_file){
    std::ifstream file;
    file.open(input_file);
    if(!file.is_open()){throw "File Not Found";}
    std::string output_file_name = input_file.substr(0,input_file.length()-4) + ".cmp323";
    std::ofstream output_file (output_file_name);
    clean_code(file, output_file);
}

void cmp323::clean_code(std::ifstream& input_file, std::ofstream& output_file){
    std::cout << "Called clean code\n";
    //clean code
    
    //take out all comments
    //  getline
    //  remove whitespace 
    //  remove whitespace

    //take out all comments vector approach
    std::string current_line;
    std::vector<std::string> all_lines;
    while (getline(input_file, current_line))
    {
        all_lines.push_back(current_line);
    }
    int line_num = all_lines.size();
    for(int i = 0; i < line_num; i++){
        
        // contains comment
        if(all_lines.at(i).find("//") != std::string::npos){
            // find all positions of // and store them
            // if odd, check for comment on next line
            //  if no comment, remove end of line

            all_lines.at(i) = all_lines.at(i).substr(0,all_lines.at(i).find("//"));
            
            // // on next line
            if(all_lines.at(i+1).find("//") != std::string::npos){
                all_lines.at(i+1) = all_lines.at(i+1).substr(all_lines.at(i+1).find("//"));
            }
        }
        // seperate ; to new line

        // remove spaces
        std::string remove_first_spaces = "";
        while (all_lines.at(i).at(0) == ' '){
            remove_first_spaces = all_lines.at(i).substr(1);
            all_lines.at(i) = remove_first_spaces;
        }

        // for(int ii = 1; ii < all_lines.at(i).length() -1; ii++){
        //     if(all_lines.at(i).at(ii) == ' ' && all_lines.at(i).at(ii) == ' '){
        //         remove_first_spaces = all_lines.at(i).substr(ii);
        //         all_lines.at(i) = all_lines.at(i).substr(0,ii-1);
        //         all_lines.at(i) += remove_first_spaces;
        //         ii--;
        //     }
        // }

        //all_lines.at(i) = remove_spaces;



        // make sure there is a space before and after ; : + = * / ( ), all non terminals
        // for(int ii = 0; ii < nonterminals->size(); ii++){
        //     auto it = all_lines.at(i).find(nonterminals->at(ii));
        //     while(it != std::string::npos){
        //        // temp string
        //        // check for space before and after
        //        // add spaces 
        //     }
        // }
    
        
        output_file << all_lines.at(i);
        
    }
    

}