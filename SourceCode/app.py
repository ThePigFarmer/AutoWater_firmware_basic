#!/bin/python3

import json

valves_file = r'valves.json'
mcu_file = r'Water2/src/main.cpp'

def lines_in_file(f):
    with open(f, 'r') as f:
        for count, line in enumerate(f):
            pass
        return count


def parse_json_valves():
    with open(valves_file, 'r') as f:
         data = json.loads(f.read())
         return data




#main -------------------------------------------------------------------------
with open(mcu_file, 'r') as f: # Loop through file lines
      
        i = 0 
        while (True):
            line = f.readline(i) 
            i = i + 1
            if line == line_to_index:
                
                return i
            elif i > lines_in_file('Water2/src/main.cpp'):
                x = False
                print('error')
                
    
            


print('lines in file
