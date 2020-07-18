#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main (int argc, char* argv[]) {

  std::ifstream ipfile (argv[1]);
  std::string line;
  std::vector<std::string> input;

  //Read lines from the input file into a vector that stores only the expressions
  if (ipfile.is_open())
  {
    while(std::getline(ipfile,line))
    {
        //Ignore comments
        if(line[0]!='#')
        {
            input.push_back(line);
        }    
    }
    ipfile.close();
  }
  else 
  std::cout << "Unable to open file"; 

    // for(auto str:input)
    // {
    //     std::cout<<str<<std::endl;
    // }

  return 0;
}