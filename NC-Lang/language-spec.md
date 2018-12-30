# Nathan OS - The Programming Language
## NC (NathanC)
NathanC is a programming language for systems programming. There are no header files, and there are no objects per-se. It is primarily designed to be used in NathanOS.

## General Syntax
### Declarer Requirements Pattern
In NC, no matter what it is, every expression will look like this:
`*declarer* *requirements* ;`
The `declarer` is a short identifier that tells the compiler what it's looking at and helps to generate more helpful errors.
`requirements` is anything the `declarer` needs to complete its task. `Requirements` will be more specifically laid in the spec for each `declarer`. Note the semicolon at the end of the line. A semicolon will always be required at the end of each expression.

Newlines are always ignored, allowing for expressions that span multiple lines.

### Brackets
Brackets `()` are used to define a list of expressions. Normally when brackets are used in a `requirements` there will be very specific rules about them. 

### Identifiers
An identifier is a tag that will be used for naming things such as functions and variables. An identifier can have any character from a-z, as well as the upper case A-Z. Underscores are also allowed. Numbers 0-9 are allowed as well. Identifiers are case-sensitive.

### Comments
Comments are exactly like C/C++. Comments are just notes that are thrown away during compilation, and are purely for documentation purposes.
`//` is to make the rest of the line a comment.
`/*` is to begin a multiline comment.
`*/` is to end a multiline comment.
Single-line comments are the only place the compiler will use newline characters.

### Literals
#### Integers
Any number literal (e.g. 1234) can be resolved to any signed or unsigned integer type, with the compiler usually picking the most convienent datatype.
For example, consider this piece of code:
`var int32 myvar`
`set myvar 26`
This code will create a variable called `myvar` and set it to a value of `26`. `26` is an integer literal, and it will automatically be of type `int32` since `myvar` is type `int32`.
You can explicitly define the integer type using `:`. The `:` goes between the integer literal and the type. For example, `25:int16` is an `int16` with a value of 25.

#### Characters
To define a character as a literal, you must enclose the character in single quotes.
For example, `'g'` would be a `char` containing the letter g. Characters are encoded in ASCII, so in reality the actual data that would be contained by the `char` would be 103 and not g.

## Built-in Datatypes
`char` is an 8-bit datatype very similar to C's `char`. It is technically an integer, but it is the only datatype that can contain a character literal.

### Signed integers
`int8`: an 8-bit integer.
`int16`: a 16-bit integer.
`int32`: a 32-bit integer.
`int64`: a 64-bit integer.

### Unsigned integers
`uint8`: an 8-bit unsigned integer.
`uint16`: a 16-bit unsigned integer.
`uint32`: a 32-bit unsigned integer.
`uint64`: a 64-bit unsigned integer.

## Defining a function
The `declarer` to define a function is `func`.
There are 3 `requirements`. These requirements are the name of the function, the arguments of the function, and the body of the function. The syntax of the requirements is this:
`*name* (*arguments*) (*body*)`
Note that when a requirement is more than one thing, it is enclosed in brackets. This is so it's very clear to the compiler what is and isn't a requirement, for example this way the compiler doesn't mistake a second argument as the return type.

`Name` is the identifier so it can be referenced and called. The regular identifier rules apply.
`Arguments` is a list of data needed for the operation of the function. This must be purely `in` and `out` expressions.
`Body` is the code that is run when the function is called. It consists of any number of any type of expression, but must end with a `return` expression.

## Variables
### Defining a variable
In order to define a variable, you must use the `var` declarer.
The requirements go like this:
`*type* *name*`

`Type` is the type of data that the variable is.
`Name` is the identifier by which someone can reference the variable.

### Setting a variable
The `set` declarer must be used to define a variable.
The requirements are as follows:
`*variable* *value*`

`Variable` is the identifier of the variable you wish to set.
`Value` is the value of the variable being set.

## Creating a new datatype
This is where the "sort-of" object orientation comes in.
`type` is the declarer to create a datatype.
The requirements are this:
`*name* (*data*) (*functions*)`

`Name` is the identifier for the datatype.
`Data` is the list of data that the datatype holds. This must be purely `var` expressions.
`Functions` is the list of function declarations that run on the datatype. This must be purely `func` expressions.

Example:
`type Person`
`(`
`    var char first_initial;`
`    var char last_initial;`
`    var int32 age;`
`)`
`(`
`    func create () (`
`        set first_initial 'n';`
`        set last_initial 'd';`
`        set age 27;`
`    );`
`);`