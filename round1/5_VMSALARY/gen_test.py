"""
Testing scheme (20 tests):
- 2 example tests (hardcoded)
- 3 tests with N <= 100
- 3 tests that tree becomes a line, N random
- 8 tests with N in [1, 100000] and random tree
- 4 tests with N = 100000
"""

import random
import subprocess
import os

PATH = 'tests/'


def linear_tree(x):
    return x - 1


def random_tree(x):
    return random.randint(1, x - 1)


def low_N():
    return random.randint(1, 100)


def high_N():
    return random.randint(1, 100000)


def max_N():
    return 100000


def gen_random_data(tree_scheme, gen_N):
    N = gen_N()
    info = []

    for i in range(1, N + 1):
        if i > 1:
            pred = tree_scheme(i)
        else:
            pred = 0
        salary = random.randint(1, 10**9)
        info.append((pred, salary))
    return (N, info)


def write_test(id, data):
    print id
    N, info = data
    input_name = PATH + str(id) + ".in"
    with open(input_name, 'wb') as f:
        f.write("%d\n" % N)
        for i in range(len(info)):
            if i == 0:
                f.write("%d\n" % info[i][1])
            else:
                f.write("%d %d\n" % (info[i][0], info[i][1]))
        f.close()

    input_file_object = open(input_name, 'rb')
    output_name = PATH + str(id) + ".out"
    output_file_object = open(output_name, 'wb')
    os.system("./a.out " + "< " + input_name + " > " + output_name)


def gen_example():
    data_0 = (5, [(0, 3), (1, 2), (1, 2), (3, 2), (3, 1)])
    write_test(0, data_0)

    data_1 = (6, [(0, 4), (1, 2), (1, 5), (1, 3), (2, 1), (3, 6)])
    write_test(1, data_1)


def gen_buck(tree_scheme, gen_N, id_low, id_high):
    for i in range(id_low, id_high + 1):
        data = gen_random_data(tree_scheme, gen_N)
        write_test(i, data)

if __name__ == "__main__":
    print "Building solution"
    os.system("g++ soln.cpp -o a.out")
    print "Generating test cases"
    gen_example()
    gen_buck(random_tree, low_N, 2, 4)
    gen_buck(linear_tree, high_N, 5, 7)
    gen_buck(random_tree, high_N, 8, 15)
    gen_buck(random_tree, max_N, 16, 19)
