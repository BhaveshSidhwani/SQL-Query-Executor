//===----------------------------------------------------------------------===//
//
//                         Rutgers CS539 - Database System
//                         ***DO NO SHARE PUBLICLY***
//
// Identification:   test/complex_executor_test.cpp
//
// Copyright (c) 2023, Rutgers University
//
//===----------------------------------------------------------------------===/

#include <iostream>
#include <string>
#include <vector>

#include "../include/filter_seq_scan_executor.h"
#include "../include/hash_join_executor.h"
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

  Table t3;
  for (int i = 0; i < 4; i++) {
    t3.insert(i, 5 + i, std::to_string(5 + i));
  }

  Table t4;
  for (int i = 4; i < 10; i++) {
    for (int j = 0; j < 2; j++) {
      t4.insert(i * 2 + j, i, std::to_string(i));
    }
  }

  FilterPredicate pred1(15, PredicateType::LESS);
  FilterPredicate pred2(5, PredicateType::GREATER);

  SeqScanExecutor scan1(&t1);
  FilterSeqScanExecutor scan2(&t2, &pred1);
  SeqScanExecutor scan3(&t3);
  FilterSeqScanExecutor scan4(&t4, &pred2);

  NestedLoopJoinExecutor join1(&scan1, &scan2, "val1");
  NestedLoopJoinExecutor join2(&scan3, &scan4, "val2");

  NestedLoopJoinExecutor executor(&join1, &join2, "val1");

  executor.Init();
  Tuple tuple;
  while (executor.Next(&tuple)) {
    cout << "Successfully get tuple! id: " << tuple.id
         << " val1: " << tuple.val1 << " val2: " << tuple.val2 << endl;
  }

  // Expected Output:
  /*
  Successfully get tuple! id: 6 val1: 6 val2: 6
  Successfully get tuple! id: 6 val1: 6 val2: 6
  Successfully get tuple! id: 7 val1: 7 val2: 7
  Successfully get tuple! id: 7 val1: 7 val2: 7
  Successfully get tuple! id: 8 val1: 8 val2: 8
  Successfully get tuple! id: 8 val1: 8 val2: 8
  */

  return 0;
}
