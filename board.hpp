#pragma once
#include <array>
#include <string>
#include "position.hpp"

enum class Turn {
  BLACK,
  WHITE
};

inline Turn opponent(const Turn &turn) {
  switch (turn) {
    case Turn::BLACK:
      return Turn::WHITE;
    case Turn::WHITE:
      return Turn::BLACK;
    default:
      throw "invalid turn value";
  }
}

inline Turn str_to_turn(const std::string &str) {
  if (str == "BLACK") return Turn::BLACK;
  else if (str == "WHITE") return Turn::WHITE;
  else throw "invalid string";
}

enum class Stone : char {
  EMPTY,
  BLACK,
  WHITE
};

inline Stone turn_to_stone(const Turn &turn) {
  switch (turn) {
    case Turn::BLACK:
      return Stone::BLACK;
    case Turn::WHITE:
      return Stone::WHITE;
    default:
      throw "invalid turn value";
  }
}

class Board {
 public:
  Board(const std::string &str) {
    if (str.size() != 64) throw "invalid string";
    for (int x = 0; x < 10; ++x) {
      for (int y = 0; y < 10; ++y) {
        table[x][y] = Stone::EMPTY;
      }
    }
    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 8; ++j) {
        int x = j+1;
        int y = i+1;
        switch (str[i*8+j]) {
          case 'X':
            table[x][y] = Stone::BLACK;
            break;
          case 'O':
            table[x][y] = Stone::WHITE;
            break;
          case '-':
            break;
          default: throw "invalid string";
        }
      }
    }
  }
  Board(const Board &) = default;
  Board& operator=(const Board &) = default;
  const Stone& at(int x, int y) const {
    return table.at(x).at(y);
  }
  Stone& at(int x, int y) {
    return table.at(x).at(y);
  }
 private:
  std::array<std::array<Stone, 10>, 10> table; // 8x8の盤面の周囲に番兵として空きマスを設ける
};

bool movable(const Board &bd, const Turn &turn, const Position &pos);
Board move(const Board &bd, const Turn &turn, const Position &pos);
bool is_gameover(const Board &bd, const Turn &turn);
std::string board_to_str(const Board &bd);
