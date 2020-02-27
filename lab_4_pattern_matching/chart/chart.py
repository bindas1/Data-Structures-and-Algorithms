#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Dec 08 14:25:02 2019

@author: bindas
"""

import matplotlib.pyplot as plt
import pandas as pd

# 5 letter key
name5 = [10005,100005,1000005,10000005]
# 15 letter key
name15 = [10015,100015,1000015,10000015]


def chart(name, filename):
    force = []
    kmp = []
    try:
        with open(filename) as f:
            lines = f.readlines()
    except EnvironmentError:
        print('bad')
        
    #5key
    lines = [x.strip() for x in lines]
    for i, line in enumerate(lines):
        if i < 4:
            force.append(int(line))
        else:
            kmp.append(int(line))
    
    plt.title("Porownanie Brute force search z KMP search")
    plt.plot(name, force, label = 'force')
    plt.plot(name, kmp, label = 'kmp')
    
    plt.xlabel('liczba elementow + liczba liter w kodzie')
    plt.ylabel('liczba spr')
    plt.legend()
    
    plt.show()

#15 key
chart(name5, "results.txt")
chart(name15, "results.txt")
