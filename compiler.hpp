#include <iostream>
#include <fstream>
#include <string>

class cmp323{
    public:
        cmp323();
        cmp323(std::string input_file);

        void clean_code(std::ifstream& input_file, std::ofstream& output_file);


        // think about steps
        //  1. Clean code
        //      a. remove whitespace
        //      b. remove comments 
        //      c. semi-colon end of line, code on same line
        //  2. Read file line by line
        //      a. convert into usable code
        //          a.a add to table nums
        //      b. use first method of trace
        //      c. convert to instructions
        //  3. convert to code
        //      a. 
        //  store variables in class, only three vars
        //  have functions for all operatons
        //  
        // runtime errors for col and row functions, very important
    private:
        std::string nonterminals [15] = {"program", "var", "begin", "end.", ":", ";", "integer", "display", "(", ")", "=", "+", "-", "*", "/"};
        std::string rules [1];
        int table [1][1];
};
