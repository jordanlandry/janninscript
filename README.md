# JanninScript

JanninScript is a programming language which compiles into C++

## How it works

The compiler works by first adding some basic functions to a build.cpp file.
For example here is a simplified version of the print function

```
void print(string message) {
    cout << message << endl;
}
```

Then when you run the `print("Hello, World")` function, it runs the previously defined function.

The compiler reads through your .jannin file and searches for keywords, such as `var`, to then translate that into C++

JanninScript
`var i = 10;`
C++
`double i = 10;`

With just adding this variable system, we can already create tons of functionality. Since it copies everything you type, C++ code is valid in JanninScript. This means that for loops are implemented just replacing int, with var

```
for (var i = 0; i < 10; i++) {
    print(i);
}
```

## Arrays

Technically there are no arrays in JanninScript, instead a custom class called Vector. This vector class contains methods such as push, sort, remove, and more. The way it works is when the compiler sees you are initializing a variable, it checks for the array syntax: `[]`
If you have values in there for example

```
var numbers = [1, 2, 3, 4, 5];
```

It will add this to the compiler

```
Vector numbers;
numbers.value = {1, 2, 3, 4, 5};
```

Everytime you access this variable, the compiler automatically adds `.value`

## Code Examples

```
var i = 10;
print(i);
```

```
var myNumbers = [9, 2, 4, 5, 6, 1 ,7, 8, 1, 23, 5, 15,6, 7, 8];
myNumbers.sort();
myNumbers.print();
```
