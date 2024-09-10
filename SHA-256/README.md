# SHA-256 Hashing Program

This program is a simple driver code that demonstrates the use of a custom `SHA256` hashing function. It takes a predefined string message ("abc") and computes its SHA-256 hash.

## Features

- Converts a string message to a `uint8_t` byte array.
- Uses the `SHA256` function to compute the hash.
- Prints the resulting SHA-256 hash in hexadecimal format.

## File Structure

- `main.c`: The driver code that demonstrates how to hash a message using SHA-256.
- `SHA256.h`: The header file containing the declaration of the `SHA256` function.

## Requirements

To compile and run this code, you need:

- A C compiler (e.g., GCC).
- The `SHA256.h` header file, which defines the `SHA256` function used in this program.

## Compilation

To compile the program, use the following command (assuming you have `SHA256.h` and the corresponding source file `SHA256.c` in the same directory):

## Customization

To compute hash of different data you can supply your data to the function in a byte array format or change the value of messsage variable.


```bash
gcc -o sha256_example SHA256.c
./sha256_example
