#include <fstream>
#include <string>
#include <regex>
#include <iostream>
#include <cstdlib>
#include <bitset>

using namespace std;

//Some Macros
#define MAP_INST_FUNC_N(INST,FUNC,FUNCN) if(inst_name == INST) FUNCN = FUNC;


regex R_TYPE_PATTERN(string("(add|sub|sll|slt|sltu|xor|srl|sra|or|and)\\s*([0-9]+)\\s*,\\s*([0-9]+)\\s*,\\s*([0-9]+)\\s*"));
regex I_TYPE_PATTERN(string("(jalr|lb|lh|lw|lbu|lhu|addi|slti|sltiu|xori|ori|andi|slli|srli|srai)\\s*([0-9]+)\\s*,\\s*([0-9]+)\\s*,\\s*([0-9]+)\\s*"));

bool disable_undescores = false;

string translate_immediate(string immediate, int bits_count){
  int reg = stoi(immediate);
  stringstream sstream;
  sstream << std::bitset<32>(reg);
  string reg_binary = sstream.str();
  return reg_binary.substr(32 - bits_count);
}

string translate_register(string register_number){
  return translate_immediate(register_number, 5);
}

string assemble_r_type(string in_inst){
  smatch sm;
  regex_match (in_inst,sm,R_TYPE_PATTERN);
  string inst_name  = sm[1];
  string rs2        = sm[2];
  string rs1        = sm[3];
  string rd         = sm[4];
  //Defaults
  string opcode = "0110011";
  string func7  = "0000000";
  string func3  = "000";
  //Func7
  MAP_INST_FUNC_N("sub","0100000",func7)
  MAP_INST_FUNC_N("sra","0100000",func7)
  //Func3
  MAP_INST_FUNC_N("sll","001",func3)
  MAP_INST_FUNC_N("slt","010",func3)
  MAP_INST_FUNC_N("sllu","011",func3)
  MAP_INST_FUNC_N("xor","100",func3)
  MAP_INST_FUNC_N("srl","101",func3)
  MAP_INST_FUNC_N("sla","101",func3)
  MAP_INST_FUNC_N("or","110",func3)
  MAP_INST_FUNC_N("and","111",func3)

  if(disable_undescores)
    return func7 + translate_register(rs2) + translate_register(rs1) + func3 + translate_register(rd) +  opcode;
  else
    return func7 + "_" + translate_register(rs2) + "_" + translate_register(rs1) + "_" + func3 + "_" + translate_register(rd) + "_" +  opcode;
}

string assemble_i_type(string in_inst){
  smatch sm;
  regex_match (in_inst,sm,I_TYPE_PATTERN);
  string inst_name  = sm[1];
  string rs1        = sm[2];
  string rd         = sm[3];
  string immediate = sm[4];
  //Defaults
  string opcode = "0010011";
  string func3  = "000";
  //Handle shift right arithmetic
  if(inst_name == "srai")
    immediate[1] = '1';
  //opcode
  MAP_INST_FUNC_N("jalr","1100111",opcode)
  MAP_INST_FUNC_N("lb","0000011",opcode)
  MAP_INST_FUNC_N("lh","0000011",opcode)
  MAP_INST_FUNC_N("lw","0000011",opcode)
  MAP_INST_FUNC_N("lbu","0000011",opcode)
  MAP_INST_FUNC_N("lhu","0000011",opcode)
  //Func3
  MAP_INST_FUNC_N("jalr","000",func3)
  MAP_INST_FUNC_N("lb","000",func3)
  MAP_INST_FUNC_N("lh","001",func3)
  MAP_INST_FUNC_N("lw","010",func3)
  MAP_INST_FUNC_N("lbu","100",func3)
  MAP_INST_FUNC_N("lhu","101",func3)
  //Arithmetic
  MAP_INST_FUNC_N("addi","000",func3)
  MAP_INST_FUNC_N("slti","010",func3)
  MAP_INST_FUNC_N("sltiu","011",func3)
  MAP_INST_FUNC_N("xori","100",func3)
  MAP_INST_FUNC_N("ori","110",func3)
  MAP_INST_FUNC_N("andi","111",func3)
  MAP_INST_FUNC_N("slli","001",func3)
  MAP_INST_FUNC_N("srli","101",func3)
  MAP_INST_FUNC_N("srai","101",func3)

  if(disable_undescores)
    return translate_immediate(immediate, 12) + translate_register(rs1) + func3 + translate_register(rd) +  opcode;
  else
    return translate_immediate(immediate, 12) + "_" + translate_register(rs1) + "_" + func3 + "_" + translate_register(rd) + "_" +  opcode;
}


string assemble_instruction(string in_inst){
  if(regex_match (in_inst,R_TYPE_PATTERN)){
    return assemble_r_type(in_inst);
  }
  else if(regex_match (in_inst,I_TYPE_PATTERN)){
    return assemble_i_type(in_inst);
  }
  else
    throw (string("Unrecognized Instruction: ") + in_inst + "; Exiting now...\n");
}


int main(int argc, char** argv){
  ifstream input_file(argv[1]);
  ofstream output_file(argv[2]);
  disable_undescores = (argc > 3 && string(argv[3]) == string("--disable-underscores"));
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
