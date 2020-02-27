#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Nov 11 14:25:02 2019

@author: bindas
"""

import matplotlib.pyplot as plt
import pandas as pd

i = 0
name = []
treemap = []
defmap = []

try:
    with open("results2.txt") as f:
        lines = f.readlines()
except EnvironmentError:
    print('bad')

lines = [x.strip() for x in lines]
for line in lines:
    if i%3 == 0:
        name.append(line)
    elif i%3 == 1:
        treemap.append(int(line))
    else:
        defmap.append(int(line))
    i += 1

plt.plot(name, treemap, label = 'treemap')
plt.plot(name, defmap, label = 'defmap')

plt.xlabel('liczba elementow')
plt.ylabel('liczba spr')
plt.legend()

plt.show()

df=pd.DataFrame({'name': name, 'treemap': treemap, 'defmap': defmap })

plt.figure()
plt.title('Porownanie map')
plt.plot('name', 'treemap', data=df, marker='o', label = 'treemap')
plt.plot('name', 'defmap', data=df, marker='o', label = 'defmap')

plt.xlabel('liczba elementow')
plt.ylabel('liczba spr')
plt.legend()

plt.show()
#contacs