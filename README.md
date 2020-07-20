# FunctionCalculator
Function Calculator used to evaluate mathematical expressions from an input text file.

The following arithmetic operations are supported:
* Addition
* Subtraction
* Multiplication
* Division

## Note:
* Some example formats :
```
    (9.25*((12.5+1.3)-5.8))/(0.125*((13.2+2.8)*2))
    
    ((2.80-4.3)*((((9.3-2.3))+7)/3.5))
```
* All negative numbers must be enclosed in braces. `Eg. 2*((-2)/1)`
* a(b+c) is considered as a*(b+c) `Eg. 2.1(4 + 3.6) --> 2.1*(4 + 3.6)`
* Any empty space is ignored
* Other deviations to the format is considered as syntax error
* All comments in the input text must begin with `#`
    Otherwise they are treated as expressions with invalid characters.
* Sample input file(input.txt) provided for reference

## To build and run :

```
mkdir build
cd build && cmake ..
make
```

Create a new input file or update the input file(input.txt) and pass the filepath as the executable's argument:
```
./evaluator <input file path>
```