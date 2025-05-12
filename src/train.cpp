// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() :countOp(0), first(nullptr) {}

void Train::addCar(bool light) {
  Car* newCar = new Car{ light, nullptr, nullptr };

  if (!first) {
    newCar->next = newCar;
    newCar->prev = newCar;
    first = newCar;
  } else {
    newCar->next = first;
    newCar->prev = first->prev;
    first->prev->next = newCar;
    first->prev = newCar;
  }
}

uint64_t Train::getLength() {
  if (!first->light) {
    first->light = true;
  }
  int steps = 0;
  Car* current = first;
  while (true) {
    steps = 0;
    do {
      current = current->next;
      steps++;
      countOp++;
    } while (!current->light && current != first);
    current->light = false;
    for (int i = 0; i < steps; i++) {
      current = current->prev;
      countOp++;
    }
    if (!current->light) {
      return steps;
    }
  }
}

uint64_t Train::getOpCount() {
  return countOp;
}
