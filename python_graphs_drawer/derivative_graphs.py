import matplotlib.pyplot as plt
import csv
import numpy as np

N = [3, 4, 5]
dir = '/home/kirill/git_repozitories/COMPUT_MATH/graphs/derivative/test_derivative_N'

lin_part_ind = [ 10, 7, 6]
colors = ['b', 'g', 'orange']

for i in range(len(N)):
    
    Y = []
    X = []

    with open( dir + '{}.csv'.format(N[i]), 'r') as datafile:
        plotting = csv.reader(datafile, delimiter=';')
        
        for ROWS in plotting:
            Y.append(float(ROWS[1]))
            X.append(float(ROWS[0]))

    X = np.array(X)
    Y = np.array(Y)

    x = X[0:lin_part_ind[i]]
    y = Y[0:lin_part_ind[i]]

    k = np.polyfit(x, y, 1)
    y = np.polyval(k, x)

    plt.plot(X, Y, ":",  label = "amount of points = {}, k = {:0.2f}".format(N[i], k[0]), color = colors[i])
    plt.plot(x, y, color = colors[i])

    plt.scatter(X, Y, color = colors[i])

plt.legend()


plt.title('ln(err) = f(ln(step))')
plt.xlabel('ln(step)')
plt.ylabel('ln(err)')
plt.grid()

plt.savefig(dir + ".png")
plt.show()
plt.close()