
import numpy as np
import matplotlib.pyplot as plt

x0 = np.loadtxt("../build/agent_0.log", usecols=(0,))

x1 = np.loadtxt("../build/agent_1.log", usecols=(0,))

x2 = np.loadtxt("../build/agent_2.log", usecols=(0,))

x3 = np.loadtxt("../build/agent_3.log", usecols=(0,))

#avg = (x0 + x1 + x2 + x3)/4

t = np.arange(0, x0.size, 1)

plt.figure(1)


plt.plot(t, x0, 'r', label='$\Delta x_{12}[k]$')
plt.plot(t, x1, 'g', label='$\Delta x_{23}[k]$')
plt.plot(t, x2, 'b', label='$\Delta x_{34}[k]$')
plt.plot(t, x3, 'c', label='$\Delta x_{41}[k]$')
#plt.plot(t, avg, 'k--', label='Avg')

leg = plt.legend(loc='upper right', shadow=True)

plt.xlabel('Time Step')
plt.ylabel('Encrypted Diff. State')

plt.show()