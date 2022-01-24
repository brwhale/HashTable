# HashTable
simple hash table implementation

output from 2019 macbook (g++ O2):
```
Sample size: 1000000
time to fill vector:                                    0.006271
time to fill std map:                                   0.594889
time to fill std unordered map:                         0.360146
time to fill hashtable:                                 0.198374
time to fill hashtable (mhash):                         0.181335

time to fill string vector:                             0.031252
time to fill std string map:                            0.808575
time to fill std unordered string map:                  0.415238
time to fill string hashtable:                          0.220552
time to fill string hashtable (mhash):                  0.214595

time to sum (1074726655427696) vec:                     0.000377
time to sum (499999500000) std map:                     0.444971
time to sum (499999500000) std unordered map:           0.093206 with 1646237 buckets
time to sum (499999500000) hashtable:                   0.047668 with 625000 buckets
time to sum (499999500000) hashtable (mhash):           0.045173 with 625000 buckets

time to sum lengths (9483300) vec:                      0.001787
time to sum (499999500000) std string map:              0.702700
time to sum (499999500000) std unordered string map:    0.228353 with 1646237 buckets
time to sum (499999500000) string hashtable:            0.146150 with 625000 buckets
time to sum (499999500000) string hashtable (mhash):    0.136627 with 625000 buckets

Total std::unordered_map time: 1.096944
Total HashTable time: 0.612744, fraction of std: 0.558592
Total HashTable(mhash) time: 0.577731, fraction of std: 0.526673
```
So this naive implementation of a HashTable is almost twice as fast as std::unordered_map
