#include <bitsetmath.hpp>
#include <iostream>
#include <rsacontext.hpp>
namespace srsa {
RSAContext::RSAContext() {
  // n = p * q
  mModulus = mPPrime;
  bitsetMultiply<RSA_SIZE>(mModulus, mQPrime);

  // phi_n = (p - 1) * (q - 1)
  mPhiN = mPPrime;
  bitsetSubtract<RSA_SIZE>(mPhiN, std::bitset<RSA_SIZE>(1));
  std::bitset<RSA_SIZE> qTmp = mQPrime;
  bitsetSubtract<RSA_SIZE>(qTmp, std::bitset<RSA_SIZE>(1));
  bitsetMultiply<RSA_SIZE>(mPhiN, qTmp);

  // getCoPrime of PhiN
  mPubKey = getCoprime();

  // get private key
  // mPrivKey = getPrivateKey();
  mPrivKey = getInverse(mPubKey, mPhiN);
}

RSAContext::~RSAContext() {}
void RSAContext::encrypt(const std::string &anInput,
                         const std::string &anOutput) const {}

void RSAContext::decrypt(const std::string &anInput,
                         const std::string &anOutput) const {}

std::bitset<RSA_SIZE>
RSAContext::numEncrypt(unsigned long long int anNum) const {
  std::bitset<RSA_SIZE> asBS(anNum);
  bitsetEncrypt(asBS);
  return asBS;
}

void RSAContext::bitsetEncrypt(std::bitset<RSA_SIZE> &anBS) const {
  bitsetPowMod<RSA_SIZE>(anBS, mPubKey.to_ullong(), mModulus);
}

std::bitset<RSA_SIZE>
RSAContext::numDecrypt(unsigned long long int anNum) const {
  std::bitset<RSA_SIZE> asBS(anNum);
  bitsetDecrypt(asBS);
  return asBS;
}

void RSAContext::bitsetDecrypt(std::bitset<RSA_SIZE> &anBS) const {
  bitsetPowMod<RSA_SIZE>(anBS, mPrivKey.to_ullong(), mModulus);
}

void RSAContext::printContext() const {
  std::cout << "mPPrime:\n" << mPPrime << std::endl;
  std::cout << "mQPrime:\n" << mQPrime << std::endl;
  std::cout << "mN:\n" << mModulus << std::endl;
  std::cout << "mPhiN:\n" << mPhiN << std::endl;
  std::cout << "mE:\n" << mPubKey << std::endl;
  std::cout << "mPrivKey:\n" << mPrivKey << std::endl;
}

inline std::bitset<RSA_SIZE> RSAContext::egcd(std::bitset<RSA_SIZE> a,
                                              std::bitset<RSA_SIZE> b) {
  std::bitset<RSA_SIZE> temp;
  while (true) {
    temp = a;
    bitsetModulo<RSA_SIZE>(temp, b);
    if (temp.none()) {
      return b;
    }
    a = b;
    b = temp;
  }
}

inline std::bitset<RSA_SIZE> RSAContext::getCoprime() {
  std::bitset<RSA_SIZE> e(2);
  while (bitsetLt<RSA_SIZE>(e, mPhiN)) {
    if (egcd(e, mPhiN) == std::bitset<RSA_SIZE>(1)) {
      break;
    }
    bitsetAdd<RSA_SIZE>(e, std::bitset<RSA_SIZE>(1));
  }
  return e;
}

inline std::bitset<RSA_SIZE> RSAContext::getPrivateKey() {
  std::bitset<RSA_SIZE> totient(mPhiN);
  bitsetMultiply<RSA_SIZE>(totient, privKeyConst);
  bitsetAdd<RSA_SIZE>(totient, std::bitset<RSA_SIZE>(1));
  std::bitset<RSA_SIZE> remainder(0);
  bitsetDivide<RSA_SIZE>(totient, mPubKey, totient, remainder);
  return totient;
}

inline std::bitset<RSA_SIZE> RSAContext::getInverse(std::bitset<RSA_SIZE> u,
                                                    std::bitset<RSA_SIZE> v) {
  std::bitset<RSA_SIZE> inv, u1(1), u3(u), v1(0), v3(v), t1, t3, q;
  long long int iter;
  while (v3 != std::bitset<RSA_SIZE>(0)) {
    bitsetDivide<RSA_SIZE>(u3, v3, q, t3);
    bitsetMultiply<RSA_SIZE>(q, v1);
    bitsetAdd<RSA_SIZE>(q, u1);
    t1 = q;
    u1 = v1;
    v1 = t1;
    u3 = v3;
    v3 = t3;
    iter = -iter;
  }
  if (u3 != std::bitset<RSA_SIZE>(1)) {
    return std::bitset<RSA_SIZE>(0);
  }
  if (iter < 0) {
    inv = v;
    bitsetSubtract<RSA_SIZE>(inv, u1);
  } else {
    inv = u1;
  }
  return inv;
}
} // namespace srsa