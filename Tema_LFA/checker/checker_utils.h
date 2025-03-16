#pragma once

#include <algorithm>
#include <iostream>
#include <optional>
#include <fstream>
#include <unordered_set>
#include <utility>
#include <iomanip>
#include <vector>
#include <string>
#include <chrono>
#include <regex>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <unistd.h>
#include <boost/tokenizer.hpp>
#include <sys/resource.h>

#define aaa system("read -r -p \"Press enter to continue...\" key");

std::pair<int, std::string> readInt(std::ifstream &in, int l, int r, const std::string& name);

double sigmoidStretch2x(int x);

class DFA{
  public:
    DFA();
    ~DFA();
    std::optional<std::string> readDFA(std::ifstream &in);
    bool accepts(std::string word);
    unsigned int size();
  private:
    unsigned int n;
    unsigned int start;
    unsigned int (*mat)[26];
    std::unordered_set<int> fin;
};
