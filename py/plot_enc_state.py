
import numpy as np
import matplotlib.pyplot as plt

col = (1,)
x0 = np.loadtxt("../build/backup/agent_0.log", usecols=col )

x1 = np.loadtxt("../build/backup/agent_1.log", usecols=col )

x2 = np.loadtxt("../build/backup/agent_2.log", usecols=col )

x3 = np.loadtxt("../build/backup/agent_3.log", usecols=col )

#avg = (x0 + x1 + x2 + x3)/4

t = np.arange(0, x0.size-1, 1)

plt.figure(1)


plt.plot(t, x0[1:], 'r', label='$\mathcal{E}_1(-x_1[k])$')
plt.plot(t, x1[1:], 'g', label='$\mathcal{E}_2(-x_2[k])$')
plt.plot(t, x2[1:], 'b', label='$\mathcal{E}_3(-x_3[k])$')
plt.plot(t, x3[1:], 'c', label='$\mathcal{E}_4(-x_4[k])$')
#plt.plot(t, avg, 'k--', label='Avg')

leg = plt.legend(loc='upper right', shadow=True)

plt.xlabel('Time Step')
plt.ylabel('Encrypted Negative State')
#plt.ylabel('Encrypted Negative State')

plt.show()