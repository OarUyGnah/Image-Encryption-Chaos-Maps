import matplotlib
import pylab as pl
import math
import numpy as np
import matplotlib.pyplot as plt


#-------------------------------------------------------------#
# Initial condition
#-------------------------------------------------------------#

x0=0.2


# List of alpha's
alpha_list=np.linspace(0.1,0.9,81)

# List of N values (Total number of iterations=length of x)
x=range(2000)

# Index corresponding to alpha=0.5
mstart=(len(alpha_list)-1)/2

#-------------------------------------------------------------#
# Creating zero matrices
# I'm going to use columns to represent xN values for different alpha's
# Rows will be different xN values for N=0 to len(x)
#-------------------------------------------------------------#

z=np.zeros((len(x),len(alpha_list)))

for m in range(len(alpha_list)):
    z[0][m]=x0


#-------------------------------------------------------------#
#defining the function f(mu)
#-------------------------------------------------------------#
def fmu(x,alpha):
    if x<0.5:
        return 2*alpha*x
    else:
        return 2*alpha*(1-x)


#-------------------------------------------------------------#
# Constructing z-matrix, XN's in rows and columns corresponds to alpha values
#-------------------------------------------------------------#

for m in range(len(alpha_list)):
    for n in range(len(x)-1):
        z[n+1][m]= fmu(z[n][m],alpha_list[m])     


#-------------------------------------------------------------#
# Plotting
#-------------------------------------------------------------#

for m in range(mstart,len(alpha_list)):
    for n in range(1000,len(x)):
        plt.scatter(alpha_list[m],z[n][m],marker='s',facecolor='0.5',edgecolor='none')
        plt.hold(True) 

plt.xlabel('Alpha')
plt.ylabel('$X_N$')
plt.title('Tent Map')
plt.show()