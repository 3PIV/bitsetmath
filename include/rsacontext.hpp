#ifndef _RSACONTEXT_H_
#define _RSACONTEXT_H_
#include <bitset>

namespace srsa {
const unsigned int RSA_SIZE = 80;
class RSAContext {
private:
  std::bitset<RSA_SIZE> mPPrime = std::bitset<RSA_SIZE>(1500450271);
  std::bitset<RSA_SIZE> mQPrime = std::bitset<RSA_SIZE>(2860486313);
  std::bitset<RSA_SIZE> mN = std::bitset<RSA_SIZE>(0);
  std::bitset<RSA_SIZE> mPhiN = std::bitset<RSA_SIZE>(0);

public:
  explicit RSAContext();
  ~RSAContext();
  void encrypt(const std::string &anInput, const std::string &anOutput) const;
  void decrypt(const std::string &anInput, const std::string &anOutput) const;
  void printMems() const;
};
} // namespace srsa
#endif