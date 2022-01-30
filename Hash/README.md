For my tests.cpp, ruin quadratic probing outputs
(a 1)
(g 7)
(j 10)
(m 13)
notice that (d 4) is never in the hashtable because add fails to find an empty space for (d 4), thus quadratic probing is ruined

for 5000 randomly generated strings
the approximate number of probes is around 3000 to 3300 which are slightly smaller than 2*5000/3 = 3333.3333