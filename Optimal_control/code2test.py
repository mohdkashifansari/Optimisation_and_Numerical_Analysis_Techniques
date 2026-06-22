import numpy as np
import matplotlib.pyplot as plt

# Parameters (set these before running)
r = 0.3    # growth rate
M = 10     # carrying capacity
A = 1      # weight parameter
x0 = 1     # initial condition
T = 5      # final time

converged = -1

delta = 0.001
N = 1000

t = np.linspace(0, T, N + 1)
h = T / N

u_k = np.zeros(N + 1)
x_k = np.zeros(N + 1)
x_k[0] = x0
lambda_k = np.zeros(N + 1)

while converged < 0:
    u_kminus1 = u_k.copy()
    x_kminus1 = x_k.copy()
    lambda_kminus1 = lambda_k.copy()

    # Forward sweep (state equation)
    for i in range(N):
        k1 = r * (M - x_k[i]) - u_k[i] * x_k[i]
        k2 = r * (M - (x_k[i] + h/2 * k1)) - 0.5 * (u_k[i] + u_k[i+1]) * (x_k[i] + h/2 * k1)
        k3 = r * (M - (x_k[i] + h/2 * k2)) - 0.5 * (u_k[i] + u_k[i+1]) * (x_k[i] + h/2 * k2)
        k4 = r * (M - (x_k[i] + h * k3)) - u_k[i+1] * (x_k[i] + h * k3)

        x_k[i+1] = x_k[i] + (h / 6) * (k1 + 2*k2 + 2*k3 + k4)

    # Backward sweep (adjoint equation)
    for i in range(N):
        j = N - i

        k1 = -2 * A * x_k[j] + (u_k[j] + r) * lambda_k[j]
        k2 = -2 * A * 0.5 * (x_k[j] + x_k[j-1]) + (0.5 * (u_k[j] + u_k[j-1]) + r) * (lambda_k[j] - h/2 * k1)
        k3 = -2 * A * 0.5 * (x_k[j] + x_k[j-1]) + (0.5 * (u_k[j] + u_k[j-1]) + r) * (lambda_k[j] - h/2 * k2)
        k4 = -2 * A * x_k[j-1] + (u_k[j-1] + r) * (lambda_k[j] - h * k3)

        lambda_k[j-1] = lambda_k[j] - (h / 6) * (k1 + 2*k2 + 2*k3 + k4)

    # Control update
    u_temp = (lambda_k * x_k) / 2
    u_k = 0.5 * (u_temp + u_kminus1)

    # Convergence test
    tol_u = delta * np.sum(np.abs(u_k)) - np.sum(np.abs(u_kminus1 - u_k))
    tol_x = delta * np.sum(np.abs(x_k)) - np.sum(np.abs(x_kminus1 - x_k))
    tol_lambda = delta * np.sum(np.abs(lambda_k)) - np.sum(np.abs(lambda_kminus1 - lambda_k))

    converged = min(tol_u, tol_x, tol_lambda)

# Plotting
plt.figure()

plt.subplot(3, 1, 1)
plt.plot(t, x_k)
plt.xlabel('Time')
plt.ylabel('State')

plt.subplot(3, 1, 2)
plt.plot(t, lambda_k)
plt.xlabel('Time')
plt.ylabel('Adjoint')

plt.subplot(3, 1, 3)
plt.plot(t, u_k)
plt.xlabel('Time')
plt.ylabel('Control')

plt.tight_layout()
plt.show()
