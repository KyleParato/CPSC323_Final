// Kyle Parato - compiler.cpp
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
    in_file.close();
    output_file.close();
    std::ifstream clean_file;
    clean_file.open("finalp2.txt");
    set_up_indexs();
    if(trace_file(clean_file)){
        std::ifstream from;
        from.open("finalp2.txt");
        std::ofstream cpp_file ("finalp.cpp", std::ofstream::trunc);
        translate_file(from, cpp_file);
    }
}
// sets up conversion functions for string to row/col, and table int to string
void cmp323::set_up_indexs(){
    // row string to row number
    row_index.insert(std::pair<std::string,int>("<prog>",       0));
    row_index.insert(std::pair<std::string,int>("<identifier>", 1));
    row_index.insert(std::pair<std::string,int>("<I>",          2));
    row_index.insert(std::pair<std::string,int>("<dec-list>",   3));
    row_index.insert(std::pair<std::string,int>("<dec>",        4)); 
    row_index.insert(std::pair<std::string,int>("<type>",       5));
    row_index.insert(std::pair<std::string,int>("<stat-list>",  6));
    row_index.insert(std::pair<std::string,int>("<stat>",       7));
    row_index.insert(std::pair<std::string,int>("<write>",      8));
    row_index.insert(std::pair<std::string,int>("<assign>",     9));
    row_index.insert(std::pair<std::string,int>("<expr>",      10));
    row_index.insert(std::pair<std::string,int>("<Q>",         11));
    row_index.insert(std::pair<std::string,int>("<term>",      12));
    row_index.insert(std::pair<std::string,int>("<R>",         13));
    row_index.insert(std::pair<std::string,int>("<factor>",    14));
    row_index.insert(std::pair<std::string,int>("<number>",    15));
    row_index.insert(std::pair<std::string,int>("<N>",         16));
    row_index.insert(std::pair<std::string,int>("<sign>",      17));
    row_index.insert(std::pair<std::string,int>("<digit>",     18));
    row_index.insert(std::pair<std::string,int>("<letter>",    19));
    // column string to column number
    col_index.insert(std::pair<std::string,int>("0", 0));
    col_index.insert(std::pair<std::string,int>("1", 1));
    col_index.insert(std::pair<std::string,int>("2", 2));
    col_index.insert(std::pair<std::string,int>("3", 3));
    col_index.insert(std::pair<std::string,int>("4", 4));
    col_index.insert(std::pair<std::string,int>("5", 5));
    col_index.insert(std::pair<std::string,int>("6", 6));
    col_index.insert(std::pair<std::string,int>("7", 7));
    col_index.insert(std::pair<std::string,int>("8", 8));
    col_index.insert(std::pair<std::string,int>("9", 9));
    col_index.insert(std::pair<std::string,int>("p", 10));
    col_index.insert(std::pair<std::string,int>("q", 11));
    col_index.insert(std::pair<std::string,int>("r", 12));
    col_index.insert(std::pair<std::string,int>("s", 13));
    col_index.insert(std::pair<std::string,int>("+", 14));
    col_index.insert(std::pair<std::string,int>("-", 15));
    col_index.insert(std::pair<std::string,int>("*", 16));
    col_index.insert(std::pair<std::string,int>("/", 17));
    col_index.insert(std::pair<std::string,int>("=", 18));
    col_index.insert(std::pair<std::string,int>("(", 19));
    col_index.insert(std::pair<std::string,int>(")", 20));
    col_index.insert(std::pair<std::string,int>(":", 21));
    col_index.insert(std::pair<std::string,int>(";", 22));
    col_index.insert(std::pair<std::string,int>(",", 23));
    col_index.insert(std::pair<std::string,int>("display",    24));
    col_index.insert(std::pair<std::string,int>("\"value=\"", 25));
    col_index.insert(std::pair<std::string,int>("program",    26));
    col_index.insert(std::pair<std::string,int>("begin",      27));
    col_index.insert(std::pair<std::string,int>("var",        28));
    col_index.insert(std::pair<std::string,int>("end.",        29));
    col_index.insert(std::pair<std::string,int>("integer",    30));
    // table number to string, rules
    table_meaning.insert(std::pair<int,std::string>(101, "program <identifier> ; var <dec-list> begin <stat-list> end."));
    table_meaning.insert(std::pair<int,std::string>(102, "<letter> <I>"));
    table_meaning.insert(std::pair<int,std::string>(103, "<letter> <I>"));
    table_meaning.insert(std::pair<int,std::string>(104, "<digit> <I>"));
    table_meaning.insert(std::pair<int,std::string>(106, "<dec> : <type> ;"));
    table_meaning.insert(std::pair<int,std::string>(107, ", <identifier> <dec>"));
    table_meaning.insert(std::pair<int,std::string>(108, "<identifier> <dec>"));
    table_meaning.insert(std::pair<int,std::string>(109, "integer"));
    table_meaning.insert(std::pair<int,std::string>(111, "<stat> <stat-list>"));
    table_meaning.insert(std::pair<int,std::string>(112, "<write>"));
    table_meaning.insert(std::pair<int,std::string>(113, "<assign>"));
    table_meaning.insert(std::pair<int,std::string>(114, "display ( <write>"));
    table_meaning.insert(std::pair<int,std::string>(115, "\"value=\" , <write>"));
    table_meaning.insert(std::pair<int,std::string>(116, "<identifier> ) ;"));
    table_meaning.insert(std::pair<int,std::string>(117, "<identifier> = <expr> ;"));
    table_meaning.insert(std::pair<int,std::string>(118, "<term> <Q>"));
    table_meaning.insert(std::pair<int,std::string>(119, "+ <term> <Q>"));
    table_meaning.insert(std::pair<int,std::string>(120, "- <term> <Q>"));
    table_meaning.insert(std::pair<int,std::string>(122, "<factor> <R>"));
    table_meaning.insert(std::pair<int,std::string>(123, "* <factor> <R>"));
    table_meaning.insert(std::pair<int,std::string>(124, "/ <factor> <R>"));
    table_meaning.insert(std::pair<int,std::string>(126, "( <expr> )"));
    table_meaning.insert(std::pair<int,std::string>(127, "<identifier>"));
    table_meaning.insert(std::pair<int,std::string>(128, "<number>"));
    table_meaning.insert(std::pair<int,std::string>(129, "<sign> <digit> <N>"));
    table_meaning.insert(std::pair<int,std::string>(130, "<digit> <N>"));
    table_meaning.insert(std::pair<int,std::string>(131, "<digit> <N>"));
    table_meaning.insert(std::pair<int,std::string>(133, "+"));
    table_meaning.insert(std::pair<int,std::string>(134, "-"));
    table_meaning.insert(std::pair<int,std::string>(136, "0"));
    table_meaning.insert(std::pair<int,std::string>(137, "1"));
    table_meaning.insert(std::pair<int,std::string>(138, "2"));
    table_meaning.insert(std::pair<int,std::string>(139, "3"));
    table_meaning.insert(std::pair<int,std::string>(140, "4"));
    table_meaning.insert(std::pair<int,std::string>(141, "5"));
    table_meaning.insert(std::pair<int,std::string>(142, "6"));
    table_meaning.insert(std::pair<int,std::string>(143, "7"));
    table_meaning.insert(std::pair<int,std::string>(144, "8"));
    table_meaning.insert(std::pair<int,std::string>(145, "9"));
    table_meaning.insert(std::pair<int,std::string>(146, "p"));
    table_meaning.insert(std::pair<int,std::string>(147, "q"));
    table_meaning.insert(std::pair<int,std::string>(148, "r"));
    table_meaning.insert(std::pair<int,std::string>(149, "s"));

    // error messages from table
    table_meaning.insert(std::pair<int,std::string>(201, "program is expected\n"));
    table_meaning.insert(std::pair<int,std::string>(203, "begin is expected\n"));
    table_meaning.insert(std::pair<int,std::string>(204, "end. is expected\n"));
    table_meaning.insert(std::pair<int,std::string>(207, "integer is expected\n"));
    table_meaning.insert(std::pair<int,std::string>(321, ": is missing\n"));
    table_meaning.insert(std::pair<int,std::string>(322, "; is missing\n"));
    table_meaning.insert(std::pair<int,std::string>(323, ", is missing\n"));
    table_meaning.insert(std::pair<int,std::string>(350, "expecting identifier\n"));
    table_meaning.insert(std::pair<int,std::string>(351, "identifier must start with letter\n"));
    table_meaning.insert(std::pair<int,std::string>(401, "unkown character\n"));
    table_meaning.insert(std::pair<int,std::string>(402, "expecting operation before (\n"));
    table_meaning.insert(std::pair<int,std::string>(403, "missing operand\n"));
    table_meaning.insert(std::pair<int,std::string>(410, "cannot perform operations while declaring variables\n"));
    table_meaning.insert(std::pair<int,std::string>(411, "cannot assign while declaring variables\n"));
}
// cleans code, removes comments and extra whitespacing, properly spaces out tokens
void cmp323::clean_code(std::ifstream& input_file, std::ofstream& output_file){
    std::string token;
    std::string temp;
    std::string output;
    while(input_file >> token){
        // removes comments
        if(token.find("//") != std::string::npos){
            input_file >> token;
            while(token.find("//") == std::string::npos){
                input_file >> token;
            }
            continue;
        }
        else{
            for(int i = 0; i < token.length(); i++){
                for(char nonterm : spacing_nonterminals){
                    if(token.at(i) == '\"'){
                        i++;
                        while(token.at(i) != '\"'){
                            i++;
                        }
                        i++;
                    }
                    // add space if nonterminal
                    if(token.at(i) == nonterm){
                        temp = token.substr(0,i);
                        temp += " ";
                        temp += token.at(i);
                        temp += " ";
                        temp += token.substr(i+1);
                        token = temp;
                        i++;
                    }
                }
            }
            output += token + " ";
            if(token.find(";") != std::string::npos || token == "var" || token == "begin"){
                output += "\n";
            }
        }
    }
    // remove excess spaces
    for(int i = 1; i < output.length(); i++){
        if(output.at(i) == ' ' && output.at(i-1) == ' '){
            temp = output.substr(i);
            output = output.substr(0,i-1);
            output += temp;
            i--;
        }
    }
    output_file << output;
}

// traces file token by token
bool cmp323::trace_file(std::ifstream& file){
    bool accepted = true;
    bool read_var = true;
    std::string current_token;
    trace_stack.empty();
    trace_stack.push("<prog>");
    while(file >> current_token){
        //std::cout << "Read: " << current_token << "\n"; 
        // store vars
        if(current_token == "begin" && read_var == true){
            read_var = false;
        }
        // find col
        int col;
        bool is_keyword = false;
        // checks if token is keyword
        for(auto i : keywords){
            if(i == current_token){
                col = str_to_col(current_token);
                is_keyword = true;
                break;
            }
        }
        // checks if token is variable
        bool is_var = false;
        for(auto i : var_list){
            if(i == current_token){
                is_var = true;
                break;
            }
        }
        bool match = false;
        if(is_keyword){
            while(!match){
                std::string top = trace_stack.top();
                //std::cout << "Pop: " << top << "\n";
                trace_stack.pop();
                if(top == current_token){
                    //std::cout << "  Match: " << top << "\n";
                    match = true;
                    continue;
                }
                int row = str_to_row(top);
                if(row == -1){
                    accepted = false;
                    break;
                }
                //std::cout << table[row][col] << "\n";
                if(table[row][col] > 199 && table[row][col] < 899){
                        std::cout << table_to_string(row, col);
                        accepted = false;
                        break;
                }
                if(table[row][col] == 999){
                    continue;
                }
                //std::cout << "  [ " << top << ", " << current_token << " ] = " << table[row][col] << "\n";
                str_to_stack(table_to_string(row, col));
                //print_stack();
            }
        }
        else{
            for(char c : current_token){
                std::string curent_character = "";
                curent_character += c;
                //std::cout << "  Read: " << curent_character << "\n";
                col = str_to_col(curent_character);
                match = false;
                while(!match){
                    std::string top = trace_stack.top();
                    //std::cout << "Pop: " << top << "\n";
                    trace_stack.pop();
                    if(top == curent_character){
                        //std::cout << "  Match: " << top << "\n";
                        match = true;
                        continue;
                    }
                    int row = str_to_row(top);
                    if(row == -1){
                        accepted = false;
                        break;
                    }
                    if(table[row][col] > 199 && table[row][col] < 599){
                        std::cout << table_to_string(row, col);
                        accepted = false;
                        break;
                    }
                    if(table[row][col] >499 && table[row][col] < 899){
                        std::cout << "Error: " << table[row][col] << "\n";
                        std::cout << "Exiting program\n";
                        exit(0);
                    }
                    if(table[row][col] == 999){
                        continue;
                    }
                    //std::cout << "  [ " << top << ", " << curent_character << " ] = " << table[row][col] << "\n";
                    str_to_stack(table_to_string(row, col));
                    //print_stack();
                }
                if(accepted == false) break;
            }
            if(accepted){
                if(current_token.at(0) == 'p' || current_token.at(0) == 'q' || current_token.at(0) == 'r' || current_token.at(0) == 's'){
                    if(read_var == false){
                        bool in_list = false;
                        for(auto i : var_list){
                            if(i == current_token){
                                in_list = true;
                                break;
                            }
                        }
                        if(in_list == false){
                            accepted = false;
                            std::cout << "Unkown identifier->" << current_token << "\n";
                        }
                    }
                    else if(read_var == true){
                        var_list.push_back(current_token);
                    }
                    else{
                        std::cout << "Unkown identifier->" << current_token << "\n";
                        accepted = false;
                    }
                }
            }
        }
        if(accepted == false) break;
    }
    if(!accepted){
        std::cout << "File not accepted\n";
        return accepted;
    }
    else {
        std::cout << "File accepted\n";
        return accepted;
    }
}
// converts code into c++ code
void cmp323::translate_file(std::ifstream& input_file, std::ofstream& output_file){
    output_file << "#include <iostream>\nusing namespace std;\nint main(){\n";
    std::string temp = var_list.at(0);
    var_list.at(0) = var_list.at(var_list.size() -1);
    var_list.pop_back();
    for(auto i : var_list){
        output_file << "    int " << i << ";\n";
    }
    // read till begin token
    while(input_file >> temp){
        if(temp == "begin") break;
    }
    output_file << "    ";
    while(input_file >> temp){
        if(temp == "end."){
            output_file << "return 0;\n}\n";
            break;
        }
        else if(temp == "display"){
            output_file << "std::cout << ";
            input_file >> temp;
            input_file >> temp;
            if(temp == "\"value=\""){
                output_file << "\"value=\" << ";
                input_file >> temp;
                input_file >> temp;
            }
            output_file << temp + " << \"\\n\";\n    ";
            input_file >> temp;
            input_file >> temp;
        }
        else if(temp == ";"){
            output_file <<temp << "\n" << "    ";
        }
        else{
            output_file << temp;
        }
    }
}
// prints content of stack
void cmp323::print_stack(){
    std::cout << "  Stack: ";
    std::stack<std::string> temp1 = trace_stack;
    std::stack<std::string> temp2;
    while(!temp1.empty()){
        temp2.push(temp1.top());
        temp1.pop();
    }
    while(!temp2.empty()){
        std::cout << temp2.top() << " ";
        temp2.pop();
    }
    std::cout << "\n";
}
// pushes string onto stack, words in reverse order
void cmp323::str_to_stack(std::string input){
    std::stack<std::string> temp;
    std::string temp_str = "";
    for(char c : input){
        if(c != ' '){
            temp_str += c;
        }
        else{
            temp.push(temp_str);
            temp_str = "";
        }
    }
    temp.push(temp_str);
    while(!temp.empty()){
        trace_stack.push(temp.top());
        temp.pop();
    }
}
// converts string to row index
int cmp323::str_to_row(std::string input){
    auto in_map = row_index.find(input);
    if(in_map != row_index.end()){
        return in_map->second;
    }
    std::cout << input << " is missing or expected\n";
    exit(0);
    return -1;
}
// converts string to column index
int cmp323::str_to_col(std::string input){
    auto in_map = col_index.find(input);
    if(in_map != col_index.end()){
        return in_map->second;
    }
    return 31; // unknown token
}
// convets table content to string
std::string cmp323::table_to_string(int row, int col){
    int table_value = table[row][col];
    auto in_map = table_meaning.find(table_value);
    if(in_map != table_meaning.end()){
        return in_map->second;
    }
    std::cout << "Something went wrong in table\n";
    std::cout << "Coordinates: " << row << ", " << col << "\n";
    exit(0);
    return "";
}