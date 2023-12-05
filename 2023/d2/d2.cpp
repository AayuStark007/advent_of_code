#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <vector>
// #define DEBUG_LOGGING

#include "../util.h"
#include <cassert>
#include <fstream>
#include <map>
#include <math.h>

using namespace std;

struct play {
  int red;
  int green;
  int blue;
};

struct game_info {
  int id;
  vector<play> plays;
};

play parse_play_data(string &play_raw) {
  int red = 0, green = 0, blue = 0;

  int num = 0;
  for (uint32_t i = 0; i < play_raw.size(); ++i) {
    char c = play_raw[i];
    if (isdigit(c)) {
      num = (num * 10) + (c - '0');
    } else if (isalpha(c)) {
      if (0 == play_raw.compare(i, 3, "red")) {
        red = num;
        i += 2;
      } else if (0 == play_raw.compare(i, 5, "green")) {
        green = num;
        i += 4;
      } else if (0 == play_raw.compare(i, 4, "blue")) {
        blue = num;
        i += 3;
      } else {
        printf("invalid color type for string segment: %s\n",
               play_raw.substr(i).c_str());
        assert(false);
      }
      num = 0;
    } else { // ' ' or ','
      continue;
    }
  }
  debugf("\tPlay: %d red, %d green, %d blue\n", red, green, blue);
  return play{.red = red, .green = green, .blue = blue};
}

game_info get_game_info(string &input) {
  // find game id: Game X.....:
  //                    ^--5  ^--colon_pos
  int colon_pos = input.find(":");
  int game_id = atoi(input.substr(5, colon_pos - 5).c_str());
  debugf("Game Id: %d\n", game_id);

  // extract plays data: %d red, % green...; %d green...; ...
  vector<play> plays;
  int find_start = colon_pos + 1;
  auto semicol_pos = string::npos;
  while ((semicol_pos = input.find(";", find_start)) != string::npos) {
    // find_start);
    string play_raw = input.substr(find_start, semicol_pos - find_start);
    plays.push_back(parse_play_data(play_raw));
    find_start = semicol_pos + 1;
  }
  // capture last play data (without semicolon)
  string last_play_raw = input.substr(find_start);
  plays.push_back(parse_play_data(last_play_raw));

  return game_info{game_id, plays};
}

bool is_game_possible(game_info &info) {
  const int r = 12, g = 13, b = 14;

  for (auto &play : info.plays) {
    if (play.red > r || play.green > g || play.blue > b) {
      return false;
    }
  }

  return true;
}

int process_part1(string input) {
  auto game_info = get_game_info(input);
  return is_game_possible(game_info) ? game_info.id : 0;
}

int get_power(game_info &info) {
  int max_r = -1, max_g = -1, max_b = -1;
  // find min required cube to make game possible
  for (auto &play : info.plays) {
    max_r = max(max_r, play.red);
    max_g = max(max_g, play.green);
    max_b = max(max_b, play.blue);
  }

  return max_r * max_g * max_b;
}

int process_part2(string input) {
  auto game_info = get_game_info(input);
  return get_power(game_info);
}

int main(int argc, char **argv) {
  ifstream inputFile("input.txt", ios::in | ios::binary);
  if (!inputFile.is_open()) {
    printf("error opening input file\n");
    return 1;
  }

  string input;

  int sum_part1 = 0, sum_part2 = 0;
  while (getline(inputFile, input)) {
    sum_part1 += process_part1(input);
    sum_part2 += process_part2(input);
  }
  printf("Solution for Day2#Part1: %d\n", sum_part1); // 1867
  printf("Solution for Day2#Part2: %d\n", sum_part2); // 84538

  assert(sum_part1 == 1867);
  assert(sum_part2 == 84538);

  inputFile.close();
  return 0;
}