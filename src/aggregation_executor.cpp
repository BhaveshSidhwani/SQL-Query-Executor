#include "../include/aggregation_executor.h"

AggregationExecutor::AggregationExecutor(AbstractExecutor *child_executor,
                                         AggregationType aggr_type)
    : child_(child_executor), aggr_type_(aggr_type){};

void AggregationExecutor::Init() {
    child_->Init();
    is_done = false;
}

bool AggregationExecutor::Next(Tuple *tuple) {
    if (is_done) {
        return false;
    }
    Tuple child_iter;
    tuple->val1 = 0;
    bool is_first_exec = true;

    while (child_->Next(&child_iter)) {
        if (is_first_exec) {
            tuple->val1 = child_iter.val1;
            is_first_exec = false;
        }

        switch (aggr_type_) {
            case AggregationType::COUNT:
                if (is_first_exec) {
                    tuple->val1 = 0;
                }
                tuple->val1++;
                break;
            case AggregationType::SUM:
                if (!is_first_exec) {
                    tuple->val1 += child_iter.val1;
                }
                break;
            case AggregationType::MIN:
                if (child_iter.val1 < tuple->val1) {
                    tuple->val1 = child_iter.val1;
                }
                break;
            case AggregationType::MAX:
                if (child_iter.val1 > tuple->val1) {
                    tuple->val1 = child_iter.val1;
                }
                break;
        }
    }
    is_done = true;
    return true;
}
