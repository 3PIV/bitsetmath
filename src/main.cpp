#include <bitsetmath.hpp>
#include <rsacontext.hpp>
#include <iostream>
#include <vector>

int main() {
  //assertTest();
  srsa::RSAContext rsac;
  rsac.printMems();
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
    std::string fileName = "";
    choice userSelect = choice::NONE;
    std::cout << "Option? ";
    std::cin >> selectOption;
    for (unsigned int i = 0; i < allowedOptions.size(); ++i) {
      if (selectOption == allowedOptions[i]) {
        userSelect = choice(i);
      }
    }
    if (userSelect == choice::ENC) {
      std::cout << "Name of file to encrypt? ";
      std::cin >> fileName;
    }
    if (userSelect == choice::DEC) {
      std::cout << "Name of file to decrypt?";
      std::cin >> fileName;
    }
    if (userSelect == choice::DONE) {
      break;
    }
  }
  exit(EXIT_SUCCESS);
}