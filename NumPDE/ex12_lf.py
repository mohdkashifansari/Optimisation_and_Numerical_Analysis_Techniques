import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

a, b = -2, 2
dx = 0.02
dt = 0.01
T_e = 2

x = np.arange(a, b + dx, dx)

def u0(x):
    return np.where((x >= -1) & (x <= 1), -1.0, 0.0)

def u_exact(x, t):
    u = np.zeros_like(x)

    if t == 0:
        return u0(x)

    left = x < -1 - 0.5*t
    middle = (x >= -1 - 0.5*t) & (x <= 1 - t)
    rare = (x >= 1 - t) & (x <= 1)
    right = x > 1

    u[left] = 0
    u[middle] = -1
    u[rare] = (x[rare] - 1) / t
    u[right] = 0

    return u

u = u0(x)
t = 0

fig, ax = plt.subplots(figsize=(8, 4))
line_num, = ax.plot(x, u, label="Lax-Friedrichs")
line_exact, = ax.plot(x, u, '--', label="Exact")

ax.set_xlim(a, b)
ax.set_ylim(-1.2, 0.2)
ax.set_xlabel("x")
ax.set_ylabel("u")
ax.legend()
ax.grid()

time_text = ax.text(0.02, 0.9, '', transform=ax.transAxes)

def update(frame):
    global u, t

    u_new = np.zeros_like(u)

    for i in range(len(u)):
        ip = (i + 1) % len(u)
        im = (i - 1) % len(u)

        u_new[i] = 0.5*(u[ip] + u[im]) \
                   - dt/(2*dx) * (0.5*u[ip]**2 - 0.5*u[im]**2)

    u = u_new
    t += dt

    line_num.set_ydata(u)
    line_exact.set_ydata(u_exact(x, t))
    time_text.set_text(f"t = {t:.2f}")

    return line_num, line_exact, time_text

frames = int(T_e / dt)
ani = FuncAnimation(fig, update, frames=frames, interval=30)

plt.show()