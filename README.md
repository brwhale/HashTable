# HashTable
simple hash table implementation

output from 2019 macbook (g++ O2):
```
Sample size:1000000
time to fill vector:                                    0.006262
time to fill std map:                                   0.595982
time to fill std unordered map:                         0.355681
time to fill hashtable:                                 0.193190
time to fill hashtable (mhash):                         0.184076

time to fill string vector:                             0.031073
time to fill std string map:                            0.812114
time to fill std unordered string map:                  0.454910
time to fill string hashtable:                          0.222782
time to fill string hashtable (mhash):                  0.228903

time to sum (1074726655427696) vec:                     0.000418
time to sum (499999500000) std map:                     0.460798
time to sum (499999500000) std unordered map:           0.089913 with 1646237 buckets
time to sum (499999500000) hashtable:                   0.047576 with 625000 buckets
time to sum (499999500000) hashtable (mhash):           0.045975 with 625000 buckets

time to sum lengths (9483300) vec:                      0.001965
time to sum (499999500000) std string map:              0.723266
time to sum (499999500000) std unordered string map:    0.224673 with 1646237 buckets
time to sum (499999500000) string hashtable:            0.145953 with 625000 buckets
time to sum (499999500000) string hashtable (mhash):    0.137639 with 625000 buckets

Total std::unordered_map time: 1.125176
Total HashTable time: 0.609500, fraction of std: 0.541693
Total HashTable(mhash) time: 0.596593, fraction of std: 0.530222
```
So this naive implementation of a HashTable is almost twice as fast as std::unordered_map
