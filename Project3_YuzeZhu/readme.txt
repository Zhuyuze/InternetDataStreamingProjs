Project 3
Yuze Zhu
UFID: 75087354
Environment: Windows, C++
My classes: countMin(number of arrays, number of counters in each array)
            counterSketch(number of arrays, number of counters in each array)
            activeCounter(). -Uses 2 unsigned short to store number and exponent.

All variables in parentheses, and input file name can be set in "main.cpp".
Implementations are all in "main.cpp", which is for the convenience of reading and compiling.
countMin: uses a 2-d array to store counters.
counterSketch: uses a 2-d array to store counters, and the leftmost bit of hash as sign to decide addition or subtraction.
activeCounter: Uses 2 unsigned short to store number and exponent with probability.

With the given input and not setting random seed:
Output of countMin is 125, which means the average mistake is 125.
Output of counterSketch is 600, which means the average mistake is 600.
Output of activeCounter is 996976 after 1000000 increases.

