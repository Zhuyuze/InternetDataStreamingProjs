Project 1
Yuze Zhu
UFID: 75087354
Environment: Windows, C++
My classes: bloomFilter(number of bits, hashes) -- codedBloomFilter(number of filters, number of bits, hashes)
                    countingBloomFilter(number of counters, hashes)
codedBloomFilter uses bloomFilter as its part, not an inheritance.

All variables in parentheses, and number of input flows, size of hash table can be set in "main.cpp".
Implementations are all in "main.cpp", which is for the convenience of reading and compiling.
bloomFilter: uses a bool array to store encoded elements.
countingBloomFilter: uses an int array to store the amount of entries.
codedBloomFilters: uses several bloomFilters as bitwise encoded filters.

With the given input:
Output of bloomFilter is 1000 43, which means all 1000 original elements are found, and 43 mistakes are made finding 1000 new elements
Output of countingBloomFilter is 517, which means 517 of the 1000 original elements are found after deleting 500 and adding 500 new ones, with 17 mistakes.
Output of codedBloomFilter is 5785, which means 5785/7000 elements get their corrent set number.
