"""
Testing scheme (20 tests):
- 2 example tests (hardcoded)
- 4 tests with N <= 1000
- 10 tests with N randomly chosen in [1, 100000]
- 4 tests with N = 100000
"""

import random
import subprocess
import os
import filecmp

PATH = 'tests/'
SANITY = 'sanity/'
OPTIMAL = 'sol_linh'
BRUTE_FORCE = 'brute_force'


def low_N():
    return random.randint(1, 1000)


def high_N():
    return random.randint(50000, 100000)


def max_N():
    return 100000


def gen_random_data(gen_N):
    N = gen_N()
    B = random.randint(1, 100000)

    info = []
    for i in range(N):
        a = random.randint(1, 100000)
        b = random.randint(1, 100000)
        c = random.randint(1, 100000)
        info.append((a, b, c))

    return ((N, B), info)


def gen_killer_data(gen_N):
    N = gen_N()
    B = 10 ** 5
    info = []
    info.append((random.randint(50000, 10**5), 1, 10 ** 5))
    for i in xrange(N-2):
        info.append((random.randint(50000, 10 ** 5), 1, 1))
    info.append((random.randint(50000, 10 ** 5), 1, 10 ** 5))
    return ((N, B), info)


def write_test(id, dest, data):
    (N, B), info = data
    input_name = dest + str(id) + ".in"
    with open(input_name, 'wb') as f:
        f.write("%d %d\n" % (N, B))
        for elt in info:
            f.write("%d %d %d\n" % (elt[0], elt[1], elt[2]))
        f.close()


def run_program(id, dest, program):
    """
    Return the output's full path
    """
    input_name = dest + str(id) + ".in"
    input_file_object = open(input_name, 'rb')

    output_extension = program
    if program == OPTIMAL:
        output_extension = ".out"

    output_name = dest + str(id) + output_extension
    output_file_object = open(output_name, 'wb')
    os.system("./" + program + " < " + input_name + " > " + output_name)
    return output_name


def gen_example():
    data_0 = ((2, 5), [(1, 4, 1), (2, 6, 1)])
    write_test(0, PATH, data_0)
    run_program(0, PATH, OPTIMAL)

    data_1 = ([2, 3], [(1, 1, 100), (2, 10, 1)])
    write_test(1, PATH, data_1)
    run_program(1, PATH, OPTIMAL)


def gen_buck(gen_N, dest, id_low, id_high, check=False):
    for i in range(id_low, id_high + 1):
        print i

        data = gen_random_data(gen_N)
        write_test(i, dest, data)
        output = run_program(i, dest, OPTIMAL)

        if check:
            bp_output = run_program(i, dest, BRUTE_FORCE)
            if not filecmp.cmp(output, bp_output):
                print "Error found in test generation"
                raise ValueError


def gen_killer(gen_N, dest, id_low, id_high, check=False):
    for i in range(id_low, id_high + 1):
        print i

        data = gen_killer_data(gen_N)
        write_test(i, dest, data)
        output = run_program(i, dest, OPTIMAL)

        if check:
            bp_output = run_program(i, dest, BRUTE_FORCE)
            if not filecmp.cmp(output, bp_output):
                print "Error found in test generation"
                raise ValueError


def sanity_check():
    gen_buck(low_N, SANITY, 0, 99, check=True)

if __name__ == "__main__":
    print "Building solution"
    os.system("g++-4.9 sol_rr.cpp -o " + OPTIMAL)
    os.system("g++-4.9 sol_linh_brute.cpp -o " + BRUTE_FORCE)
    # sanity_check()
    # os.system("rm -rf " + SANITY + "*")

    random.seed(7777);
    gen_example()
    gen_buck(low_N, PATH, 2, 4, True)
    gen_killer(low_N, PATH, 5, 5, True)
    gen_buck(high_N, PATH, 6, 15)
    gen_buck(high_N, PATH, 16, 16)
    gen_killer(high_N, PATH, 17, 19)
