#include "../include/hash_join_executor.h"

HashJoinExecutor::HashJoinExecutor(AbstractExecutor *left_child_executor,
                                   AbstractExecutor *right_child_executor,
                                   SimpleHashFunction *hash_fn)
    : left_(left_child_executor),
      right_(right_child_executor),
      hash_fn_(hash_fn) {}

void HashJoinExecutor::Init() {
  left_->Init();
  right_->Init();

  result_iter_ = 0;
  Tuple l_iter;
  
  ht.ClearTable();
  while (left_->Next(&l_iter)) {
    hash_t h = hash_fn_->GetHash(l_iter);
    ht.Insert(h, l_iter);
  }
};

bool HashJoinExecutor::Next(Tuple *tuple) {
  if (!hash_match_results_.empty()) {
    *tuple = hash_match_results_[result_iter_++];
    
    if (result_iter_ >= hash_match_results_.size()) {
      hash_match_results_.clear();
      result_iter_ = 0;
    }
    return true;
  }

  Tuple r_iter;
  while (right_->Next(&r_iter)) {
    hash_t h = hash_fn_->GetHash(r_iter);
    ht.GetValue(h, &hash_match_results_);
    if (!hash_match_results_.empty()) {
      *tuple = Tuple(hash_match_results_[result_iter_++]);
      if (result_iter_ >= hash_match_results_.size()) {
        hash_match_results_.clear();
        result_iter_ = 0;
      }
      return true;
    }
  }

  return false; 
}
