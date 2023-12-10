#include <set>
#include <unordered_map>
#include <vector>
// #define DEBUG_LOGGING

#include "../util.h"
#include <cassert>
#include <fstream>
#include <math.h>

struct card_info {
  int id;
  std::vector<int> winning;
  std::vector<int> current;
};

using std::ifstream, std::ios;

std::vector<int> read_line_ints(std::string &input) {
  std::vector<int> result;
  debugf("\t");

  int num = 0;
  bool filling = false;
  for (int i = 0; i < input.length(); i++) {
    char ch = input[i];
    if (std::isdigit(ch)) {
      num = (num * 10) + (ch - '0');
      filling = true;
    } else if (filling) {
      debugf("[%d] ", num);
      result.push_back(num);
      filling = false;
      num = 0;
    }
  }

  // end line case
  if (filling) {
    debugf("[%d] ", num);
    result.push_back(num);
  }

  debugf("\n");

  return result;
}

card_info get_card_info(std::string &input) {
  // find card id: Card X.....:
  //                    ^--5  ^--colon_pos
  int skip_len = std::string("Card").size();
  int colon_pos = input.find(':');
  int card_id = atoi(input.substr(skip_len, colon_pos - skip_len).c_str());
  debugf("Card Id: %d\n", card_id);

  // extract winning nums

  int bar_pos = input.find('|');
  std::string winning_str = input.substr(colon_pos, bar_pos - colon_pos);
  std::string current_str = input.substr(bar_pos + 1);

  debugf("\twinning: %s\n", winning_str.c_str());
  std::vector<int> winning = read_line_ints(winning_str);

  debugf("\tcurrent: %s\n", current_str.c_str());
  std::vector<int> current = read_line_ints(current_str);

  return card_info{.id = card_id, .winning = winning, .current = current};
}

int count_winning_nums(card_info &info) {
  // find winning nums in current
  int count = 0;
  std::set<int> winning;
  for (int win : info.winning) {
    winning.insert(win);
  }

  for (int num : info.current) {
    if (winning.find(num) != winning.end()) {
      count++;
    }
  }

  return count;
}

long get_card_points(card_info &info) {
  int count = count_winning_nums(info);
  return (count == 0) ? 0 : pow(2, count - 1);
}

long process_part1(std::string &input) {
  card_info info = get_card_info(input);
  long point = get_card_points(info);
  debugf("\tPoints: %ld\n", point);
  return point;
}

int process_part2(std::vector<std::string> &input) {
  std::unordered_map<int, int> card_id_copies;
  card_id_copies[1] = 0;
  int total = 0;
  for (std::string &line : input) {
    card_info info = get_card_info(line);
    debugf("Card: %d\n", info.id);
    int count = count_winning_nums(info);
    int self_copies = card_id_copies[info.id];
    debugf("\tcopies: %d\n", self_copies);
    debugf("\tcount: %d\n", count);
    total += self_copies + 1;
    debugf("\tloop: {%d} to {%d}\n", info.id + 1, info.id + count);
    for (int i = info.id + 1; i <= info.id + count; i++) {
      if (card_id_copies.find(i) != card_id_copies.end()) {
        int curr = card_id_copies[i];
        debugf("\tset card {%d} as %d\n", i, curr + self_copies + 1);
        card_id_copies[i] = curr + self_copies + 1;
      } else {
        debugf("\tinit card {%d} as %d\n", i, self_copies + 1);
        card_id_copies[i] = self_copies + 1;
      }
    }
  }

  for (auto it = card_id_copies.begin(); it != card_id_copies.end(); ++it) {
    debugf("[%d] => {%d}\n", it->first, it->second);
  }

  // count total cards
  return total;
}

int main(int argc, char **argv) {
  ifstream inputFile("input.txt", ios::in | ios::binary);
  if (!inputFile.is_open()) {
    printf("error opening input file\n");
    return 1;
  }

  std::string input;

  long sum_part1 = 0, sum_part2 = 0;
  std::vector<std::string> lines;
  while (getline(inputFile, input)) {
    sum_part1 += process_part1(input);
    lines.push_back(input);
  }
  sum_part2 = process_part2(lines);

  printf("Solution for Day2#Part1: %ld\n", sum_part1); // 24733
  printf("Solution for Day2#Part2: %ld\n", sum_part2); // 5422730

  assert(sum_part1 == 24733);
  assert(sum_part2 == 5422730);

  inputFile.close();
  return 0;
}