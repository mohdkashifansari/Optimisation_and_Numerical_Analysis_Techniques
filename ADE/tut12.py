import numpy as np
import matplotlib.pyplot as plt

c = 1.0  
beta = 1.0  
k = 1.0  

L = 5.
T = 10.

h = 0.5
dt = 0.5

n = int(2*L/h)+1
m = int(T/dt)

x = np.linspace(-L,L,n)
t = np.linspace(0, T, m)

def soln(t,x):
    return np.exp(-beta * k**2*t) * np.sin(k*(x-c*t))

# plot solution
plt.figure(figsize=(10, 6))
for i in range(len(t)):
    plt.plot(x, soln(t[i], x), label=f"t={t[i]:.1f}")
plt.xlabel("x")
plt.ylabel("u")
plt.title("Solution of the wave equation over time")
plt.legend()
plt.grid()
plt.savefig("plotx.png")
plt.close()
#plt.show()

# plot u vs t
plt.figure(figsize=(10, 6))
for i in range(len(x)):
    plt.plot(t, soln(t, x[i]), label=f"x={x[i]:.1f}")
plt.xlabel("t")
plt.ylabel("u")
plt.title("Solution of the wave equation over space")
plt.legend()
plt.grid()
plt.savefig("plott.png")
plt.close()
#plt.show()
