#ifndef BITARRAY_H
#define BITARRAY_H

#include <iostream>

class BitArray {
private:
  int num_bits;
  std::vector<unsigned long> data;

public:
  BitArray();
  ~BitArray();

  explicit BitArray(int num_bits, unsigned long value = 0);
  BitArray(const BitArray& b);

  void swap(BitArray& b);

  BitArray& operator=(const BitArray& b);

  void resize(int new_size, bool value = false);
  void clear();
  void push_back(bool bit);

  BitArray& operator&=(const BitArray& b);
  BitArray& operator|=(const BitArray& b);
  BitArray& operator^=(const BitArray& b);

  BitArray& operator<<=(int n);
  BitArray& operator>>=(int n);
  BitArray operator<<(int n) const;
  BitArray operator>>(int n) const;

  BitArray& set(int n, bool val = true);
  BitArray& set();

  BitArray& reset(int n);
  BitArray& reset();

  bool any() const;
  bool none() const;
  BitArray operator~() const;
  int count() const;

  bool operator[](int i) const;

  int size() const;
  bool empty() const;

  std::string to_string() const;

  friend bool operator==(const BitArray& a, const BitArray& b);
  friend bool operator!=(const BitArray& a, const BitArray& b);

  void printDataBit(); // TODO: delete this method
};

#endif