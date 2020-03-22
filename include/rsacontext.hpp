#ifndef _RSACONTEXT_H_
#define _RSACONTEXT_H_
#include <bitset>

namespace srsa {
const unsigned int RSA_SIZE = 128;
const std::bitset<RSA_SIZE> privKeyConst(2);
class RSAContext {
private:
  std::bitset<RSA_SIZE> mPPrime = std::bitset<RSA_SIZE>(1500450271);
  std::bitset<RSA_SIZE> mQPrime = std::bitset<RSA_SIZE>(2860486313);
  std::bitset<RSA_SIZE> mModulus = std::bitset<RSA_SIZE>(0);
  std::bitset<RSA_SIZE> mPhiN = std::bitset<RSA_SIZE>(0);
  std::bitset<RSA_SIZE> mPubKey = std::bitset<RSA_SIZE>(0);
  std::bitset<RSA_SIZE> mPrivKey = std::bitset<RSA_SIZE>(0);

  inline std::bitset<RSA_SIZE> egcd(std::bitset<RSA_SIZE> a,
                                    std::bitset<RSA_SIZE> b);

  inline std::bitset<RSA_SIZE> getCoprime();

  inline std::bitset<RSA_SIZE> getPrivateKey();

  inline std::bitset<RSA_SIZE> getInverse(std::bitset<RSA_SIZE> a,
                                          std::bitset<RSA_SIZE> b);

public:
  explicit RSAContext();
  ~RSAContext();

  void encrypt(const std::string &anInput, const std::string &anOutput) const;
  void decrypt(const std::string &anInput, const std::string &anOutput) const;

  std::bitset<RSA_SIZE> numEncrypt(unsigned long long int anNum) const;
  void bitsetEncrypt(std::bitset<RSA_SIZE> &anBS) const;

  std::bitset<RSA_SIZE> numDecrypt(unsigned long long int anNum) const;
  void bitsetDecrypt(std::bitset<RSA_SIZE> &anBS) const;

  void printContext() const;
};
} // namespace srsa
#endif