#include <rsacontext.hpp>
#include <bitsetmath.hpp>
#include <iostream>
namespace srsa {
RSAContext::RSAContext() {
  // n = p * q
  mN = mPPrime;
  bitsetMultiply<RSA_SIZE>(mN, mQPrime);

  // phi_n = (p - 1) * (q - 1)
  mPhiN = mPPrime;
  bitsetSubtract<RSA_SIZE>(mPhiN, std::bitset<RSA_SIZE>(1));
  std::bitset<RSA_SIZE> qTmp = mQPrime;
  bitsetSubtract<RSA_SIZE>(qTmp, std::bitset<RSA_SIZE>(1));
  bitsetMultiply<RSA_SIZE>(mPhiN, qTmp);
}

RSAContext::~RSAContext() {}
void RSAContext::encrypt(const std::string &anInput,
                         const std::string &anOutput) const {}

void RSAContext::decrypt(const std::string &anInput,
                         const std::string &anOutput) const {}

void RSAContext::printMems() const{
  std::cout << "mPPrime:\n" << mPPrime << std::endl;
  std::cout << "mQPrime:\n" << mQPrime << std::endl;
  std::cout << "mN:\n" << mN << std::endl;
  std::cout << "mPhiN:\n" << mPhiN<< std::endl;
}
} // namespace srsa