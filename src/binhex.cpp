#include <fstream>
#include <string>
#include <regex>
#include <iostream>
#include <cstdlib>
#include <bitset>
#include <iomanip>


using namespace std;



int main(int argc, char** argv){
  string input_file_name = argv[1];
  string output_file_name = input_file_name + ".hex";
  ifstream input_file(input_file_name.c_str());
  ofstream output_file(output_file_name.c_str());
  output_file << "@00000000\n";
  string read_int;
  while(input_file >> read_int){
    int conv = strtol(read_int.c_str(),nullptr, 2);
   output_file << std::hex << std::setw(8) << setfill('0') << conv << " ";
 }
  input_file.close();
  output_file.close();
}
