import random

for test in range(5, 51, 5):
    n = str(test)
    # if (len(n) < 3):
    #     n = '0'*(3 - len(n)) + n

    graph_size = test
    possibility = 0.3

    matrix = [[0] * graph_size for _ in range(graph_size)]

    for i in range(graph_size):
        for j in range(i + 1, graph_size):
            if random.random() < possibility:  
                matrix[i][j] = 1
                matrix[j][i] = 1

    file_name = "./data/test_" + n + ".txt"
    with open(file_name, 'w') as f:
        f.write(str(graph_size) + '\n')
        for row in matrix:
            f.write(' '.join(str(i) for i in row) + '\n')
