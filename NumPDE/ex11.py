import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

nx = 200
x = np.linspace(0, 1, nx)
dx = x[1] - x[0]
c = 1.0
dt = 0.5 * dx / c
nt = 200

u_lf = np.where((x > 0.3) & (x < 0.6), -1.0, 0.0)
u_lw = u_lf.copy()

fig, ax = plt.subplots()
line_lf, = ax.plot(x, u_lf, label='Lax-Friedrichs')
line_lw, = ax.plot(x, u_lw, label='Lax-Wendroff')
line_init, = ax.plot(x, u_lf, 'k--', label='initial')

ax.set_ylim(-1.2, 1.2)
ax.legend()
ax.grid()

def update(frame):
    global u_lf, u_lw

    u_lf_new = u_lf.copy()
    u_lw_new = u_lw.copy()

    for j in range(nx):
        jp = (j + 1) % nx
        jm = (j - 1) % nx

        u_lf_new[j] = 0.5*(u_lf[jp] + u_lf[jm]) \
                      - 0.5*(c*dt/dx)*(u_lf[jp] - u_lf[jm])

        u_lw_new[j] = u_lw[j] \
                      - 0.5*(c*dt/dx)*(u_lw[jp] - u_lw[jm]) + \
                      0.5*(c*dt/dx)**2 * (u_lw[jp] - 2*u_lw[j] + u_lw[jm])

    u_lf = u_lf_new
    u_lw = u_lw_new

    line_lf.set_ydata(u_lf)
    line_lw.set_ydata(u_lw)

    return line_lf, line_lw

ani = FuncAnimation(fig, update, frames=nt, interval=50)

plt.show()