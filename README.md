# HashTable
simple hash table implementation

output from 2019 macbook (g++ O2):
```
Sample size: 1000000
time to fill vector:                                    0.006150
time to fill std map:                                   0.564573
time to fill std unordered map:                         0.333154
time to fill hashtable:                                 0.172776
time to fill hashtable (mhash):                         0.165442

time to fill string vector:                             0.030247
time to fill std string map:                            0.812622
time to fill std unordered string map:                  0.420199
time to fill string hashtable:                          0.192606
time to fill string hashtable (mhash):                  0.184335

time to sum (1074726655427696) vec:                     0.000398
time to sum (499999500000) std map:                     0.442435
time to sum (499999500000) std unordered map:           0.084314 with 1646237 buckets
time to sum (499999500000) hashtable:                   0.041412 with 524288 buckets
time to sum (499999500000) hashtable (mhash):           0.040880 with 524288 buckets

time to sum lengths (9483300) vec:                      0.001897
time to sum (499999500000) std string map:              0.708857
time to sum (499999500000) std unordered string map:    0.218482 with 1646237 buckets
time to sum (499999500000) string hashtable:            0.131577 with 524288 buckets
time to sum (499999500000) string hashtable (mhash):    0.091167 with 524288 buckets

Total std::unordered_map time: 1.056149
Total HashTable time: 0.538371, fraction of std: 0.509749
Total HashTable(mhash) time: 0.481824, fraction of std: 0.456208
```
So this simple implementation of a HashTable is around twice as fast as std::unordered_map
