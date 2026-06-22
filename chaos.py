import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from scipy.integrate import solve_ivp

R = 3.0
p = 1.05
c = 0.2
kick_strength = 0.08
kick_period = 25.0
relax_dt = 0.5
steps = 400

x0 = 0.5
z0 = 0.2
state = np.array([x0, z0])
trajectory = [state.copy()]

def sys(t, y):
    x, z = y
    dx = p * (1 - z) * (1 - x) * (x ** 2) - p * (1 + z) * x * ((1 - x) ** 2) + c * (1 - z) * (1 - x)
    dz = R * x * z * (1 - z) - z
    return [dx, dz]

for n in range(steps):
    state[0] += kick_strength * np.sin(2 * np.pi * n / 7)
    state[1] += kick_strength * np.cos(2 * np.pi * n / 11)

    sol = solve_ivp(
        sys,
        (0, kick_period),
        state,
        t_eval=np.arange(0, kick_period, relax_dt),
        method='RK45'
    )

    pts = np.vstack((sol.y[0], sol.y[1])).T
    trajectory.extend(pts)
    state = pts[-1]

trajectory = np.array(trajectory)

fig, ax = plt.subplots(figsize=(10, 6))
ax.set_xlim(np.min(trajectory[:, 0]) - 0.02, np.max(trajectory[:, 0]) + 0.02)
ax.set_ylim(np.min(trajectory[:, 1]) - 0.02, np.max(trajectory[:, 1]) + 0.02)
ax.set_xlabel('x')
ax.set_ylabel('z')
ax.set_title('Periodically Kicked Phase Space Dynamics')
ax.grid(True)

line, = ax.plot([], [], lw=1.5)
point, = ax.plot([], [], 'ro', markersize=4)

xdata = []
zdata = []

def init():
    line.set_data([], [])
    point.set_data([], [])
    return line, point

def update(frame):
    xdata.append(trajectory[frame, 0])
    zdata.append(trajectory[frame, 1])
    line.set_data(xdata, zdata)
    point.set_data([trajectory[frame, 0]], [trajectory[frame, 1]])
    return line, point

ani = FuncAnimation(
    fig,
    update,
    frames=len(trajectory),
    init_func=init,
    interval=10,
    blit=True
)

plt.show()
