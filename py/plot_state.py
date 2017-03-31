
import numpy as np
import matplotlib.pyplot as plt

x0 = np.loadtxt("../build/agent_0.log", usecols=(0,))

x1 = np.loadtxt("../build/agent_1.log", usecols=(0,))

x2 = np.loadtxt("../build/agent_2.log", usecols=(0,))

x3 = np.loadtxt("../build/agent_3.log", usecols=(0,))

w0 = 0.1
w1 = 0.3
w2 = 0.2
w3 = 0.4
avg = (w0*x0 + w1*x1 + w2*x2 + w3*x3)

t = np.arange(0, x0.size, 1)

plt.figure(1)


plt.plot(t, x0, 'rx-', label='$x_1[k]$')
plt.plot(t, x1, 'g.-', label='$x_2[k]$')
plt.plot(t, x2, 'bx-', label='$x_3[k]$')
plt.plot(t, x3, 'c.-', label='$x_4[k]$')
plt.plot(t, avg, 'k--', label='Wt_Avg')

leg = plt.legend(loc='upper right', shadow=True)

plt.xlabel('Time Step')
plt.ylabel('State')

plt.show()
