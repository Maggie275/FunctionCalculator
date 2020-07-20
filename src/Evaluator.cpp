#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <algorithm>

bool isNegative = false;

enum eTokenType
{
    TYPE_DIGIT = 0,
    TYPE_OPEN_BRACE,
    TYPE_CLOSE_BRACE,
    TYPE_OPERATOR,
    TYPE_NONE = 255
};

int checkPrecedence(char op)
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

void apply(std::stack<float> &digits, std::stack<char> &operators)
{
    char op = operators.top();
    if (!operators.empty())
    {
        operators.pop();
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
    std::stack<float> digits;
    std::stack<char> operators;
    eTokenType prevTok = TYPE_NONE;

    //Check for braces mismatch
    if (std::count(exp.begin(), exp.end(), '(') == std::count(exp.begin(), exp.end(), ')'))
    {
        for (auto i = 0; i < exp.size(); i++)
        {
            //Identify numbers
            if (isdigit(exp[i]))
            {
                // eg. (23.56 45.6) Is treated as a syntax error
                if (prevTok == TYPE_DIGIT)
                {
                    std::cout << "Syntax Error : Missing operator" << std::endl;
                    return;
                }
                // eg. (2+3)2 --> is treated as (2+3)*2
                else if (prevTok == TYPE_CLOSE_BRACE)
                {
                    operators.push('*');
                }

                std::string strDigit; // temporary string to hold parsed floating numbers

                /*After first occurance of a digit, iterate through the string 
                to get the complete floating point number by checking the subsequent characters.
                The end of a floating point number is identified by the next occurance of a symbol.*/
                while (i < exp.size() && (isdigit(exp[i]) || exp[i] == '.'))
                {
                    strDigit.push_back(exp[i]);
                    i++;
                }

                std::string::size_type sz;
                float digit = stof(strDigit, &sz);

                // eg. (45 + 67.4556.34) is treated as a syntax error.
                if (sz != strDigit.size())
                {
                    std::cout << "Syntax Error : Invalid floating point number" << std::endl;
                    return;
                }

                //Check for a negative number
                if (isNegative && exp[i] == ')')
                {
                    digits.push(-digit);
                    isNegative = false;
                }
                else
                {
                    digits.push(digit);
                    i--;
                }
                prevTok = TYPE_DIGIT;
            }
            //Identify symbols
            else if (exp[i] == '(')
            {
                //Check for negative numbers
                if (exp[i + 1] == '-' && std::isdigit(exp[i + 2]))
                {
                    isNegative = true;
                    i++;
                    continue;
                }
                //2(2+3) --> is treated as 2*(2+3)
                if (prevTok == TYPE_DIGIT)
                {
                    operators.push('*');
                }
                operators.push(exp[i]);
                prevTok = TYPE_OPEN_BRACE;
            }
            else if (exp[i] == ')')
            {
                // eg. (2+ )+5 is treated as a syntax error
                if (prevTok == TYPE_OPERATOR)
                {
                    std::cout << "Syntax Error : Missing operand/Extra operator identified" << std::endl;
                    return;
                }
                //If ')' is encountered evaluate the expression after the immediate previous '('
                while (!operators.empty() && operators.top() != '(')
                {
                    apply(digits, operators);
                }
                //Remove the previous corresponding '('
                if (!operators.empty())
                {
                    operators.pop();
                }
                prevTok = TYPE_CLOSE_BRACE;
            }
            else if (validateOperator(exp[i]))
            {
                // eg. (2+ *3) and (*2+3) is treated as a syntax error
                if ((prevTok != TYPE_DIGIT) && (prevTok != TYPE_CLOSE_BRACE))
                {
                    std::cout << "Syntax Error : Missing operand/Extra operator identified" << std::endl;
                    return;
                }
                /*If the symbol is an operator, check for precedence of previous operator in operators stack
                and evaluate the expression in the current brace.*/
                while (!operators.empty() && checkPrecedence(operators.top()) >= checkPrecedence(exp[i]))
                {
                    apply(digits, operators);
                }
                operators.push(exp[i]);
                prevTok = TYPE_OPERATOR;
            }
            //Ignore empty spaces
            else if (std::isspace(exp[i]))
            {
                continue;
            }
            else
            {
                std::cout << "Syntax Error : Invalid character" << std::endl;
                return;
            }
        }
        //Evaluate the final expression.
        while (!operators.empty())
        {
            apply(digits, operators);
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
                    evaluate(line);
                }
            }
        }
        ipfile.close();
    }
    else
        std::cout << "Unable to open file" << std::endl;
    return 0;
}
