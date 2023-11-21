#include "../include/nested_loop_join_executor.h"

NestedLoopJoinExecutor::NestedLoopJoinExecutor(
    AbstractExecutor *left_child_executor,
    AbstractExecutor *right_child_executor, const std::string join_key)
    : left_(left_child_executor),
      right_(right_child_executor),
      join_key_(join_key){};

void NestedLoopJoinExecutor::Init() {
  flag_ = false;
  left_->Init();
  right_->Init();
}

bool NestedLoopJoinExecutor::Next(Tuple *tuple) {
  Tuple l_iter, r_iter;

  if (flag_) {
    while (right_->Next(&r_iter)) {
      if (Compare(curr_left_, r_iter)) {
        *tuple = Tuple(curr_left_);
        return true;
      }
    }
  }

  while (left_->Next(&l_iter)) {
    right_->Init();
    curr_left_ = l_iter;
    while (right_->Next(&r_iter)) {
      if (Compare(l_iter, r_iter)) {
        *tuple = Tuple(l_iter);
        flag_ = true;
        return true;
      }
    }
  }
  return false;
}

bool NestedLoopJoinExecutor::Compare(Tuple l, Tuple r) {
  if (join_key_ == "id") {
    if (l.id == r.id) {
      return true;
    }
  } else if (join_key_ == "val1") {
    if (l.val1 == r.val1) {
      return true;
    }
  } else if (join_key_ == "val2") {
    if (l.val2 == r.val2) {
      return true;
    }
  }
  return false;
}
