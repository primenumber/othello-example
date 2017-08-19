#include "board.hpp"
#include <sstream>

bool movable(const Board &bd, const Turn &turn, const Position &pos) {
  if (pos.is_pass()) throw "invalid call";
  Stone stone = turn_to_stone(turn);
  Stone op_stone = turn_to_stone(opponent(turn));
  int x = pos.x();
  int y = pos.y();
  if (bd.at(x, y) != Stone::EMPTY) return false;
  int dx[8] = {1, 1, 1, 0, -1, -1, -1, 0};
  int dy[8] = {1, 0, -1, -1, -1, 0, 1, 1};
  for (int i = 0; i < 8; ++i) { // 8方向に対してひっくり返せるかそれぞれ調べる
    for (int j = 1;; ++j) {
      int nx = x + j * dx[i];
      int ny = y + j * dy[i];
      if (bd.at(nx, ny) != op_stone) {
        if (bd.at(nx, ny) == stone) {
          if (j >= 2) { // 相手の石を1個以上挟んでいればひっくり返せる
            return true;
          } else {
            break;
          }
        } else {
          break;
        }
      }
    }
  }
  return false;
}

Board move(const Board &bd, const Turn &turn, const Position &pos) {
  if (pos.is_pass()) return bd;
  Stone stone = turn_to_stone(turn);
  Stone op_stone = turn_to_stone(opponent(turn));
  int x = pos.x();
  int y = pos.y();
  if (!movable(bd, turn, pos)) throw "invalid move";
  int dx[8] = {1, 1, 1, 0, -1, -1, -1, 0};
  int dy[8] = {1, 0, -1, -1, -1, 0, 1, 1};
  Board res = bd;
  for (int i = 0; i < 8; ++i) {
    for (int j = 1;; ++j) {
      int nx = x + j * dx[i];
      int ny = y + j * dy[i];
      if (bd.at(nx, ny) != op_stone) {
        if (bd.at(nx, ny) == stone) {
          if (j >= 2) {
            for (int k = 1; k < j; ++k) {
              int mx = x + k * dx[i];
              int my = y + k * dy[i];
              res.at(mx, my) = stone;
            }
          } else {
            break;
          }
        } else {
          break;
        }
      }
    }
  }
  res.at(x, y) = stone;
  return res;
}

bool is_gameover(const Board &bd, const Turn &turn) {
  for (int x = 1; x <= 8; ++x) {
    for (int y = 1; y <= 8; ++y) {
      if (movable(bd, turn, Position(x, y))) return false;
    }
  }
  for (int x = 1; x <= 8; ++x) {
    for (int y = 1; y <= 8; ++y) {
      if (movable(bd, opponent(turn), Position(x, y))) return false;
    }
  }
  return true;
}

std::string board_to_str(const Board &bd) {
  std::stringstream ss;
  for (int y = 1; y <= 8; ++y) {
    for (int x = 1; x <= 8; ++x) {
      switch (bd.at(x, y)) {
        case Stone::BLACK:
          ss << 'X';
          break;
        case Stone::WHITE:
          ss << 'O';
          break;
        case Stone::EMPTY:
          ss << '-';
          break;
      }
    }
    ss << '\n';
  }
  return ss.str();
}
