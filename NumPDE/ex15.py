import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

L = 1.0
N = 200
dx = L / N
x = np.linspace(0, L, N)

T = 0.5
CFL = 0.8
dt = CFL * dx
Nt = int(T / dt)

a, b = 0.3, 0.7
u_a = 0.8
u_b = 0.2
u_0 = 0.5

def f(u):
    return u * (1 - u)

def initial_condition(x):
    u = np.zeros_like(x)
    for j in range(len(x)):
        if a <= x[j] <= b:
            u[j] = u_a + (u_b - u_a) * (x[j] - a) / (b - a)
        else:
            u[j] = u_0
    return u

u = initial_condition(x)

def step(u):
    return 0.5 * (np.roll(u, -1) + np.roll(u, 1)) \
           - (dt / (2 * dx)) * (f(np.roll(u, -1)) - f(np.roll(u, 1)))


fig, ax = plt.subplots()
line, = ax.plot(x, u, lw=2)

ax.set_xlim(0, L)
ax.set_ylim(0, 1)
ax.set_xlabel("x")
ax.set_ylabel("u")
ax.set_title("Traffic flow (Lax–Friedrichs)")

time = 0.0

def update(frame):
    global u, time
    u = step(u)
    time += dt
    
    line.set_ydata(u)
    ax.set_title(f"(Traffic flow)")
    return line,

ani = animation.FuncAnimation(
    fig,
    update,
    frames=Nt,
    interval=30,
    blit=True
)

plt.show()
