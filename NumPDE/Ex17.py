import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

Nx = 400
L = 5
dx = L / Nx
x = np.linspace(0, L, Nx)

dt = 0.2 * dx
T = 1.0
Nt = int(T / dt)

p = L / 4
d0 = 0.3

d = np.ones(Nx)
d[x > p] = d0
u = np.zeros(Nx)

def step(d, u):
    d_new = np.copy(d)
    u_new = np.copy(u)

    f1 = d * u
    f2 = 0.5 * u**2 + d

    d_new[1:-1] = 0.5 * (d[2:] + d[:-2]) - (dt / (2 * dx)) * (f1[2:] - f1[:-2])
    u_new[1:-1] = 0.5 * (u[2:] + u[:-2]) - (dt / (2 * dx)) * (f2[2:] - f2[:-2])

    u_new[0] = 0
    d_new[0] = d_new[1]

    u_new[-1] = 0
    d_new[-1] = d_new[-2]

    return d_new, u_new

fig, ax = plt.subplots()
line1, = ax.plot(x, d, label="d")
line2, = ax.plot(x, u, label="u")
ax.set_ylim(-0.5, 1.5)
ax.legend()

def update(frame):
    global d, u
    d, u = step(d, u)
    line1.set_ydata(d)
    line2.set_ydata(u)
    ax.set_title(f"t = {frame*dt:.3f}")
    return line1, line2

ani = FuncAnimation(fig, update, frames=Nt, interval=30)

plt.show()