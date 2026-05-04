import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

a, b = -2, 2
dx = 0.02
dt = 0.01
T_e = 2

x = np.arange(a, b + dx, dx)

def u0(x):
    return np.where((x >= -1) & (x <= 1), 1.0, 0.0)

def u_exact(x, t):
    u = np.zeros_like(x)

    left = x < -1
    rare = (x >= -1) & (x <= -1 + t)
    middle = (x >= -1 + t) & (x <= 1 + 0.5*t)
    right = x > 1 + 0.5*t

    u[left] = 0
    u[rare] = (x[rare] + 1) / t
    u[middle] = 1
    u[right] = 0

    return u

u = u0(x)
t = 0

fig, ax = plt.subplots(figsize=(8, 4))
line_num, = ax.plot(x, u, label="Numerical")
line_exact, = ax.plot(x, u, '--', label="Exact")

ax.set_xlim(a, b)
ax.set_ylim(-0.2, 1.2)
ax.set_xlabel("x")
ax.set_ylabel("u")
ax.legend()
ax.grid()

time_text = ax.text(0.02, 0.9, '', transform=ax.transAxes)

def update(frame):
    global u, t

    v = np.zeros_like(u)

    for i in range(1, len(u)):
        v[i] = u[i] - dt/dx * (0.5*u[i]**2 - 0.5*u[i-1]**2)

    # periodic BC
    v[0] = u[0] - dt/dx * (0.5*u[0]**2 - 0.5*u[-1]**2)

    u = v.copy()
    t += dt

    # update plots
    line_num.set_ydata(u)
    line_exact.set_ydata(u_exact(x, t))

    time_text.set_text(f"t = {t:.2f}")

    return line_num, line_exact, time_text

frames = int(T_e / dt)

ani = FuncAnimation(fig, update, frames=frames, interval=30)

plt.show()