#include <iostream>
#include <cctype>

int
main(void) {
  int c;

  while ((c = std::cin.get()) != EOF) {
    c = ::toupper(c);
    std::cout << (char) c;
  }

  return 0;
}
