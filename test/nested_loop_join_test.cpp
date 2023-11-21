//===----------------------------------------------------------------------===//
//
//                         Rutgers CS539 - Database System
//                         ***DO NO SHARE PUBLICLY***
//
// Identification:   test/nested_loop_join_test.cpp
//
// Copyright (c) 2023, Rutgers University
//
//===----------------------------------------------------------------------===/

#include <iostream>
#include <string>
#include <vector>

#include "../include/nested_loop_join_executor.h"
#include "../include/seq_scan_executor.h"

using std::cout;
using std::endl;
using std::vector;

int main() {
  Table t1;
  for (int i = 0; i < 15; i++) {
    t1.insert(i, i, std::to_string(i));
  }

  Table t2;
  for (int i = 5; i < 20; i++) {
    t2.insert(i, i, std::to_string(i));
  }

  SeqScanExecutor seq1(&t1);
  SeqScanExecutor seq2(&t2);

  NestedLoopJoinExecutor executor1(&seq1, &seq2, "val1");

  executor1.Init();
  Tuple tuple;
  while (executor1.Next(&tuple)) {
    cout << "Successfully get tuple! id: " << tuple.id
         << " val1: " << tuple.val1 << " val2: " << tuple.val2 << endl;
  }

  cout << endl;
  NestedLoopJoinExecutor executor2(&seq1, &seq2, "val2");
  executor2.Init();
  while (executor2.Next(&tuple)) {
    cout << "Successfully get tuple! id: " << tuple.id
         << " val1: " << tuple.val1 << " val2: " << tuple.val2 << endl;
  }

  // Expected Output:
  /*
  Successfully get tuple! id: 5 val1: 5 val2: 5
  Successfully get tuple! id: 6 val1: 6 val2: 6
  Successfully get tuple! id: 7 val1: 7 val2: 7
  Successfully get tuple! id: 8 val1: 8 val2: 8
  Successfully get tuple! id: 9 val1: 9 val2: 9
  Successfully get tuple! id: 10 val1: 10 val2: 10
  Successfully get tuple! id: 11 val1: 11 val2: 11
  Successfully get tuple! id: 12 val1: 12 val2: 12
  Successfully get tuple! id: 13 val1: 13 val2: 13
  Successfully get tuple! id: 14 val1: 14 val2: 14

  Successfully get tuple! id: 5 val1: 5 val2: 5
  Successfully get tuple! id: 6 val1: 6 val2: 6
  Successfully get tuple! id: 7 val1: 7 val2: 7
  Successfully get tuple! id: 8 val1: 8 val2: 8
  Successfully get tuple! id: 9 val1: 9 val2: 9
  Successfully get tuple! id: 10 val1: 10 val2: 10
  Successfully get tuple! id: 11 val1: 11 val2: 11
  Successfully get tuple! id: 12 val1: 12 val2: 12
  Successfully get tuple! id: 13 val1: 13 val2: 13
  Successfully get tuple! id: 14 val1: 14 val2: 14
  */

  return 0;
}
