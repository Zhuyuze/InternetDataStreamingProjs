# Hash Tables

Environment: Windows, C++, Dev-Cpp

My class structure:

hashTable(interface) -- multiHashTable(Table Size, Num of Hashes)

                     |- cuckooHashTable(Table Size, Num of Hashes, Num of cuckoo steps)

                     |- dLeftHashTable(Table Size, Num of segments)

                    *|- cuckooDLeftHash(Table Size, Num of segments, Num of cuckoo steps)

All variables in parentheses, and number of input flows, size of hash table can be set in "main.cpp".

Implementations are in "multiHashTable.cpp", "cuckooHashTable.cpp", "dLeftHashTable.cpp", *"cuckooDLeftHash.cpp".


Fid is stored in table[entry][0] ,Counter is in table[entry][1].

Input is set as given, and can be changed in main.cpp

Execution will show the amount of entries are successfully inserted, and the amount of failures.

And output files are "multiHashTableOutput", "cuckooHashTableOutput", "dLeftHashTableOutput", *"cuckooDLeftHashTableOutput".

First line is number of Successful Insertions, and number of Occupied Entries.

(Note that "-1" represents NO Flow was Entered in this Table Entry.)


With the given input:

| | num of insertions | num of failures | num of occupied |
| --- | --- | --- | --- |
|MultiHash | 820 | 180 | 808 |

|CuckooHash | 924 | 76 | 918 |

|D-LeftHash | 884 | 116 | 871 |

|*Cuckoo&D-Left | 999 | 1 | 984 |

*: Combination of Cuckoo and D-Left, which is the best result.