#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <vector>
// #define DEBUG_LOGGING

#include "../util.h"
#include <cassert>
#include <fstream>
#include <map>
#include <math.h>

using namespace std;

char safe_access(std::vector<std::string> &input, int i, int j) {
  if (i < 0 || i > input.size() - 1 || j < 0 || j > input[0].size() - 1)
    return '.';
  return input[i][j];
}

bool has_special_neighbour(std::vector<std::string> &input, int row, int st,
                           int en) {
  for (int i = row - 1; i <= row + 1; i++) {
    for (int j = st - 1; j <= en + 1; j++) {
      char ch = safe_access(input, i, j);
      if (!isdigit(ch) && ch != '.') {
        return true;
      }
    }
  }
  return false;
}

int process_part1(std::vector<std::string> &input) {
  int num = 0;
  int st = -1, en = -1;
  long sum = 0;
  for (int i = 0; i < input.size(); i++) {
    num = 0, st = -1, en = -1;
    for (int j = 0; j < input[0].size(); j++) {
      if (isdigit(input[i][j])) {
        num = (num * 10) + (input[i][j] - '0');
        if (st == -1)
          st = j;
      } else if (st != -1 && en == -1) {
        // found end of number
        en = j - 1;
        if (has_special_neighbour(input, i, st, en)) {
          debugf("%d\n", num);
          sum += num;
        }
        st = -1, en = -1, num = 0;
      }
    }
  }
  return sum;
}

int process_part2(string &input) { return 0; }

int main(int argc, char **argv) {
  ifstream inputFile("input.txt", ios::in | ios::binary);
  if (!inputFile.is_open()) {
    printf("error opening input file\n");
    return 1;
  }

  std::vector<string> input;
  string line;

  while (getline(inputFile, line)) {
    input.push_back(line);
  }

  long sum_part1 = process_part1(input);
  long sum_part2 = 0l;

  printf("Solution for Day2#Part1: %ld\n", sum_part1); // 556057
  printf("Solution for Day2#Part2: %ld\n", sum_part2); // todo

  assert(sum_part1 == 556057);
  //   assert(sum_part2 == todo);

  inputFile.close();
  return 0;
}