
import numpy as np
import matplotlib.pyplot as plt

x0 = np.loadtxt("../build/agent_0.log", usecols=(2,))

x1 = np.loadtxt("../build/agent_1.log", usecols=(2,))

x2 = np.loadtxt("../build/agent_2.log", usecols=(2,))

x3 = np.loadtxt("../build/agent_3.log", usecols=(2,))

avg = (x0 + x1 + x2 + x3)/4

t = np.arange(0, x0.size, 1)

plt.figure(1)


plt.plot(t, x0, 'rx-', label='$x_1[k]$')
plt.plot(t, x1, 'g.-', label='$x_2[k]$')
plt.plot(t, x2, 'bx-', label='$x_3[k]$')
plt.plot(t, x3, 'c.-', label='$x_4[k]$')
plt.plot(t, avg, 'k--', label='Avg')

leg = plt.legend(loc='upper right', shadow=True)

plt.xlabel('Time Step')
plt.ylabel('State')

plt.show()