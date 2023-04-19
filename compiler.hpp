#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <stack>
#include <vector>

class cmp323{
    public:
        cmp323();
        cmp323(std::string input_file);
        void set_up_indexs(); // step up inde
        int str_to_row(std::string input);
        int str_to_col(std::string input);
        std::string table_to_string(int row, int col);

        void str_to_stack(std::string input);

        void print_stack();

        void clean_code(std::ifstream& input_file, std::ofstream& output_file);
        bool trace_file(std::ifstream& file);
        void translate_file(std::ifstream& input_file, std::ofstream& output_file);

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
        std::stack<std::string> trace_stack;

        std::string keywords [7] = {"program", "var", "begin", "end.", "integer", "display", "\"value=\""};
        char spacing_nonterminals [11] = {':', ';', '(', ')', '=', '+', '-', '*', '/', '"', ','};
        std::string rules [47];
                                  // 0   1   2   3   4   5   6   7   8   9   p   q   r   s   +   -   *   /   =   (   )   :   ;   ,  display "value=" program begin var end. integer  $
        int table [20][32] ={/*A*/ {201,201,201,201,201,201,201,201,201,201,201,201,201,201,201,201,201,201,201,201,201,201,201,201,   201,     201,     101,  201,201,201,     201,201}, /*<prog>*/
                             /*B*/ {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,102,102,102,102,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,     0,       0,       0,    0,  0,  0,       0, 0}, /*<identifier>*/
                             /*C*/ {104,104,104,104,104,104,104,104,104,104,103,103,103,103,999,999,999,999,999,  0,999,999,999,999,   322,       0,       0,    0,322,  0,     321, 0}, /*I*/
                             /*D*/ {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,106,106,106,106,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,     0,       0,       0,    0,104,  0,       0, 0}, /*<dec-list>*/
                             /*E*/ {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,108,108,108,108,  0,  0,  0,  0,  0,  0,  0,999,  0,107,     0,       0,       0,    0,  0,  0,       0, 0}, /*<dec>*/
                             /*F*/ {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,     0,       0,       0,    0,  0,  0,     109, 0}, /*<type>*/
                             /*G*/ {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,111,111,111,111,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   111,       0,       0,  111,  0,999,       0,204}, /*<stat-list>*/
                             /*H*/ {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,113,113,113,113,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   112,       0,       0,    0,  0,  0,       0, 0}, /*<stat>*/
                             /*I*/ {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,116,116,116,116,  0,  0,  0,  0,  0,  0,  0,  0,  0,999,   114,     115,       0,    0,  0,  0,       0, 0}, /*<write>*/
                             /*J*/ {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,117,117,117,117,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   322,       0,       0,    0,  0,  0,       0, 0}, /*assign*/
                             /*K*/ {118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,  0,  0,  0,118,  0,  0,  0,  0,     0,       0,       0,    0,  0,  0,       0, 0}, /*<expr>*/
                             /*L*/ {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,119,120,  0,  0,  0,  0,999,  0,999,  0,     0,       0,       0,    0,  0,  0,       0, 0}, /*Q*/
                             /*M*/ {122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,  0,  0,  0,122,  0,  0,  0,  0,     0,       0,       0,    0,  0,  0,       0, 0}, /*<term>*/
                             /*N*/ {  0,  0,  0,  0,  0,  0,  0,  0,  0,322,322,322,322,322,999,999,123,124,  0,  0,999,  0,999,  0,   322,       0,       0,    0,  0,  0,       0, 0}, /*R*/
                             /*O*/ {128,128,128,128,128,128,128,128,128,128,127,127,127,127,  0,  0,  0,  0,  0,126,  0,  0,  0,  0,     0,       0,       0,    0,  0,  0,       0, 0}, /*<factor>*/
                             /*P*/ {130,130,130,130,130,130,130,130,130,130,  0,  0,  0,  0,129,129,  0,  0,  0,  0,  0,  0,  0,  0,     0,       0,       0,    0,  0,  0,       0, 0}, /*<number>*/
                             /*Q*/ {131,131,131,131,131,131,131,131,131,131,999,999,999,999,999,999,999,  0,  0,  0,999,  0,999,  0,     0,       0,       0,    0,  0,  0,       0, 0}, /*N*/
                             /*R*/ {999,999,999,999,999,999,999,999,999,999,  0,  0,  0,  0,133,134,  0,  0,  0,  0,  0,  0,  0,  0,     0,       0,       0,    0,  0,  0,       0, 0}, /*<sign>*/
                             /*S*/ {136,137,138,139,140,141,142,143,144,145,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,     0,       0,       0,    0,  0,  0,       0, 0}, /*<digit>*/
                             /*T*/ {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,146,147,148,149,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,     0,       0,       0,    0,  0,  0,       0, 0} /*<letter>*/};

                             // /*Z*/ {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,     0,       0,       0,    0,  0,  0,       0, 0}, /*<>*/
        std::map<int, std::string> table_meaning;
        std::map<std::string, int> row_index;
        std::map<std::string, int> col_index;

        std::vector<std::string> var_list;
};
