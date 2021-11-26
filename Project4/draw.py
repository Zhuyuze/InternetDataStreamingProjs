import numpy as np
import matplotlib.pyplot as plt
with open('data.txt') as f:
    lines = f.readlines()
    x = [int(line.split()[0]) for line in lines]
    y = [int(line.split()[1]) for line in lines]
plt.plot(x, y, '+')
plt.xlabel('Actual')
plt.ylabel('Estimated')
plt.plot([0,500], [0,500], 'r')
plt.show()