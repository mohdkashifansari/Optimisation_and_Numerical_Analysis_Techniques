import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import solve_bvp

def ode(t, y):

    x = y[0]
    lam = y[1]

    u = -lam

    dxdt = x + u
    dlamdt = -3*x - lam

    return np.vstack((dxdt, dlamdt))

def bc(ya, yb):

    return np.array([
        ya[0] - 1,
        yb[1]
    ])


t = np.linspace(0, 1, 100)

y_guess = np.zeros((2, t.size))

sol = solve_bvp(ode, bc, t, y_guess)

x = sol.y[0]
lam = sol.y[1]
u = -lam

plt.figure(figsize=(8,6))

plt.subplot(3,1,1)
plt.plot(sol.x, x)
plt.ylabel('x(t)')
plt.grid()

plt.subplot(3,1,2)
plt.plot(sol.x, lam)
plt.ylabel('lambda(t)')
plt.grid()

plt.subplot(3,1,3)
plt.plot(sol.x, u)
plt.ylabel('u(t)')
plt.xlabel('Time')
plt.grid()

plt.tight_layout()
plt.show()