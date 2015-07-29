import os
import shutil

# Loop through the tests
for i in xrange(30, 60):
    print '--------------------'
    print "Processing test: {}".format(i)

    # Copy to input.txt
    ORIGINAL_FILE_PATH = "tests/{}.in".format(i)
    INPUT_PATH = 'input.txt'
    shutil.copyfile(ORIGINAL_FILE_PATH, INPUT_PATH)

    # Run all solutions
    SOLUTION_PATH = 'solutions'
    names = os.listdir(SOLUTION_PATH)

    best_value = 0
    for name in names:
        print "Running: {}".format(name)

        SOURCE_FILE = "{}/{}".format(SOLUTION_PATH, name)
        EXECUTABLE = 'cur'
        OUTPUT_PATH = 'output.txt'
        RESULT_PATH = 'output.sol'
        os.system("g++-4.9 {} -o {} --std=c++11".format(SOURCE_FILE, EXECUTABLE))
        os.system("gtimeout 3 ./{} < {} > {}".format(EXECUTABLE, INPUT_PATH, OUTPUT_PATH))

        os.system("./sol_linh_local < {} > {}".format(INPUT_PATH, RESULT_PATH))
        os.system("./judge")

        SCORE_PATH = 'result.txt'
        with open(SCORE_PATH, 'r') as f:
            lines = f.readlines()
            if len(lines) <= 1:
                continue
            score = float(lines[0])
            value = int(lines[1])
            if score > 0.0:
                best_value = max(best_value, value)

    print 'Result: {}'.format(best_value)
    with open("tests/{}.out".format(i), 'w') as f:
        f.write(str(best_value))
