//===----------------------------------------------------------------------===//
//
//                         Rutgers CS539 - Database System
//                         ***DO NO SHARE PUBLICLY***
//
// Identification:   test/seq_scan_test.cpp
//
// Copyright (c) 2023, Rutgers University
//
//===----------------------------------------------------------------------===/

#include <iostream>
#include <string>
#include <vector>

#include "../include/seq_scan_executor.h"

using std::cout;
using std::endl;
using std::vector;

int main() {
  Table t1;
  t1.insert(0, 0, "0");
  t1.insert(0, 0, "0");

  for (int i = 0; i < 10; i++) {
    t1.insert(i, i, std::to_string(i));
  }

  SeqScanExecutor executor(&t1);

  executor.Init();
  Tuple tuple;
  while (executor.Next(&tuple)) {
    cout << "Successfully get tuple! id: " << tuple.id
         << " val1: " << tuple.val1 << " val2: " << tuple.val2 << endl;
  }

  // Expected Output:
  /*
  Successfully get tuple! id: 0 val1: 0 val2: 0
  Successfully get tuple! id: 0 val1: 0 val2: 0
  Successfully get tuple! id: 0 val1: 0 val2: 0
  Successfully get tuple! id: 1 val1: 1 val2: 1
  Successfully get tuple! id: 2 val1: 2 val2: 2
  Successfully get tuple! id: 3 val1: 3 val2: 3
  Successfully get tuple! id: 4 val1: 4 val2: 4
  Successfully get tuple! id: 5 val1: 5 val2: 5
  Successfully get tuple! id: 6 val1: 6 val2: 6
  Successfully get tuple! id: 7 val1: 7 val2: 7
  Successfully get tuple! id: 8 val1: 8 val2: 8
  Successfully get tuple! id: 9 val1: 9 val2: 9
  */

  return 0;
}
