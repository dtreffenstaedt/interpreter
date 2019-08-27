# interpreter
A fun little past time project:
an interperer with a creative name and C-like syntax.
any character recognised as a text character by the en_GB.UTF-8 locale is allowed as identifier.

No dependencies, uses c++ 17 standard library.


Has the dataypes:

- Real (represented by the keyword "real" or the UTF-8 character "ℝ")
- Integer (represented by the keyword "int" or the UTF-8 character "ℤ")
- Boolean (keyword "bool")
- String (keyword "String")
- Character (keyword "char")

Functions can have one of the Datatypes as return value, or void.

Has the classical mathematical operators, and ^ for power.

Currently thinking about how exactly to implement conditionals.
