#include "lib/testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int NTEST = 10;

string get_input_file(int test_id) {
    stringstream ss; ss << "tests/" << test_id << ".in";
    return ss.str();
}

string get_output_file(int test_id) {
    stringstream ss; ss << "tests/" << test_id << ".out";
    return ss.str();
}

void gen(int test_id, int bound) {
    cerr << "Generating test: " << test_id << endl;

    string in_file = get_input_file(test_id);
    fstream fout(in_file, fstream :: out);
    for(int i = bound - NTEST + 1; i <= bound; ++i)
        fout << i << endl;
    fout.close();

    system(("./sol_rr << " + in_file + " >> " + get_output_file(test_id)).c_str());
}

int main() {
    rnd.setSeed(7777);
    system("mkdir tests");

    gen(0, 100);
    gen(1, 1000);

    gen(2, 10000);
    gen(3, 20000);
    gen(4, 50000);
    gen(5, 80000);
    gen(6, 100000);
    gen(7, 400000);
    gen(8, 900000);
    gen(9, 1000000);
}

