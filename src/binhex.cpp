#include <fstream>
#include <string>
#include <regex>
#include <iostream>
#include <cstdlib>
#include <bitset>
#include <iomanip>
#include <climits>

using namespace std;



template <typename T>
T swap_endian(T u)
{
    static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");

    union
    {
        T u;
        unsigned char u8[sizeof(T)];
    } source, dest;

    source.u = u;

    for (size_t k = 0; k < sizeof(T); k++)
        dest.u8[k] = source.u8[sizeof(T) - k - 1];

    return dest.u;
}

int main(int argc, char** argv){
  string input_file_name = argv[1];
  string output_file_name = input_file_name + ".hex";
  ifstream input_file(input_file_name.c_str());
  ofstream output_file(output_file_name.c_str());
  string read_int;
  while(input_file >> read_int){
    int conv = strtol(read_int.c_str(),nullptr, 2);
    conv = swap_endian<uint32_t>(conv);
   output_file << std::hex << std::setw(8) << setfill('0') << conv << " ";
 }
  input_file.close();
  output_file.close();
}
