maincpp = 'Water2/src/main.cpp' # code file to set

# open file
with open (maincpp, 'r') as f:

    # count lines in file
    for line_count, line in enumerate(f):
        pass

    for line in range(0, line_count):
        print(f.readline(line))

    print(f.readline(1))
    print(f.readline(2))
