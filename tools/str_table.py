import os, sys

"""
String Lookup Generator, for Btree.c

This works by taking an input string, for sorted ascii characters, and
giving them weight, based on the index of where they are in the string.
Then the remaining character spots are given an incremental value, from
the last weight + 1 onwards.

"""

def main():
    # In order string table
    table = '.\r\n _-\'"\\/|()[]{}@#$%^&*+=`~<>,?!0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'
    
    # Generate base list
    lst = [255 for i in range(0, 256)]
    
    # Add ascii character weights to lst
    x = 0
    for i in table:
        lst[ord(i)] = x
        x += 1
    
    # Go over lst, and add an incremental weight for each
    # remaining character location.
    for i in range(0, len(lst)):
        if lst[i] == 255:
            lst[i] = x
            x += 1
    
    # Generate C code
    out = 'char CE_BTREE_STRING_TABLE[] = {'
    for i in lst:
        out += str(i) + ', '
    out += '};'
    
    # Output
    print(out)
    
if __name__ == '__main__':
    main()
