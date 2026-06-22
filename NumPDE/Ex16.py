import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

Nx = 400
x_min, x_max = -1, 1
dx = (x_max - x_min)/Nx
x = np.linspace(x_min, x_max, Nx)

dt = 0.4 * dx / 2  
T = 0.5
Nt = int(T/dt)

u = np.zeros(Nx)
u[x < 0] = 1

def f(u):
    return u**2 / (u**2 + 0.5*(1-u)**2)

fig, ax = plt.subplots()
line, = ax.plot(x, u)
ax.set_ylim(-0.1, 1.1)
ax.set_xlabel("x")
ax.set_ylabel("u")
ax.set_title("Buckley–Leverett (Lax–Friedrichs)")

def step(u):
    u_new = np.copy(u)
    for i in range(1, Nx-1):
        u_new[i] = 0.5*(u[i+1] + u[i-1]) \
                   - (dt/(2*dx))*(f(u[i+1]) - f(u[i-1]))
    return u_new

def update(frame):
    global u
    u = step(u)
    line.set_ydata(u)
    ax.set_title(f"t = {frame*dt:.3f}")
    return line,

ani = FuncAnimation(fig, update, frames=Nt, interval=30)

plt.show()