# JanninScript

Welcome to JanninScript, a programming language created in C++ that compiles into C++.
JanninScript is an extremely basic language that allows you to write code that is easily translated into runnable C++ code.

### How I got the name

Years ago, when I was coming up with my GamerTag name, I experimented with modifying certain words, to see if I could come up with something cool. I eventually used the word "Ninja", and took the first syllable "nin", and put it after the second syllable "ja", to create Janin, and I added another n to have the spelling feel more correct, so we get Jannin.
I took this name and combined it with my go to programming language, JavaScript, to get JanninScript.

## Included functions and variables

Functions in JanninScript are written in C++ and added to the top of the build file allowing you to call them.

### Print

```
void print() {
    std::cout << "\n";
}

template<typename First, typename ... Strings>
void print(First arg, const Strings&... rest) {
    std::cout << std::boolalpha << arg  << " ";
    print(rest...);
}
```

If you are unfamiliar with C++, the print function may look confusing.
This function essentially just allows you to have unlimited parameters of any type, making it so you can run the following code

`print("Hello!", "I am Jordan.", "My birthday is on February", 6);`

The above code contains multiple parameters, with both strings and a number, not usually possible in a traditional C++ function.

### Math functions

| Function Name | Description                                           | Params                     | Return |
| ------------- | ----------------------------------------------------- | -------------------------- | ------ |
| floor         | Rounds decimal number down                            | x: Number                  | Number |
| ceil          | Rounds decimal number up                              | x: Number                  | Number |
| round         | Rounds decimal number                                 | x: Number                  | Number |
| round         | Rounds decimal number to specified number of decimals | x: Number, decimal: Number | Number |
| abs           | Returns the absolute value                            | x: Number                  | Number |
| square        | Returns the squared value                             | x: Number                  | Number |
| pow           | Returns x^y                                           | x: Number, y: Number       | Number |
| log           | Return log(x)                                         | x:Number                   | Number |

### Math values

| Name | Value                  |
| ---- | ---------------------- |
| PI   | 3.14159265358979323846 |
| E    | 2.71828182845904523536 |

## Syntax

_note semicolons are mandatory in JanninScript_

### Variables

In JanninScript to create a variable, use the var keyword.

JanninScript: `var myVariable = 10;`
C++ Translation: `auto myVariable = 10;`

In JanninScript, you do not need to add a type to a normal variable.

### Arrays

Arrays in JanninScript use a custom Vector Class and are typed.
To make an array in JanninScript, simply set the value of a var using `[ ]` syntax, note it must be typed using `:arrayType` after the variable name.

#### JanninScript:

```
var array1:number = [1, 2, 3];

var array2:number = [];
array2.push(1);
array2.push(2);
array2.push(3);
```

#### C++ Translation

```
VectorDouble array1;
array1.value = {1, 2, 3};

VectorDouble array2;
array2.push_back(1);
array2.push_back(2);
array2.push_back(3);
```

Since arrays are custom classes, they come with many useful functions such as `push`, `print`, `removeIndex`, and more.

See the Vector files in the classes folder for a full list of all the methods included in each class.

### Loops

Since C++ code is valid code in JanninScript, loops are written with the same syntax as C++, but you can switch `int` to `var` in for loops

#### JanninScript for loop

```
for (var i = 0; i < 10; i++) {
  print(i);
}
```

#### Translated in C++

```
for (int i = 0; i < 10; i++) {
  std::cout << i << std::endl;
}
```

#### JanninScript while loop

```
var j = 0;
while (j < 10) {
  print(j);
  j++;
}
```

#### Translated in C++

```
auto j = 0;
while (j < 10) {
    std::cout << j << std::endl;
    j++;
}
```

Note the compiler will actually use print, a function included in the build file, instead of cout.

## Getting Started

### Download

Before coding in JanninScript, please ensure you have the following:

- Text editor / IDE
- C++ compiler
- Git

1. Open the desired download directory
2. Paste the following command in your terminal `git clone https://github.com/jordanlandry/janninscript.git` -Alternatively, you can download and unzip the project by clicking Code, then Download ZIP.

3. Open the folder in your IDE of choice
4. Write your JanninScript code in build.jannin

### Compile

1. Compile and run Compiler.cpp. - This will create build.cpp with your compiled JanninScript code
2. Compile and run build.cpp - This will run your JanninScript code.

### Alternative

_Note_ I will be making an online compiler soon with text highlighting, so you don't have to download the code.
