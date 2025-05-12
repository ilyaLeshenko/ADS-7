// Copyright 2022 NNTU-CS
#include <iostream>
#include <random>
#include <chrono>
#include "Train.h"

void printHeader() {
  std::cout << "N\t\tMode\t\tEterations\tTime\n";
  std::cout << "--------------------------------------------------\n";
}

void runExperiment(int numCars, const std::string& mode) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_int_distribution<> dist(0, 1);

  Train train;

  for (int i = 0; i < numCars; ++i) {
    bool light;
    if (mode == "all_on")
      light = true;
    else if (mode == "all_off")
      light = false;
    else
      light = dist(gen);
    train.addCar(light);
  }

  auto start = std::chrono::high_resolution_clock::now();
  int detected = train.getLength();
  auto end = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
  bool correct = (detected == numCars);

  std::cout << numCars << "\t\t" << mode << "\t\t"
    << train.getOpCount() << "\t\t"
    << duration << "\n";
}

int main() {
  printHeader();

  const int tests[] = { 50, 100, 250, 500, 750, 1000 };
  for (int n : tests) {
    runExperiment(n, "all_off");
    runExperiment(n, "all_on");
    runExperiment(n, "random");
    std::cout << "--------------------------------------------------\n";
  }
}
