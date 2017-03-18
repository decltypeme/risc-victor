#include <fstream>
#include <string>
#include <regex>
#include <iostream>
#include <cstdlib>
#include <bitset>

using namespace std;

#define INST_SIZE_B 4
vector<string> r_insts {"add", "sub", "sll", "slt", "sltu", "xor", "srl", "sra", "or", "and"};
vector<string> i_insts {"lb","lh","lw","lbu","lhu", "addi","slti","sltiu","xori","ori","andi","slli","srli","srai"};
//Handle JALR differently
inline int rand_int_range(int min_, int max_){
  return min_ + (rand() % (int)(max_ - min_ + 1));
}

string select_random_string(const vector<string>& in_list){
  return in_list[rand_int_range(0, in_list.size() - 1)];
}

string generate_random_register(bool write = false){
  int min_ = (write)?1:0;
  int max_ = 31;
  return to_string(rand_int_range(min_, max_));
}

string generate_rand_r_inst(int mem_index){
  string ret = select_random_string(r_insts);
  ret       += " ";
  ret       += generate_random_register();
  ret       += " , ";
  ret       += generate_random_register();
  ret       += " , ";
  ret       += generate_random_register(true);
  return ret;
}

string generate_rand_i_inst(int mem_index){
  string ret = select_random_string(i_insts);
  ret       += " ";
  ret       += generate_random_register();
  ret       += " , ";
  ret       += generate_random_register();
  ret       += " , ";
  ret       += to_string(rand_int_range(0, ((1<<12) - 1)));
  return ret;
}

string generate_rand_instruction(int mem_index){
  int inst_type_dice = rand_int_range(0, 1);
  switch(inst_type_dice){
    case 0: return generate_rand_r_inst(mem_index);
    case 1: return generate_rand_i_inst(mem_index);
  }
}

int generate_rand_prog(string prog_file_name, int prog_min_length, int prog_max_length){
  int prog_length = rand_int_range(prog_min_length, prog_max_length);
  ofstream output_file(prog_file_name);
  if(output_file.fail())
    throw string("Could not write to file: " + prog_file_name + "; Exiting now...\n");
  for(int mem_index = 0; mem_index < INST_SIZE_B * prog_length; mem_index += INST_SIZE_B){
    output_file << generate_rand_instruction(mem_index)  <<"\n";
  }
  output_file.close();
  return prog_length;
}



int main(int argc, char** argv){
  srand(42);
  int prog_min_length = 17;
  int prog_max_length = 42;
  int prog_count = stoi(argv[1]);
  string parent_dir(argv[2]);
  if(argc > 3)
    prog_min_length = stoi(argv[3]);
  if(argc > 4)
    prog_max_length = stoi(argv[4]);
  for(int prog_index = 1; prog_index <= prog_count; prog_index++){
    try{
      string mkdir_command = "mkdir -p " + parent_dir + "/rand_" + to_string(prog_index).c_str();
      const int dir_err = system(mkdir_command.c_str());
      if (-1 == dir_err)
      {
          printf("Error creating directory!\n");
          exit(1);
      }
      string prog_name = parent_dir + "/rand_" + to_string(prog_index).c_str() + "/rand_" + to_string(prog_index).c_str() + ".s";
      int prog_length = generate_rand_prog(prog_name, prog_min_length, prog_max_length);
      cout << "Pseudo-random program of length: " << prog_length << " generated. Saved at: " << prog_name << endl;
  }
  catch(string& err){
    cerr << err;
    exit(EXIT_FAILURE);
  }
  }
}
