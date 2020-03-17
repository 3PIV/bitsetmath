#include <bitset>

namespace srsa {
class RSAContext {
private:
  std::bitset<512> mPPrime;
  std::bitset<512> mQPrime;
  
public:
};
} // namespace srsa