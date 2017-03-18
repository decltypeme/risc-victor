#include <fstream>
#include <string>
#include <regex>
#include <iostream>
#include <cstdlib>
#include <bitset>

using namespace std;

#define BANK_OUT(BANK) BANK << inst_line.substr(0, 8) << "\n";inst_line = inst_line.substr(8);

void divide_file(ifstream& in_file, ofstream& bank3, ofstream& bank2, ofstream& bank1, ofstream& bank0){
  string inst_line;
  while (std::getline(in_file, inst_line))
  {
    BANK_OUT(bank3)
    BANK_OUT(bank2)
    BANK_OUT(bank1)
    BANK_OUT(bank0)
  }
}


int main(int argc, char** argv){
  ifstream input_file(argv[1]);
  ofstream output_banks[4];
  for(int i = 0; i < 4; i++){
    string bank_name = string(argv[1]) + string("_b") + to_string(i);
    output_banks[i].open(bank_name.c_str());
  }
  try{
      divide_file(input_file, output_banks[3], output_banks[2], output_banks[1], output_banks[0]);
    }
  catch(string& error_){
      cerr << error_;
    }
  input_file.close();
  for(int i = 0; i < 4; i++){
    output_banks[i].close();
  }
}
