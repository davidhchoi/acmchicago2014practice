#!/usr/bin/python
import sys
import random

T = 5
edges = set()
for tc in xrange(T):
  n = random.randint(1,100)
  for i in xrange(1,n):
    first = random.randint(0,i-1)
    edges.add((first, i))
    for j in xrange(i):
      if (random.choice((0,1))):
        if (random.choice((0,1))):
          edges.add((i,j))
        else:
          edges.add((j,i))
  m = len(edges)
  print n, m
  for i in xrange(n):
    print random.choice((0,1)),
  print ''
  for u,v in edges:
    print u,v

print 0,0
      

