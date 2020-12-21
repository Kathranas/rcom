## RCOM -> My personal library code

### Philosophy
The idea is to have small simple lightweight classes.
These improve on C code by guarding internal state without becoming too bloated as C++ often does.
Additional functionality should be provided by helper functions.
Simple objects can be used as building blocks for more complicated objects, although I don't reccomend inheritance in all cases.

### rcom::Array
Array is a lightweight wrapper around a C-array which provides bounds checking.

### rcom::ArrayPtr
ArrayPtr is a pointer to an array.
In C an array frequently decays into a pointer losing size information.
ArrayPtr retains this size information and has bounds checking.

Q: Why not use an std::vector?
A: std::vector does too much. It allocates memory, does raii, has too many member functions,
cannot be used to refer to a staticly allocated array.

Q: Why not use std::array or rcom::array?
A: Array wrappers are templated on the size of the array.
This means that any function must specify the size of the array in advance or use a template function.
It's wasteful to generate each of these functions and inflexible to be restristed to arrays of a predetermined size.
They also do not represent dynamicly allocated arrays returned from malloc/new.

ArrayPtr is similar in spirit to the new std::array_view and std::span.
Sometimes you just want a range of contigious elements and you don't care about the details such as who allocated them.

Q: What about raii?
A: ArrayPtr is a simple object rather like C-pointer, simpicity is the philosophy of this library.
Any of the types here can be extended to with raii & ownership symantics.
For example UniqueArrayPtr and SharedArrayPtr.

### rcom::DynamicArray
DynamicArray is an ArrayPtr-like implementation of the classic CS data structure.
Has counted logical size which is less than or equal to the overall capacity of the underlying array.
