import matplotlib.pyplot as plt
import csv
import numpy as np

N = [3, 4, 5]
dirs = [ '/home/kirill/Вычматы 2023/graphs/test_graph_uniform_grid_N',\
         '/home/kirill/Вычматы 2023/graphs/test_graph_chebyshev_grid_N'  ]

for dir in dirs:

    for n_i in N:
        
        X = []
        Y = []

        with open( dir + f'{n_i}.csv', 'r') as datafile:
            plotting = csv.reader(datafile, delimiter=';')
            
            for ROWS in plotting:
                X.append(float(ROWS[1]))
                Y.append(float(ROWS[0]))

        X = np.log(np.array(X))
        Y = np.log(np.array(Y))

        plt.plot(X, Y, label = f"N = {n_i}")
        plt.scatter(X, Y)

    plt.legend()


    plt.title('ln(err) = f(ln(length))')
    plt.xlabel('ln(length)')
    plt.ylabel('ln(err)')
    plt.grid()

    plt.savefig(dir + ".png")
    plt.show()
    plt.close()