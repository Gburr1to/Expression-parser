# Expression Parser

A simple lexical scanner and recursive descent parser for validating mathematical and bitwise expressions.

## Features
- **Lexical Analysis**: Custom DFA-based scanner supporting integers, hex literals (`#[0-9a-fA-F]+`), variables, arithmetic, and bitwise operators.
- **Parsing**: Recursive descent parser for verifying expression syntax (operator precedence: primary > unary > multiplicative > additive > bitwise).
- **Validation**: Outputs `accept` for valid expressions and `reject` for syntax errors.

## Building the Application
To build the project using CMake:
```bash
mkdir build && cd build
cmake ..
make
```

## Running the Application
Run the executable by providing an input file containing the expression:
```bash
./parser <input_file>
```

## Documentation
Generate source code documentation using Doxygen:
```bash
doxygen Doxyfile
```
The output will be available in the `docs/` directory.
