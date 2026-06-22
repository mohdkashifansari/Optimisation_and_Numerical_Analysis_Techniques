import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import solve_bvp

t = np.linspace(1, 5, 101)

def ode(t, y):
    x = y[0]
    lam = y[1]

    dxdt = 1.5 * x + 0.5 * lam
    dlamdt = 1.5 * x - 1.5 * lam

    return np.vstack((dxdt, dlamdt))


def bc(ya, yb):
    return np.array([
        ya[0] - 2,
        yb[1]
    ])

y_guess = np.zeros((2, t.size))
y_guess[0] = 2

sol = solve_bvp(ode, bc, t, y_guess)

x = sol.y[0]
lam = sol.y[1]
u = 0.5 * (x + lam)

plt.figure(figsize=(8,8))

plt.subplot(3,1,1)
plt.plot(sol.x, x)
plt.ylabel("x(t)")
plt.grid()

plt.subplot(3,1,2)
plt.plot(sol.x, lam)
plt.ylabel("lambda(t)")
plt.grid()

plt.subplot(3,1,3)
plt.plot(sol.x, u)
plt.ylabel("u(t)")
plt.xlabel("t")
plt.grid()

plt.tight_layout()
plt.show()

u_vals = u