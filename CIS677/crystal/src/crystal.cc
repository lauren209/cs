/* #include <crystal/crystal.hpp> */
/* #include <crystal/particle.hpp> */
#include <algorithm>
#include <chrono>
#include <fstream>
#include "../include/crystal/crystal.hpp"
#include "../include/crystal/particle.hpp"
#include <iostream>
#include <iterator>
#include <random>

namespace crystal {
  int Crystal::Run(int particles) {
    int radius = 0;
    std::vector<std::vector<int>> simulation_space(
        this->ROWS,
        std::vector<int>(this->COLS));

    int origin_row = std::get<0>(this->ORIGIN);
    int origin_column = std::get<1>(this->ORIGIN);

    // Place our point in the center of the board
    simulation_space[origin_row][origin_column] = 1;

    for (int i = 0; i < particles; i++) {
      if (radius >= this->ROWS) {
        this->end_simulation(simulation_space);
        return EXIT_SUCCESS;
      }

      std::tuple<int, int> point_location = this->insert_particle(simulation_space);

    }
  }

  /**
   * Takes the simulation space and
   * maps it into a file for processing
   * in the python interpreter
   */
  void Crystal::end_simulation(const std::vector<std::vector<int>> &simulation_space) {
    std::ofstream the_goods;

    the_goods.open("output.txt");

    for (int i = 0; i < simulation_space.size(); i++) {
      for (int j = 0; j < simulation_space[i].size(); j++) {
        the_goods << simulation_space[i][j] << " ";
      }
      the_goods << "\n";
    }
  }

  bool Crystal::valid_coordinates(const std::vector<std::vector<int>>& simulation_space, int x, int y) {
    return simulation_space[x][y] == 0;
  }

  std::tuple<int, int> Crystal::insert_particle(const std::vector<std::vector<int>>& simulation_space) {
    std::random_device rd;
    std::mt19937 g(rd());
    int random_row = 0;
    int random_col = 0;

    while (true) {
      random_row = g() % this->ROWS;
      random_col = g() % this->COLS;
      if (this->valid_coordinates(simulation_space, random_row, random_col)) {
        return std::make_tuple(random_row, random_col);
      }
    }
  }

}// namespace crystal