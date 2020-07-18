#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>

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
                std::cout<<"Invalid operator"<<std::endl;
    }
}

void evaluate(std::string exp)
{
    //std::cout<<exp<<std::endl;
    std::stack<float> numbers;
    std::stack<char> symbols;
    for (auto i = 0; i < exp.size(); i++)
    {
        //Identify numbers
        if (isdigit(exp[i])){
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
            numbers.push(stof(test));
            i--; 
        }
        //Identify symbols
        else if(exp[i] == '('){ 
			symbols.push(exp[i]); 
		}
        //If ')' is encountered evaluate the expression after the immediate previous '('
        else if(exp[i] == ')'){
            while(!symbols.empty() && symbols.top() != '(') 
			{ 
                char op = symbols.top();
				auto num1 = numbers.top();
				numbers.pop(); 				
				auto num2 = numbers.top(); 
                numbers.pop();
                auto res = operate(num2, num1, op); 
				numbers.push(res); 
                symbols.pop();
			} 	 
			if(!symbols.empty()){ 
			symbols.pop();
            } 
        } 
        //If the symbol is an operator add to the stack.
        else if(exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/'){
            symbols.push(exp[i]);
        }
        else
        {
            std::cout<<"Invalid character : "<<exp[i]<<std::endl;
            while(!symbols.empty()){
                symbols.pop();
            }
            while(!numbers.empty()){
                numbers.pop();
            }			
            continue;
        }
    }

        //Validate the final operation
        while(!symbols.empty()) 
			{ 
                char op = symbols.top();
				auto num1 = numbers.top();
				numbers.pop(); 				
				auto num2 = numbers.top(); 
                numbers.pop();
                auto res = operate(num2, num1, op); 
				numbers.push(res); 
                symbols.pop();
			}
    
            if(!numbers.empty()) 
			{
            std::cout<<"Output : "<<numbers.top()<<std::endl;
            numbers.pop();
            }
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
        evaluate(exp);
    }
    return 0;
}
