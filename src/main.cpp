#include <bitsetmath.hpp>
#include <iostream>
#include <vector>

int main() {
  assertTest();
  const std::string encryptFN = "encrypted.txt";
  const std::string decryptFN = "decrypted.txt";
  std::vector<std::string> allowedOptions{"encrypt", "decrypt", "done"};
  enum choice {
    ENC = 0,
    DEC = 1,
    DONE = 2,
    NONE = 3,
  };

  std::string selectOption = "";
  while (true) {
    choice userSelect = choice::NONE;
    std::cout << "Option? ";
    std::cin >> selectOption;
    std::cout << std::endl;
    for (unsigned int i = 0; i < allowedOptions.size(); ++i) {
      if (selectOption == allowedOptions[i]) {
        userSelect = choice(i);
      }
    }
    if (userSelect == choice::ENC) {
      std::cout << "Name of file to encrypt?" << std::endl;
    }
    if (userSelect == choice::DEC) {
      std::cout << "Name of file to decrypt?" << std::endl;
    }
    if (userSelect == choice::DONE) {
      break;
    }
  }
  /*
  std::bitset<512> bigNum(18446744073709551615ULL);
  std::bitset<512> anotherOne(3);
  std::cout << bigNum.to_string() << std::endl;
  bitsetMultiply<512>(bigNum, anotherOne);
  std::cout << bigNum.to_string() << std::endl;
  std::cout << bigNum.to_ullong() << std::endl;*/
  exit(EXIT_SUCCESS);
}