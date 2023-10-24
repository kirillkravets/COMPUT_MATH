import matplotlib.pyplot as plt
import csv
import numpy as np

dir = "/home/kirill/git_repozitories/COMPUT_MATH/graphs/spline/test_spline.csv"


Y = []
X = []

with open( dir, 'r') as datafile:
    plotting = csv.reader(datafile, delimiter=';')
    
    for ROWS in plotting:
        Y.append(float(ROWS[1]))
        X.append(float(ROWS[0]))

X = np.array(X)
Y = np.array(Y)

k = np.polyfit(X, Y, 1)
Yth = np.polyval(k, X)

plt.plot(X, Yth, ":",  label = "k = {}".format(k[0]))
plt.scatter(X, Y)


plt.legend()


plt.title('ln(err) = f(ln(N))')
plt.xlabel('ln(step)')
plt.ylabel('ln(N)')
plt.grid()

plt.savefig(dir + ".png")
plt.show()
plt.close()