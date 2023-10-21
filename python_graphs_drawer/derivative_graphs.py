import matplotlib.pyplot as plt
import csv
import numpy as np

N = [3, 4, 5]
dir = '/home/kirill/git_repozitories/COMPUT_MATH/graphs/derivative/test_derivative_N'


for n_i in N:
    
    Y = []
    X = []

    with open( dir + f'{n_i}.csv', 'r') as datafile:
        plotting = csv.reader(datafile, delimiter=';')
        
        for ROWS in plotting:
            Y.append(float(ROWS[1]))
            X.append(float(ROWS[0]))

    X = np.array(X)
    Y = np.array(Y)

    plt.plot(X, Y, label = f"N = {n_i}")
    plt.scatter(X, Y)

plt.legend()


plt.title('ln(err) = f(ln(step))')
plt.xlabel('ln(step)')
plt.ylabel('ln(err)')
plt.grid()

plt.savefig(dir + ".png")
plt.show()
plt.close()