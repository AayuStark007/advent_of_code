#include <fstream>
#include <map>
#include <math.h>

using namespace std;

map<string, int> digits = {
    {"zero", 0}, {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4},
    {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9},
};

int process_part1(string input) {
  int num = 0;

  // extract numbers from the line: seven7he3l0thre -> 730
  for (char c : input) {
    if (isdigit(c)) {
      num = (num * 10) + (c - '0');
    }
  }

  // only retain the 1st and last digit
  int power = (int)log10(num);
  int first = (int)(num / pow(10, power));
  int last = num % 10;
  return (first * 10) + last;
}

int process_part2(string input) {
  printf("For input [%s]:\n", input.c_str());

  int first = -1;
  int last = -1;
  char digit;

  while (!input.empty()) {
    // if input starts with numeric digit
    if (isdigit(input.front())) {
      printf("\tfound [%c] => %c\n", input.front(), input.front());
      digit = input.front();
      if (-1 == first) {
        first = digit - '0';
      }
    } else {
      for (auto it = digits.begin(); it != digits.end(); ++it) {
        // if start of input matches known digit word
        if (input.substr(0, it->first.length()).find(it->first.c_str(), 0) !=
            string::npos) {
          printf("\tfound [%s] => %d\n", it->first.c_str(), it->second);
          digit = it->second + '0';
          if (-1 == first) {
            first = it->second;
          }
          break;
        }
      }
    }

    // remove the first char
    input.erase(0, 1);
  }
  last = digit - '0';

  return (first * 10) + last;
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
  printf("Solution for Day1#Part1: %d\n", sum_part1);
  printf("Solution for Day1#Part2: %d\n", sum_part2);

  inputFile.close();
  return 0;
}