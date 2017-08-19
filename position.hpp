#pragma once
#include <string>

class Position {
 public:
  Position()
    : x_(0), y_(0), pass(true) {}
  Position(int x, int y)
    : x_(x), y_(y), pass(false) {}
  Position(const std::string &str) 
    : Position() {
    if (str.size() != 2) throw "invalid string";
    if (str == "ps") {
      pass = true;
    } else {
      pass = false;
      x_ = str[0] - '@';
      if (x_ < 0 || x_ >= 10) throw "invalid string x";
      y_ = str[1] - '0';
      if (y_ < 0 || y_ >= 10) throw "invalid string y";
    }
  }
  int x() const { return x_; }
  int y() const { return y_; }
  bool is_pass() const { return pass; }
 private:
  int x_, y_;
  bool pass;
};

inline std::string pos_to_str(const Position &pos) {
  if (pos.is_pass()) return "ps";
  std::string res;
  res += '@' + pos.x();
  res += '0' + pos.y();
  return res;
}
