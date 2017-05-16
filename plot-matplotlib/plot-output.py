#!/usr/bin/env python

import numpy as np
import matplotlib.pyplot as plt

# read output
path_output = '../output/output_table.csv'

# read errors
path_output_error = '../output/errors.csv'

# open output
output_file = open(path_output, 'r')

# open errors file
error_file = open(path_output_error, 'r')

# use numpy to read file as list (array)
n, x, A, rho, v, T, p, M, mdot = np.loadtxt(path_output, unpack=True,
                                            skiprows=1, delimiter=',')
n_iter, err_rho, err_v, err_T = np.loadtxt(path_output_error, unpack=True,
                                           skiprows=1, delimiter=',')

# use matplotlib to visualize output data
plot_axis = [0, 3, 0, 1]


plt.plot(x, rho, 'ro')
plt.xlabel('x')
plt.ylabel(r'$\rho$')
plt.title('Density Distribution in Duct')
plt.grid(True)
plt.axis(plot_axis)
plt.savefig('plot-images/density-distribution.png', dpi=200)
plt.gcf().clear()
