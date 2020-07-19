# FunctionCalculator
Function Calculator used to evaluate mathematical expressions.

The following arithmetic operations are supported
* Addition
* Subtraction
* Multiplication
* Addition

Note:
* Some example formats :
```
    (9.25*((12.5+1.3)-5.8))/(0.125*((13.2+2.8)*2))
    
    ((2.80-4.3)*((((9.3-2.3))+7)/3.5))
```
* a(b+c) is considered as a*(b+c) Eg. 2.1(4 + 3.6) --> 2.1*(4 + 3.6)
* Any empty space is ignored
* Other deviations to the format is considered as syntax error
* All comments in the input text must begin with #. 
    Otherwise they are treated as expressions with invalid characters.
* Sample input file provided for reference

To build and run :

```
cmake -Bbuild -H.
cd build && make 
```

Create or update the input file and pass it with the executable argument:
```
./evaluator <input file path>
```

