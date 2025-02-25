import numpy as np
import matplotlib.pyplot as plt
from matplotlib.patches import Patch

# Define the vertices of the triangle
A = np.array([0, 0, 0])  # Vertex A
B = np.array([1, 0, 1])  # Vertex B
C = np.array([0, 1, 2])  # Vertex C

# Generate a structured grid of (u, v) values inside the triangle
num_points = 50  # Number of points along each axis
u = np.linspace(0, 1, num_points)
v = np.linspace(0, 1, num_points)
u, v = np.meshgrid(u, v)  # Create a grid of (u, v) values

# Ensure that the points lie within the triangle (u + v <= 1)
valid = u + v <= 1
u = u[valid]
v = v[valid]

# Compute the corresponding (x, y, z) points for the original surface
x_original = (1 - u - v) * A[0] + u * B[0] + v * C[0]
y_original = (1 - u - v) * A[1] + u * B[1] + v * C[1]
z_original = (1 - u - v) * A[2] + u * B[2] + v * C[2]

# Projection direction (z-axis projection)
n = np.array([0, 1, 0.5])
n_norm_sq = np.dot(n, n)  # Squared norm of n

# Compute dot product of (x_original, y_original, z_original) with n
dot_product = x_original * n[0] + y_original * n[1] + z_original * n[2]

# Project points onto the plane orthogonal to n
x_proj = x_original - (dot_product * n[0] / n_norm_sq)
y_proj = y_original - (dot_product * n[1] / n_norm_sq)
z_proj = z_original - (dot_product * n[2] / n_norm_sq)  # This will be constant

# Plot both the original and projected surfaces
fig = plt.figure()
ax = fig.add_subplot(111, projection="3d")

# Plot the original triangular surface
ax.plot_trisurf(
    x_original,
    y_original,
    z_original,
    color="red",
    edgecolor="k",
    alpha=0.6,
    label="Original Surface",
)

# Plot the projected triangular surface
ax.plot_trisurf(
    x_proj,
    y_proj,
    z_proj,
    color="cyan",
    edgecolor="k",
    alpha=0.6,
    label="Projected Surface",
)

# Create custom legend handles
original_patch = Patch(color="red", label="Original Surface")
projected_patch = Patch(color="cyan", label="Projected Surface")

# Add the legend
ax.legend(handles=[original_patch, projected_patch])

# Labels and view adjustments
ax.set_xlabel("X")
ax.set_ylabel("Y")
ax.set_zlabel("Z")
ax.set_title("Original and Projected Parametric Triangle Surfaces")
plt.show()
