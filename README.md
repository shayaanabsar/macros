# Macros

A programme that enables use of macros in languages that don't support it.

A macro can be thought of as a shorthand for a piece of code. They are particularly useful for pieces of code that are often repeated many times.

For example, a for loop in python that iterates 5 times looks like this:
``` python
for i in range(5):
```
Using a macro, _f_loop_, that is given the value _for i in range_, the same code can be shortened to
```python
f_loop(5):
```

The following is how the definition of a macro looks, where _shorthand_ is the shorthand of the code and _longhand_ is the full code:
```C++
#define shorthand longhand
```

Using the example of a python for loop, the macro definition would look like:
```C++
#define f_loop for i in range
```
Macros with parameters can be implemented in the following way:
```C++
#define square(x) x * x
```
This will replace all instances of _square_ followed by a number in brackets, _x_, with _x * x_.

__Macro shorthands should only consist of alphanumeric characters and underscores.__

To run the programme, install _make_, install the files for the programme, _cd_ into the correct directory and then run _make_ which will compile the programme for you. After this you can run _./macro input_file_.

After running the programme, the macro shorthands will be replaced with their longhands and the macro definitions will be removed to allow you too then compile/interpret your source code using the necessary interpreter/compiler(s) for the language.

