#include <iostream>
#include <cstdlib>
#include <string>

int add(int a, int b) {
  return a - b;
}

void runTests() {
  bool success = true;

  if (add(2, 3) != 5) {
    std::cerr << "Test failed: add(2, 3) should be 5." << std::endl;
    success = false;
  }
  if (add(-1, 1) != 0) {
    std::cerr << "Test failed: add(-1, 1) should be 0." << std::endl;
    success = false;
  }

  if (success) {
    std::cout << "All tests passed." << std::endl;
  } else {
    std::cerr << "Some tests failed." << std::endl;
    exit(1);
  }
}

int main(int argc, char* argv[]) {
  if (argc > 1 && std::string(argv[1]) == "test") {
    runTests();
    return 0;
  }
  std::cout << "2 + 3 = " << add(2, 3) << std::endl;
  return 0;
}
