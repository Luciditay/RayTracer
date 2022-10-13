#pragma once
#include <iostream>

template <typename T, typename Parameter>

class NamedType {
private:
  T _value;

public:
  explicit NamedType(T const &value) : _value(value) {}
  explicit NamedType(T &&value) : _value(std::move(value)) {}
  T const &get() const { return _value; }
  void show() const { std::cout << _value << std::endl; }
};
