import numpy as np 
from scipy.interpolate import RectBivariateSpline, bisplrep
import matplotlib.pyplot as plt 

SZ = 2 * np.pi

x = np.linspace(0, SZ, 5)
y = np.linspace(0, SZ, 5)
(xx, yy) = np.meshgrid(x, y)

def z_func(x, y):
    return np.cos(x) + np.sin(y) ** 2 + 0.05 * x + 0.1 * y

zz = z_func(xx, yy)

points = np.column_stack((xx.flatten(), yy.flatten(), zz.flatten()))
np.savetxt("points.csv", points, delimiter=",", fmt="%f")
exit()

spline = RectBivariateSpline(x, y, zz)

x2 = np.linspace(0, SZ, 101)
y2 = np.linspace(0, SZ, 101)
z2 = spline(x2, y2)

X2, Y2 = np.meshgrid(x2, y2,)
fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X2, Y2, z2, cmap='viridis')
ax.set_xlabel('X axis')
ax.set_ylabel('Y axis')
ax.set_zlabel('Z axis')
plt.show()
