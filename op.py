import numpy as np
from scipy.integrate import solve_ivp
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Parameters
p = 5.0
c = 1.0
R = 2.0

def system(t, u0, p, c, R):
  
    x, y, z = u0

    dxdt = (
        p * (1.0 + z) * (1.0 - z - x ) * x**2
        - p * (1.0 - z) * ((1.0 - z - x )**2) * x
        - c * (1.0 - z) * x
        + z
    )

    dydt = (
        -p * (1.0 + z) * (1.0 - z - x ) * x**2
        + p * (1.0 - z) * ((1.0 - z - x )**2) * x
        + c * (1.0 - z) * x
        - R * z * (1.0 - z - x )
    )

    dzdt = R * z * (1.0 - z - x ) - z

    return [dxdt, dydt, dzdt]


t_span = (0.0, 300.0)        
t_eval = np.linspace(*t_span, 10000)  

initial_conditions = np.random.dirichlet([1, 1, 1], size=20)


figure = plt.figure(figsize=(10, 8))
ax = figure.add_subplot(111, projection='3d')
for ic in initial_conditions:
    sol = solve_ivp(system, t_span, ic, args=(p, c, R), t_eval=t_eval)
    ax.plot(sol.y[0], sol.y[1], sol.y[2], label=f'IC: {ic}')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')
ax.set_title('3D Trajectories in Opinion Space')
plt.show()

