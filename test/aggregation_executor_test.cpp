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

#include "../include/aggregation_executor.h"

#include <iostream>
#include <string>
#include <vector>

#include "../include/seq_scan_executor.h"

using std::cout;
using std::endl;
using std::vector;

int main() {
  Table t1;

  for (int i = 0; i < 10; i++) {
    t1.insert(i, i, std::to_string(i));
  }

  SeqScanExecutor seq(&t1);
  // Note: for aggregation executor, we just need to verify tuple.val1

  {
    AggregationExecutor aggr_count(&seq, AggregationType::COUNT);
    aggr_count.Init();
    Tuple tuple;
    while (aggr_count.Next(&tuple)) {
      cout << "COUNT aggregation: "
           << " val1: " << tuple.val1 << endl;
    }
  }
  {
    AggregationExecutor aggr_sum(&seq, AggregationType::SUM);
    aggr_sum.Init();
    Tuple tuple;
    while (aggr_sum.Next(&tuple)) {
      cout << "SUM aggregation: "
           << " val1: " << tuple.val1 << endl;
    }
  }

  {
    AggregationExecutor aggr_max(&seq, AggregationType::MAX);
    aggr_max.Init();
    Tuple tuple;
    while (aggr_max.Next(&tuple)) {
      cout << "MAX aggregation: "
           << " val1: " << tuple.val1 << endl;
    }
  }

  {
    AggregationExecutor aggr_min(&seq, AggregationType::MIN);
    aggr_min.Init();
    Tuple tuple;
    while (aggr_min.Next(&tuple)) {
      cout << "MIN aggregation: "
           << " val1: " << tuple.val1 << endl;
    }
  }

  // Expected Output:
  /*
  COUNT aggregation: val1: 10
  SUM aggregation: val1: 45
  MAX aggregation: val1: 9
  MIN aggregation: val1: 0
  */

  return 0;
}
