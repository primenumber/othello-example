#include "eval.hpp"

int eval(const Board &bd, const Turn &turn) {
  int black_cnt = 0;
  int white_cnt = 0;
  for (int x = 1; x <= 8; ++x) {
    for (int y = 1; y <= 8; ++y) {
      switch (bd.at(x, y)) {
        case Stone::BLACK:
          ++black_cnt;
          break;
        case Stone::WHITE:
          ++white_cnt;
          break;
        default:;
      }
    }
  }
  if (turn == Turn::BLACK) return black_cnt - white_cnt;
  else return white_cnt - black_cnt;
}
