#include <iostream>
#include <fstream>
#include <string>
#include <vector>

float operate(float num1, float num2, char op)
{
    switch(op)
    {
        case '+':
                return num1 + num2;
                break;
        case '-':
                return num1 - num2;
                break;
        case '*':
                return num1 * num2;
                break;
        case '/':
                return num1 / num2;
                break;
        default:
                return -1;
    }
    //return 0;
}

void evaluate(std::string exp)
{
    std::cout<<exp<<std::endl;
    std::vector<float> numbers;
    std::vector<char> symbols;
    for (auto i = 0; i < exp.size(); ++i)
    {
        //Identify numbers
        if (isdigit(exp[i]))
        {
            std::string test;
            /*After first occurance of a digit, iterate through the string 
            to get the complete floating point number by checking the subsequent characters.
            The end of a floating point number is identified by the next occurance of a symbol.*/
            while (i < exp.size())
            {
                if ((isdigit(exp[i]) || exp[i] == '.'))
                {
                    test.push_back(exp[i]);
                    i++;
                }
                else
                {
                    break;
                }
                
            }    
            numbers.push_back(stof(test));
            symbols.push_back(exp[i]);
        }
        //Identify symbols
        else
        {
            symbols.push_back(exp[i]);
        }
    }
    for(auto num:numbers)
    {
        std::cout<<num<<" ";
    }
        for(auto num:symbols)
    {
        std::cout<<num<<" ";
    }
    std::cout<<std::endl;

}
int main(int argc, char* argv[]) {

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

    for(auto exp:input)
    {
        //std::cout<<str<<std::endl;
        evaluate(exp);
    }
    return 0;
}
