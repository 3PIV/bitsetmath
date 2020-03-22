#include <bitsetmath.hpp>
#include <fstream>
#include <iostream>
#include <rsacontext.hpp>
#include <sstream>
#include <string>
#include <vector>

void bitmathTest();

int main() {
  //bitmathTest();
  srsa::RSAContext rsac;
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
    /// The user selected to encrypt
    if (userSelect == choice::ENC) {
      // Steps to encrypt:
      // 1) Get file name
      // 2) Create an encrypted.txt to place content in
      // 3) Go number by number in file's lines and encrypt
      //    3.a) Make sure we preserve new lines!
      std::cout << "Name of file to encrypt? ";
      std::cin >> fileName;

      std::ifstream infile(fileName, std::fstream::in);
      std::ofstream outfile(encryptFN);

      std::string inputline;
      while (std::getline(infile, inputline)) {
        unsigned long long innum;
        std::istringstream iss(inputline);
        bool notfirst = false;
        while (iss >> innum) {
          if (notfirst) {
            outfile << " ";
          }
          std::bitset<srsa::RSA_SIZE> enc = rsac.numEncrypt(innum);
          outfile << enc.to_ullong();
          notfirst = true;
        }
        outfile << std::endl;
      }
    }
    /// The user selected to decrypt
    else if (userSelect == choice::DEC) {
      // Steps to decrypt:
      // 1) Get file name
      // 2) Create an decrypted.txt to place content in
      // 3) Go number by number in file's lines and decrypt
      //    3.a) Make sure we preserve new lines!
      std::cout << "Name of file to decrypt? ";
      std::cin >> fileName;

      std::ifstream infile(fileName, std::fstream::in);
      std::ofstream outfile(decryptFN);

      std::string inputline;
      while (std::getline(infile, inputline)) {
        unsigned long long innum;
        std::istringstream iss(inputline);
        bool notfirst = false;
        while (iss >> innum) {
          if (notfirst) {
            outfile << " ";
          }
          std::bitset<srsa::RSA_SIZE> dec = rsac.numDecrypt(innum);
          outfile << dec.to_ullong();
          notfirst = true;
        }
        outfile << std::endl;
      }
    }
    /// The user selected done
    else if (userSelect == choice::DONE) {
      break;
    }
  }
  exit(EXIT_SUCCESS);
}

void bitmathTest() {
  // ensure 64 bit
  assert(sizeof(unsigned long long) == 8);

  // test sub
  std::bitset<512> test0x(4);
  std::bitset<512> test0y(3);
  bitsetSubtract<512>(test0x, test0y);
  assert(test0x.to_ullong() == 1);

  // test add
  std::bitset<512> test1x(2);
  std::bitset<512> test1y(3);
  bitsetAdd<512>(test1x, test1y);
  assert(test1x.to_ullong() == 5);

  // test mul
  std::bitset<512> test2x(2);
  std::bitset<512> test2y(3);
  bitsetMultiply<512>(test2x, test2y);
  assert(test2x.to_ullong() == 6);

  // test compares
  std::bitset<512> test3x(2);
  std::bitset<512> test3y(3);
  assert(bitsetLt<512>(test3x, test3y));
  assert(bitsetLtEq<512>(test3x, test3y));
  assert(bitsetGt<512>(test3y, test3x));
  assert(bitsetGtEq<512>(test3y, test3x));

  std::bitset<512> test3w(3);
  std::bitset<512> test3z(3);
  assert(!bitsetLt<512>(test3w, test3z));
  assert(bitsetLtEq<512>(test3w, test3z));
  assert(!bitsetGt<512>(test3z, test3w));
  assert(bitsetGtEq<512>(test3z, test3w));

  // test divide
  std::bitset<512> test4d(4);
  std::bitset<512> test4z(2);
  std::bitset<512> test4q(0);
  std::bitset<512> test4r(0);
  bitsetDivide<512>(test4d, test4z, test4q, test4r);
  assert(test4q.to_ullong() == 2);
  assert(test4r.to_ullong() == 0);

  test4d = std::bitset<512>(5);
  test4z = std::bitset<512>(3);
  test4q = std::bitset<512>(0);
  test4r = std::bitset<512>(0);
  bitsetDivide<512>(test4d, test4z, test4q, test4r);
  assert(test4q.to_ullong() == 1);
  assert(test4r.to_ullong() == 2);

  // test modulo
  std::bitset<512> test5x(5);
  std::bitset<512> test5y(3);
  bitsetModulo<512>(test5x, test5y);
  assert(test5x.to_ullong() == 2);

  // test pow
  std::bitset<512> test6x(5);
  std::bitset<512> test6y(3);
  bitsetPow<512>(test6x, 3);
  bitsetPow<512>(test6y, 5);
  assert(test6x.to_ullong() == 125);
  assert(test6y.to_ullong() == 243);
}