import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as anim

# Traffic Jam smoothing simulation
def get_parameters():
    mu = 1  # average speed
    a = 0.3  # jam amplitude
    m = 4  # wave number
    return mu, a, m

def u0(x):
    mu, a, m = get_parameters()
    return mu + a * np.sin(m * x)

def f(u):
    return u * (1 - u)

def LaxFriedrich(L, T, h, dt):
    # Parameters
    n = int(L / h) + 1
    m = int(T / dt)
    x = np.linspace(0, L, n)
    gamma = dt / h
    # Solutions
    ucurrent = u0(x)
    usolutions = [ucurrent.copy()]
    unext = np.zeros_like(ucurrent)
    
    for k in np.linspace(dt, T, m):
        # Update unext = uk+1
        for i in range(1, n - 1):
            unext[i] = (1/2) * (ucurrent[i - 1] + ucurrent[i + 1]) + gamma / 2 * (f(ucurrent[i + 1]) - f(ucurrent[i - 1]))
        
        # Periodic boundary conditions
        unext[0] = (1/2) * (ucurrent[-1] + ucurrent[1]) + gamma / 2 * (f(ucurrent[1]) - f(ucurrent[-1]))
        unext[-1] = (1/2) * (ucurrent[-2] + ucurrent[0]) + gamma / 2 * (f(ucurrent[0]) - f(ucurrent[-2]))
        
        usolutions.append(unext.copy())
        ucurrent = unext.copy()
    
    return x, usolutions

def animate(L, x, usolutions):
    fig, ax = plt.subplots()
    line, = ax.plot([], [], lw=2)
    mu, a, m = get_parameters()

    def init():
        ax.set_xlim(0, L)
        ax.set_ylim(mu - 2 * a, mu + 2 * a)
        ax.set_xlabel('x')
        ax.set_ylabel('u')
        ax.set_title('Burger\'s Traffic Equation - Lax Friedrich Scheme')
        return line,  # the comma is necessary here for the animation package

    def update(frame):
        line.set_data(x, usolutions[frame])
        return line,

    ani = anim.FuncAnimation(fig, update, frames=len(usolutions), init_func=init, blit=True)
    plt.grid(True)
    plt.show()

def animate_circular(L, x, usolutions, tau, speed=0.25):
    fig, ax = plt.subplots()
    line, = ax.plot([], [], lw=2)
    mu, a, m = get_parameters()

    def init():
        ax.set_xlim(-mu - 2 * a, mu + 2 * a)
        ax.set_ylim(-mu - 2 * a, mu + 2 * a)
        ax.set_xlabel('x')
        ax.set_ylabel('y')
        ax.set_title('Burger\'s Traffic Equation - Lax Friedrich Scheme')
        return line,

    def update(frame):
        theta = x / L * 2 * np.pi  # Convert x to angles in radians
        r = usolutions[frame]
        x_circle = r * np.cos(theta)
        y_circle = r * np.sin(theta)
        line.set_data(x_circle, y_circle)
        return line,

    interval = int(tau * 1000 / speed)
    ani = anim.FuncAnimation(fig, update, frames=len(usolutions), init_func=init, blit=True, interval=interval)
    plt.grid(True)
    plt.gca().set_aspect('equal', adjustable='box')
    plt.show()

L = 2 * np.pi
T = 5.0
h = 0.1
tau = 0.025
x, usolutions = LaxFriedrich(L, T, h, tau)
#animate(L, x, usolutions)
animate_circular(L, x, usolutions, tau)
