"""
Testing scheme: 100 tests
- 10 tests with N <= 50, allowing for optimal solution by brute force
- 20 tests with N in [51, 200] with density 0.5
- 40 tests with N in [51, 200] with varying density
- 30 tests with N = 200, with varying density
"""
import random
PATH = "tests/"


def gen_random_graph(min_vertex_bound, max_vertex_bound, density=0.5):
    """
        Generate a random graph with:
        - Number of vertices in [min_vertex_bound, max_vertex_bound]
        - Density specifies the probability a certain pair (i, j) forms an edge
    """
    N = random.randint(min_vertex_bound, max_vertex_bound)
    edges = []
    for i in xrange(N):
        for j in range(i + 1, N):
            if random.random() < density:
                edges.append((i + 1, j + 1))
    return (N, edges)


def write_test(id, data):
    print id
    (N, edges) = data
    M = len(edges)

    file_name = PATH + str(id) + '.in'

    f = open(file_name, 'wb')
    f.write("%d %d\n" % (N, M))
    for elt in edges:
        f.write("%d %d\n" % (elt[0], elt[1]))
    f.close()


def gen_low_bound():
    return (1, 50)


def gen_high_bound():
    return (51, 200)


def gen_max_bound():
    return (200, 200)


def gen_uniform_density():
    return 0.5


def gen_random_density():
    return random.random()


def gen_test_scheme(gen_bound, gen_density, id_low, id_high):
    for i in range(id_low, id_high + 1):
        low_bound, high_bound = gen_bound()
        density = gen_density()

        data = gen_random_graph(low_bound, high_bound, density)
        write_test(i, data)

if __name__ == "__main__":
    gen_test_scheme(gen_low_bound, gen_random_density, 0, 9)
    gen_test_scheme(gen_high_bound, gen_uniform_density, 10, 29)
    gen_test_scheme(gen_high_bound, gen_random_density, 30, 69)
    gen_test_scheme(gen_max_bound, gen_random_density, 70, 99)
