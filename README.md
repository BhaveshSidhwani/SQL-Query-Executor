# CS539 - Database System

Programming Project 2 - Query Execution

## Project Description

This programming project is to add support for executing queries in a database system. You will implement executors that are responsible for taking query plans and executing them. You will create executors that perform sequential scans, hash joins and aggregations.

We will use the iterator query processing model (i.e., the Iterator model). Every query plan either returns a single tuple or indicates that there are no more tuples. This lets the executor implement a loop that just keeps calling `Next` on its children to get and process their tuples.

Optional reading resources: [following a select statement through the PostgreSQL internals](https://patshaughnessy.net/2014/10/13/following-a-select-statement-through-postgres-internals)

The project is comprised of the following task:

- Executor #1 - Sequential Scans (We provide complete reference code)
- Executor #1 - Filter Sequential Scans
- Executor #2 - Nested Loop Join
- Executor #3 - Hash Join
- Executor #4 - Aggregation

In this project, we fixed the tuple type and table type. All tables have the same schema: 
  - `id`: int type, primary key.
  - `val1`: int type value.
  - `val2`: string type value.

You can modify the initialization, `Init()`, `Next()` or add helper classes and functions in the executor realted .h files and .cpp files. But don't modify the pre-defined helpers functions we provide.

We manually pre-define simple query plans in the test cases. You can read the code to have a high-level idea about how the queries be executed.

## Executors

### SEQUENTIAL SCANS

Sequential scans iterate over a table and return its tuples one-at-a-time. We pass in the table to iterate in the initialization function. This simple sequential scans doesn't support filter by predicate.

We provide the code for this executor as the reference to help you understand how iterator model works.

### FILTER SEQUENTIAL SCANS

This executor is similar to the simple sequential scans executor. But it support the predicate filter function. We pass in the table and predicate in the initialization function.

**Hint**: The `FilterPredicate` supports basic three comparisons. You just need to call the `evaluate()` function to compare it with the processed tuple.

### NESTED LOOP JOIN

This executor will have only once child that propagates tuples corresponding to the outer table of the join. For each of these tuples, you will need to find the corresponding tuple in the inner table that having the same value on the join key.

### HASH JOIN

Hash joins are used to combine the results of two child executors together. In this project, you just need to implement a basic hash join. For more details on hash joins, refer to the Lecture #9 notes on join algorithms. In this project, by convention the left child is used to build the hash table and the right child is used to probe.

We are providing you with a `SimpleHashJoinHashTable` implementation. You can use it to build the hash table and probe.

We also provide the `SimpleHashFunction` to convert a specify tuple attribute to a hash value. We pass in the hash function in the initialization of the executor, you can easily use it by calling `hash_fn->GetHash(tuple)` and don't need to take care of the join key.

### Aggregation

This is a simple version of the aggregation that you just need to implement 4 aggregation operations: `Count, Sum, Max, Min` on `val1` value. Since we just have one common schema, for the return Tuple, just put some default values for `id` and `val2`.

## Build

run the following commands to build the system:

```
$ mkdir build
$ cd build
$ cmake ..
$ make
```


## Testing

You can test the individual components of this assignment using our testing file in the (`test/`) folder, you can modify this file to test and debug the functionality.

We just provide simple sample test cases in the testing file. We will use more complex test cases for grading.

**Hint**: We recommend you to read the test code to have a clear idea about the whole query execution process. You can try the seq_scan_test first.

```
$ cd build
$ ./seq_scan_test
```

## Submission

Compress the whole project folder into a zip file and submit it. Include all the cmake files.

## Grading Rubric

Each project submission will be graded based on the following criteria:

Does the submission successfully execute all of the test cases and produce the correct answer?
Does the submission execute without any memory leaks?
Does the submission follow the code formatting and style policies?

Note that we will use additional test cases that are more complex and go beyond the sample test cases that we provide you.

**WARNING: All of the code for this project must be your own. You may not copy source code from other students or other sources that you find on the web. Plagiarism will not be tolerated. See [Rutgers University Academic Integrity Policy](http://nbacademicintegrity.rutgers.edu/) for additional information.**
