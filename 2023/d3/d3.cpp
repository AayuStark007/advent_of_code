#include <unordered_map>
#include <vector>
// #define DEBUG_LOGGING

#include "../util.h"
#include <cassert>
#include <fstream>

struct Num {
  int seq;
  int num;
  int row;
  int col_start;
  int col_end;
};

/**
 * @brief safe access in a grid with out of bounds checking
 *
 * @param input input grid
 * @param i row to access
 * @param j col to access
 * @return char at the requested row,col otherwise '.' if invalid coords
 */
char safe_access(std::vector<std::string> &input, int i, int j) {
  if (i < 0 || i > input.size() - 1 || j < 0 || j > input[0].size() - 1)
    return '.';
  return input[i][j];
}

/**
 * @brief Traverse the neighbourhood of each found number and check for any
 * symbols
 *
 * @param input input grid with numbers and symbols
 * @param row at which the number was found
 * @param st start col index of the number
 * @param en end col index of the number
 * @return true if the neighbourhood around the number has a symbol (except '.')
 * @return false no symbols found in the neighborhood
 */
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

/**
 * @brief return index of Num from the vector {nums} which is present at the
 * given row, col in the grid.
 *
 * @param nums vector of Nums whithin which the check is made
 * @param row find num preset at this row
 * @param col find num passing through this col
 * @return int index of matching number otherwise, -1
 */
int find_num_index_at(std::vector<Num> &nums, int row, int col) {
  for (int i = 0; i < nums.size(); i++) {
    if (nums[i].row == row &&
        (col >= nums[i].col_start && col <= nums[i].col_end)) {
      return i;
    }
  }
  return -1;
}

/**
 * @brief Taking the Num vector and the symbol, find those Num which are in
 * neighbor of this symbol.
 *
 * @param nums Num vector having the start and end position of each number in
 * grid
 * @param symbol Special char whose neighbours we want to check
 * @param row Row location of symbol
 * @param col Col location of the symbol
 * @return std::vector<int> vector of numbers adjacent to the symbol in the grid
 */
std::vector<int> find_nums_adj(std::vector<Num> &nums, char symbol, int row,
                               int col) {
  std::vector<int> result;
  std::unordered_map<int, bool> found;
  for (auto i = row - 1; i <= row + 1; i++) {
    for (auto j = col - 1; j <= col + 1; j++) {
      auto index = find_num_index_at(nums, i, j);
      if (index >= 0 && !found[index]) {
        found[index] = true;
        result.push_back(nums[index].num);
      }
    }
  }
  return result;
}

/**
 * @brief Traverse through the input grid and find all numbers and capture their
 * value, row and column span in Num struct.
 *
 * @param input input grid of numbers and symbols.
 * @return std::vector<Num> vector of computed Num structs for each number found
 * in grid.
 */
std::vector<Num> gather_nums_from_grid(std::vector<std::string> &input) {
  int num = 0;
  int st = -1, en = -1;
  int seq = 0;
  std::vector<Num> nums;
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
        nums.push_back(Num{
            .seq = seq, .num = num, .row = i, .col_start = st, .col_end = en});
        st = -1, en = -1, num = 0, seq++;
      }
    }
  }
  return nums;
}

long process_part2(std::vector<std::string> &input) {
  // scan for each number and store in struct Num
  // will be used later to correlate with gear (*) position
  auto nums = gather_nums_from_grid(input);

  long sum = 0l;
  for (int i = 0; i < input.size(); i++) {
    for (int j = 0; j < input[0].size(); j++) {
      char ch = input[i][j];
      if (ch == '*') {
        std::vector<int> adj = find_nums_adj(nums, ch, i, j);
        if (adj.size() != 2)
          continue;
        sum += adj[0] * adj[1];
      }
    }
  }
  return sum;
}

int main(int argc, char **argv) {
  std::ifstream inputFile("input.txt", std::ios::in | std::ios::binary);
  if (!inputFile.is_open()) {
    printf("error opening input file\n");
    return 1;
  }

  std::vector<std::string> input;
  std::string line;

  while (getline(inputFile, line)) {
    input.push_back(line);
  }

  long sum_part1 = process_part1(input);
  long sum_part2 = process_part2(input);

  printf("Solution for Day2#Part1: %ld\n", sum_part1); // 556057
  printf("Solution for Day2#Part2: %ld\n", sum_part2); // 82824352

  assert(sum_part1 == 556057);
  assert(sum_part2 == 82824352);

  inputFile.close();
  return 0;
}