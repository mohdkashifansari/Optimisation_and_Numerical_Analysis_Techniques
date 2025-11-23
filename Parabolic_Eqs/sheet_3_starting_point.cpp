// This code reads in three numbers from the user as
// command line arguments and interpretes them as an singed integer and an
// unsigned type size_t and a floating point type double

// Include the header files for standard input/output routines, here std::cout.
#include <iostream>
#include <sstream>

// The main function is obligatory is where the program starts. Its return is
// of type int but can be omitted. The first arguments gives the number of
// of command line arguments and the second is a two dimensional array, which
// contains the arguments.
int main(int argc, char **argv) {
  // Check if an argument was passed to the program.
  // Note that the first argument is always the name of the program.
  // If no argument was entered in the console, we abort the program.
  if (argc < 4) exit(1);

  // Interprete the character array argv[1] as integer.
  int a;
  std::istringstream(argv[1]) >> a;

  size_t b;
  std::istringstream(argv[2]) >> b;

  double c;
  std::istringstream(argv[3]) >> c;

  // Output a to the console and end the current line.
  std::cout << "a = " << a << ", b = " << b << ", c = " << c << std::endl;

  return 0;
}
