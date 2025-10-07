#!/bin/python3

import math
import os
import random
import re
import sys



#
# Complete the 'isAnagram' function below.
#
# The function is expected to return an INTEGER.
# The function accepts following parameters:
#  1. STRING s
#  2. STRING t
#

def isAnagram(s, t):
    frequency = {} #dicionario
    frequency2 = {}
    
    for c in s:
        if c in frequency: 
            frequency[c] += 1
        else:
            frequency[c] = 1
            
    for k in t:
        if k in frequency2: 
            frequency2[k] += 1
        else:
            frequency2[k] = 1
            
    for i in frequency:
        if frequency2.get(i,0) != frequency[i]:
            return 0
     
     
    return 1   

if __name__ == '__main__':
    s = input()

    t = input()

    result = isAnagram(s, t)

    print(result)
