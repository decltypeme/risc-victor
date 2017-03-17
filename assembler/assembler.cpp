#include <fstream>
#include <string>
#include <regex>
#include <iostream>
#include <cstdlib>
#include <bitset>

using namespace std;

regex R_TYPE_PATTERN(string("(add|sub|sll|slt|sltu|xor|srl|sra|or|and)\\s*([0-9]+),\\s*([0-9]+)\\s*,\\s*([0-9]+)\\s*"));

string translate_register(string register_number){
  int reg = stoi(register_number);
  stringstream sstream;
  sstream << std::bitset<32>(reg);
  string reg_binary = sstream.str();
  return reg_binary.substr(27);
}

string assemble_instruction(string in_inst){
  smatch sm;
  if(regex_match (in_inst,sm,R_TYPE_PATTERN)){
    string inst_name = sm[1];
    string rd        = sm[2];
    string rs1       = sm[3];
    string rs2       = sm[4];
    string opcode = "0010011";
    string func7  = "0000000";
    string func3  = "000";
    if(inst_name == "sub")
        func7 = "0100000";
    else if(inst_name == "sra")
        func7 = "0100000";
    //Func3
    if(inst_name == "sll")
      func3 = "001";
    if(inst_name == "slt")
        func3 = "010";
    if(inst_name == "sltu")
        func3 = "011";
    if(inst_name == "xor")
        func3 = "100";
    if(inst_name == "srl")
      func3 = "101";
    if(inst_name == "sra")
        func3 = "101";
    if(inst_name == "or")
        func3 = "110";
    if(inst_name == "and")
        func3 = "111";
    return func7 + "_" + translate_register(rs2) + "_" + translate_register(rs1) + "_" + func3 + "_" + translate_register(rd) + "_" +  opcode;
  }
  else{
    throw string("Unrecognized Instruction");
  }
}


int main(int argc, char** argv){
  ifstream input_file(argv[1]);
  ofstream output_file(argv[2]);
  std::string inst_line;
  try{
      while (std::getline(input_file, inst_line))
      {
        output_file << assemble_instruction(inst_line) << "\n";
      }
    }
  catch(string& error_){
      cerr << error_;
    }
  input_file.close();
  output_file.close();
}
