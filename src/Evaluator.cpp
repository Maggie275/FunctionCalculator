#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

enum TokenType
{
    eTYPE_DIGIT = 0,
    eTYPE_OPEN_BRACE,
    eTYPE_CLOSE_BRACE,
    eTYPE_OPERATOR,
    eTYPE_NONE = 255
};

int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

bool validateOperator(char op)
{
    return (op == '+' || op == '-' || op == '*' || op == '/') ? true : false;
}

float operate(float num1, float num2, char op)
{
    switch (op)
    {
    case '+':
        return num1 + num2;
    case '-':
        return num1 - num2;
    case '*':
        return num1 * num2;
    case '/':
        return num1 / num2;
    default:
        std::cout << "Invalid operator" << std::endl;
        return 0;
    }
}

void apply(std::stack<float> &digits, std::stack<char> &symbols)
{
    char op = symbols.top();
    if (!symbols.empty())
    {
        symbols.pop();
    }
    float num1 = digits.top();
    if (!digits.empty())
    {
        digits.pop();
    }
    float num2 = digits.top();
    if (!digits.empty())
    {
        digits.pop();
    }
    digits.push(operate(num2, num1, op));
}

void evaluate(const std::string &exp)
{
    //std::cout << exp << std::endl;
    std::stack<float> digits;
    std::stack<char> symbols;
    TokenType prevTok = eTYPE_NONE;

    if (std::count(exp.begin(), exp.end(), '(') == std::count(exp.begin(), exp.end(), ')'))
    {
        for (auto i = 0; i < exp.size(); i++)
        {
            //Identify numbers
            if (isdigit(exp[i]))
            {
                // eg. (2+3)2 --> is treated as (2+3)*2
                if (prevTok == eTYPE_CLOSE_BRACE)
                {
                    symbols.push('*');
                }
                // eg. (23.56 45.6) Is treated as a syntax error
                else if (prevTok == eTYPE_DIGIT)
                {
                    std::cout << "Syntax Error : Missing operator" << std::endl;
                    return;
                }

                std::string digit_str;

                /*After first occurance of a digit, iterate through the string 
                to get the complete floating point number by checking the subsequent characters.
                The end of a floating point number is identified by the next occurance of a symbol.*/
                while (i < exp.size())
                {
                    if ((isdigit(exp[i]) || exp[i] == '.'))
                    {
                        digit_str.push_back(exp[i]);
                        i++;
                    }
                    else
                    {
                        break;
                    }
                }

                std::string::size_type sz;
                digits.push(stof(digit_str, &sz));

                // eg. (45 + 67.4556.34) is treated as a syntax error.
                if (sz != digit_str.size())
                {
                    std::cout << "Syntax Error : Invalid floating point number" << std::endl;
                    return;
                }

                i--;
                prevTok = eTYPE_DIGIT;
            }
            //Identify symbols
            else if (exp[i] == '(')
            {
                //2(2+3) --> is treated as 2*(2+3)
                if (prevTok == eTYPE_DIGIT)
                {
                    symbols.push('*');
                }
                symbols.push(exp[i]);
                prevTok = eTYPE_OPEN_BRACE;
            }
            else if (exp[i] == ')')
            {
                // eg. (2+ )+5 is treated as a syntax error
                if (prevTok == eTYPE_OPERATOR)
                {
                    std::cout << "Syntax Error : Missing operand/Extra operator identified" << std::endl;
                    return;
                }
                //If ')' is encountered evaluate the expression after the immediate previous '('
                while (!symbols.empty() && symbols.top() != '(')
                {
                    apply(digits, symbols);
                }
                //Remove the previous corresponding '('
                if (!symbols.empty())
                {
                    symbols.pop();
                }
                prevTok = eTYPE_CLOSE_BRACE;
            }
            //Ignore empty spaces
            else if (std::isspace(exp[i]))
            {
                continue;
            }
            else if (validateOperator(exp[i]))
            {
                // eg. (2+ *3) is treated as a syntax error
                if ((prevTok != eTYPE_DIGIT) && (prevTok != eTYPE_CLOSE_BRACE))
                {
                    std::cout << "Syntax Error : Missing operand/Extra operator identified" << std::endl;
                    return;
                }

                /*If the symbol is an operator, check for precedence of previous operator in symbols stack
                and evaluate the expression in the current brace.*/
                while (!symbols.empty() && precedence(symbols.top()) >= precedence(exp[i]))
                {
                    apply(digits, symbols);
                }
                symbols.push(exp[i]);
                prevTok = eTYPE_OPERATOR;
            }
            else
            {
                std::cout << "Syntax Error : Invalid character" << std::endl;
                return;
            }
        }
        //Evaluate the final expression.
        while (!symbols.empty())
        {
            apply(digits, symbols);
        }

        if (!digits.empty())
        {
            std::cout << digits.top() << std::endl;
            digits.pop();
        }
    }
    else
    {
        std::cout << "Syntax error : Mismatching Braces" << std::endl;
    }
}
int main(int argc, char *argv[])
{

    std::ifstream ipfile(argv[1], std::ifstream::in);
    std::string line;
    std::vector<std::string> input;

    //Read lines from the input file into a vector that stores only the expressions
    if (ipfile.is_open())
    {
        if (ipfile.peek() == std::ifstream::traits_type::eof())
        {
            std::cout << "Input file is empty" << std::endl;
        }
        else
        {
            while (std::getline(ipfile, line))
            {
                //Ignore comments
                if (line[0] != '#')
                {
                    input.push_back(line);
                }
            }
            for (const auto &exp : input)
            {
                evaluate(exp);
            }
        }
        ipfile.close();
    }
    else
        std::cout << "Unable to open file" << std::endl;
    return 0;
}
