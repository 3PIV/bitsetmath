/**
 * @file bitsetmath.hpp
 * @author Paul Preston Provins IV (pprovins@vols.utk.edu)
 * @brief A simple math library to extend std::bitset with
 * @date 2020-03-17
 */
#include <bitset>
#include <stdexcept>

/**
 * @brief Adds two bits together, returns bool indicating if set or not
 *
 * @param anBit a bit to add
 * @param anotherBit another bit to add
 * @param anCarry if the add overflowed
 * @return true a set bit
 * @return false an unset bit
 */
inline bool addBits(bool anBit, bool anotherBit, bool &anCarry) {
  bool sum = (anBit ^ anotherBit) ^ anCarry;
  anCarry =
      (anBit && anotherBit) || (anBit && anCarry) || (anotherBit && anCarry);
  return sum;
}

/**
 * @brief subtract a bit from a bit
 *
 * @param minuend the bit subtracted from
 * @param subtrahend the bit to subtract
 * @param borrow did it underflow
 * @return true a set bit
 * @return false an unset bit
 */
inline bool subtractBits(bool minuend, bool subtrahend, bool &borrow) {
  bool diff;
  if (borrow) {
    diff = !(minuend ^ subtrahend);
    borrow = !minuend || (minuend && subtrahend);
  } else {
    diff = minuend ^ subtrahend;
    borrow = !minuend && subtrahend;
  }
  return diff;
}

/**
 * @brief is bitset less than or equal to another bitset
 *
 * @tparam N length of bitset
 * @param leftHandSide left hand side of inequality
 * @param rightHandSide right hand side of inequality
 * @return true LHS is less than or equal to RHS
 * @return false LHS is greater than RHS
 */
template <unsigned int N>
inline bool bitsetLtEq(const std::bitset<N> &leftHandSide,
                       const std::bitset<N> &rightHandSide) {
  for (int index = N - 1; index >= 0; index--) {
    if (leftHandSide[index] && !rightHandSide[index]) {
      return false;
    }
    if (!leftHandSide[index] && rightHandSide[index]) {
      return true;
    }
  }
  return true;
}

/**
 * @brief is bitset less than another bitset
 *
 * @tparam N length of bitset
 * @param leftHandSide left hand side of inequality
 * @param rightHandSide right hand side of inequality
 * @return true LHS is less than RHS
 * @return false LHS is greater than or equal to RHS
 */
template <unsigned int N>
inline bool bitsetLt(const std::bitset<N> &leftHandSide,
                     const std::bitset<N> &rightHandSide) {
  for (int index = N - 1; index >= 0; index--) {
    if (leftHandSide[index] && !rightHandSide[index]) {
      return false;
    }
    if (!leftHandSide[index] && rightHandSide[index]) {
      return true;
    }
  }
  return false;
}

/**
 * @brief is bitset greater than or equal to another bitset
 *
 * @tparam N length of bitset
 * @param leftHandSide left hand side of inequality
 * @param rightHandSide right hand side of inequality
 * @return true LHS is greater than or equal to RHS
 * @return false LHS is less than RHS
 */
template <unsigned int N>
inline bool bitsetGtEq(const std::bitset<N> &leftHandSide,
                       const std::bitset<N> &rightHandSide) {
  return !bitsetLt<N>(leftHandSide, rightHandSide);
}

/**
 * @brief is bitset greater than another bitset
 *
 * @tparam N length of bitset
 * @param leftHandSide left hand side of inequality
 * @param rightHandSide right hand side of inequality
 * @return true LHS is greater than RHS
 * @return false LHS is less than or equal to RHS
 */
template <unsigned int N>
inline bool bitsetGt(const std::bitset<N> &leftHandSide,
                     const std::bitset<N> &rightHandSide) {
  return !bitsetLtEq<N>(leftHandSide, rightHandSide);
}

/**
 * @brief add two bitsets together and store sum in first argument
 *
 * @tparam N length of bitset
 * @param termOne amount one, and sum
 * @param termTwo amount two
 */
template <unsigned int N>
inline void bitsetAdd(std::bitset<N> &termOne, const std::bitset<N> &termTwo) {
  bool carry = false;
  for (int i = 0; i < N; i++) {
    termOne[i] = addBits(termOne[i], termTwo[i], carry);
  }
}

/**
 * @brief subtract a bitset termTwo from termOne and store remainder in first
 * termOne
 *
 * @tparam N length of bitset
 * @param termOne amount one, and remainder
 * @param termTwo amount two
 */
template <unsigned int N>
inline void bitsetSubtract(std::bitset<N> &minuend,
                           const std::bitset<N> &subtrahend) {
  bool borrow = false;
  for (int i = 0; i < N; i++) {
    if (borrow) {
      if (minuend[i]) {
        minuend[i] = subtrahend[i];
        borrow = subtrahend[i];
      } else {
        minuend[i] = !subtrahend[i];
        borrow = true;
      }
    } else {
      if (minuend[i]) {
        minuend[i] = !subtrahend[i];
        borrow = false;
      } else {
        minuend[i] = subtrahend[i];
        borrow = subtrahend[i];
      }
    }
  }
}

/**
 * @brief multiply two bitsets together and store product in term one
 *
 * @tparam N length of bitset
 * @param term first number in multiply
 * @param multiplier second number in multiply
 */
template <unsigned int N>
inline void bitsetMultiply(std::bitset<N> &term,
                           const std::bitset<N> &multiplier) {
  std::bitset<N> tmp = term;
  term.reset();
  // we want to minimize the number of times we shift and add
  if (tmp.count() < multiplier.count()) {
    for (int i = 0; i < N; i++)
      if (tmp[i]) {
        bitsetAdd<N>(term, multiplier << i);
      }
  } else {
    for (int i = 0; i < N; i++) {
      if (multiplier[i]) {
        bitsetAdd<N>(term, tmp << i);
      }
    }
  }
}

/**
 * @brief divide a bitset by a bitset and store the remainder and quotient
 *
 * @tparam N length of bitsets
 * @param dividend bitset being divided
 * @param divisor bitset that is used as divisor
 * @param quotient bitset remaining parts
 * @param remainder bitset quotient parts
 */
template <unsigned int N>
inline void bitsetDivide(std::bitset<N> dividend, std::bitset<N> divisor,
                         std::bitset<N> &quotient, std::bitset<N> &remainder) {
  if (divisor.none()) {
    throw std::runtime_error("bitsetmath::bitsetDivide(): Division by Zero!");
  }
  quotient.reset();
  remainder.reset();
  if (dividend.none()) {
    return;
  }
  if (dividend == divisor) {
    quotient[0] = 1;
    return;
  }
  remainder = dividend;
  if (bitsetLt<N>(dividend, divisor)) {
    return;
  }

  // count significant digits in divisor and dividend
  unsigned int sigDividend;
  for (int i = N - 1; i >= 0; i--) {
    sigDividend = i;
    if (dividend[i]) {
      break;
    }
  }
  unsigned int sigDivisor;
  for (int i = N - 1; i >= 0; i--) {
    sigDivisor = i;
    if (divisor[i])
      break;
  }
  // align the divisor with the dividend
  unsigned int n = (sigDividend - sigDivisor);
  divisor <<= n;
  // set loop comparator
  n += 1;
  // perform long division:
  // Step 1) Shift
  // Step 2) Subtract
  while (n--) {
    // shift the quotient to the left
    if (bitsetLtEq<N>(divisor, remainder)) {
      // add a new digit to quotient
      quotient[n] = true;
      bitsetSubtract<N>(remainder, divisor);
    }
    // shift the divisor to the right
    divisor >>= 1;
  }
}

/**
 * @brief perform modulous arithmetic on two bitsets
 * 
 * @tparam N length of bitset
 * @param dividend number being modulod, also stores modulo
 * @param modulo the number to modulo
 */
template <unsigned int N>
inline void bitsetModulo(std::bitset<N> &dividend, std::bitset<N> modulo) {
  std::bitset<N> quotient;
  std::bitset<N> remainder;
  bitsetDivide<N>(dividend, modulo, quotient, remainder);
  dividend = remainder;
}

void assertTest() {
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
}