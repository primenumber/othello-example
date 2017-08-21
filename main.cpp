#include <iostream>
#include <fstream>
#include "position.hpp"
#include "board.hpp"
#include "search.hpp"

std::string load_str(std::string filename) {
  std::ifstream ifs(filename);
  std::string res;
  for (int i = 0; i < 8; ++i) {
    std::string line;
    std::getline(ifs, line);
    res += line;
  }
  return res;
}

int main(int argc, char **argv) {
  if (argc < 4) {
    std::cerr << "usage: " << argv[0] << " [PLAYER] [INIT] [BOARD]" << std::endl;
    std::cerr << "example: " << argv[0] << " WHITE BLACK init.txt" << std::endl;
    return 1;
  }
  Turn player = str_to_turn(argv[1]);
  Turn turn = str_to_turn(argv[2]);
  Board bd(load_str(argv[3]));
  while (!is_gameover(bd, turn)) {
    std::cout << board_to_str(bd) << std::endl;
    if (turn == player) {
      Position p = search(bd, turn);
      std::cout << pos_to_str(p) << std::endl;
      bd = move(bd, turn, p);
    } else {
      std::string pos_str;
      std::cin >> pos_str;
      try {
        bd = move(bd, turn, Position(pos_str));
      } catch(const char *err) {
        std::cerr << err << std::endl;
        continue;
      }
    }
    turn = opponent(turn);
  }
  return 0;
}
