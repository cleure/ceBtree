import os, sys

f = open('files.txt', 'r')
files = []
for line in f:
    files.append('"' + line[0:-1] + '"')

print(', '.join(files))

