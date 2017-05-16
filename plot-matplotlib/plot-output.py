#!/usr/bin/env python

import numpy as np
import matplotlib.pyplot as plt
import os


# define function for plotting (only 1 graph per image)
def plot(x, y, marker, plot_label, xlabel, ylabel, axis, title, figname):
    plt.plot(x, y, marker, label=plot_label)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.title(title)
    plt.grid(True)
    plt.axis(axis)
    plt.legend(loc='upper right')
    plt.savefig('plot-images/' + figname + '.png', dpi=200)
    plt.gcf().clear()
    return

# iterate over file in output directory
main_path = '../output/'
for filename in os.listdir(main_path):
    # slice filename for plotting purpose
    add_figname = filename[6:filename.index('c') - 1]

    if filename.startswith('errors'):
        # define the path
        path_errors = main_path + filename

        # open file
        errors_file = open(path_errors, 'r')

        # use numpy to read file as list (array)
        n_iter, err_rho, err_v, err_T = np.loadtxt(errors_file, unpack=True,
                                                   skiprows=1, delimiter=',')

        # error rho
        plot(n_iter, err_rho, 'b--', r'error_$\rho$', 'iterations',
             r'error_$\rho$', [0, 2250, 0, 0.018],
             'Error (Continuity)', 'error-rho' + add_figname)

        # error v
        plot(n_iter, err_v, 'r--', 'error_v', 'iterations',
             'error_v', [0, 2250, 0, 0.018],
             'Error (Momentum)', 'error-v' + add_figname)

        # error T
        plot(n_iter, err_T, 'g--', 'error_T', 'iterations',
             'error_T', [0, 2250, 0, 0.025],
             'Error (Energy)', 'error-T' + add_figname)

        # plot the error trenline
        plot_axis_error = [0, 2250, 0, 0.012]

        # error all
        plt.plot(n_iter, err_rho, 'b--', label=r'error_$\rho$')
        plt.plot(n_iter, err_v, 'r--', label='error_v')
        plt.plot(n_iter, err_T, 'g--', label='error_T')
        plt.xlabel('n_iter')
        plt.ylabel('error')
        plt.title('Error (All)')
        plt.grid(True)
        plt.axis(plot_axis_error)
        plt.legend(loc='upper right')
        plt.savefig('plot-images/all-error' + add_figname + '.png', dpi=200)
        plt.gcf().clear()

    elif filename.startswith('output'):
        # define the path
        path_output = main_path + filename

        # open file
        output_file = open(path_output, 'r')

        # use numpy to read file as list (array)
        n, x, A, rho, v, T, p, M, mdot = np.loadtxt(output_file, unpack=True,
                                                    skiprows=1, delimiter=',')

        # rho
        plot(x, rho, 'k', r'$\rho$', 'x', r'$\rho$', [0, 3, 0, 1],
             'Density Distribution in Duct', 'density' + add_figname)

        # velocity
        plot(x, v, 'k', 'v', 'x', 'v', [0, 3, 0, 2.0],
             'Velocity Distribution in Duct', 'velocity' + add_figname)

        # temperature
        plot(x, T, 'k', 'T', 'x', 'T', [0, 3, 0, 1],
             'Temperature Distribution in Duct', 'temperature' + add_figname)

        # pressure
        plot(x, p, 'k', 'p', 'x', 'p', [0, 3, 0, 1],
             'Pressure Distribution in Duct', 'pressure' + add_figname)

        # mach
        plot(x, M, 'k', 'M', 'x', 'M', [0, 3, 0, 3.5],
             'Mach Distribution in Duct', 'mach' + add_figname)

        # mass-flow
        plot(x, mdot, 'k', 'mdot', 'x', 'mdot', [0, 3, 0, 1],
             'Mass Flow Distribution in Duct', 'mass-flow' + add_figname)

    else:
        print("Wrong file!")
