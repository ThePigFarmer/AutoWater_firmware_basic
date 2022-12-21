#!/bin/python3

import json

def lines_in_file(f):
    with open(f, 'r') as f:
        for count, line in enumerate(f):
            pass
        return count


def parse_json_valves():
    with open('valves.json', 'r') as f:
         data = json.loads(f.read())
         return data

def index_line(line_to_index):
    line_count = lines_in_file('Water2/src/main.cpp') # get line count of file
    with open('Water2/src/main.cpp', 'r') as f: # Loop through file lines
        i = 0 
        while (i < line_count):
            line = f.readline(i)
            print(i,'.  ',line)
            i = i + 1

                
    
            

print(index_line(r'//!AutoWater_Valve_Init'))
    

# if line == line_to_index:
            #    return i

    #valves = parse_json_valves()
