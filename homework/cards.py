#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Dec  7 19:39:00 2019

@author: bindas
"""
import itertools
import random

def isbigger(a, b):
    if numbers_dict[a[1]]>numbers_dict[b[1]]:
        return True
    elif numbers_dict[a[1]]==numbers_dict[b[1]]:
        return colors_dict[a[0]] > colors_dict[b[0]]
    else:
        return False

colors = ['S','H','D','C']
numbers = ['2','3','4','5','6','7','8','9','10', 'Jack', 'Queen', 'King', 'Ace']
colors_dict = {'S':1,'H':2,'D':3,'C':4}
numbers_dict = {'2':2,'3':3,'4':4,'5':5,'6':6,'7':7,'8':8,'9':9,'10':10, 'Jack':11, 'Queen':12, 'King':13, 'Ace':14}

cards = [card for card in itertools.product(colors, numbers)]
random.shuffle(cards)
print("Before sorting")
print(cards[:10])

deck = len(cards)
for i in range(deck):
    max_ind = 0;
    for j in range(deck-i):
        if isbigger(cards[j], cards[max_ind]):
            max_ind = j
    cards[j], cards[max_ind] = cards[max_ind], cards[j]
    
print("After sorting")
print(cards[:10])

        