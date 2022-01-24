# HashTable
simple hash table implementation

output from 2019 macbook (g++ O2):
time to fill vector:                                    0.006380
time to fill std map:                                   0.590294
time to fill std unordered map:                         0.347417
time to fill hashtable:                                 0.278725
time to fill hashtable (mhash):                         0.279218

time to fill string vector:                             0.029052
time to fill std string map:                            0.813420
time to fill std unordered string map:                  0.454887
time to fill string hashtable:                          0.330661
time to fill string hashtable (mhash):                  0.340210

time to sum (1074726655427696) vec:                     0.000368
time to sum (499999500000) std map:                     0.514760
time to sum (499999500000) std unordered map:           0.092402 with 1646237 buckets
time to sum (499999500000) hashtable:                   0.075948 with 1562500 buckets
time to sum (499999500000) hashtable (mhash):           0.076206 with 1562500 buckets

time to sum lengths (9483300) vec:                      0.002086
time to sum (499999500000) std string map:              0.815633
time to sum (499999500000) std unordered string map:    0.247796 with 1646237 buckets
time to sum (499999500000) string hashtable:            0.237457 with 1562500 buckets
time to sum (499999500000) string hashtable (mhash):    0.226176 with 1562500 buckets

So this naive implementation of a HashTable is just barely faster than std::unordered_map, cuts about 20% time for most operations.
Also seems like what you use as a key really matters. Certain growth rates and initial bucket sizes work a lot better depending on how much your hashes collide.
