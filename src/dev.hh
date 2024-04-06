#pragma once

#include <cmath>
#include <cstdlib>
#include <cstdint>

#include <iostream>

#define PRINT(...) \
  ::std::cout << #__VA_ARGS__ << " = " << __VA_ARGS__ << ::std::endl

#define FLAG(...)  \
  ::std::cout << "FLAG:" << #__VA_ARGS__ << ::std::endl

#define SHOW(...)  \
  ::std::cout << #__VA_ARGS__ << ::std::endl

#define COUT(...)  \
  ::std::cout << __VA_ARGS__ << ::std::endl

#define STRING(...) __VA_ARGS__
