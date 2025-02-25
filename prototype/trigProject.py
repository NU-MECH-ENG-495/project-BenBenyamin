import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Define vectors B, C (3D points)
B = np.array([2, 1, 3])
C = np.array([1, 2, 1])

# Define a P that is a linear combination of B and C
u_true, v_true = 1.5, -0.5  # Example coefficients
P = u_true * B + v_true * C

# Construct matrix A
A = np.column_stack((B, C))  # 3x2 matrix

# Solve for (u, v) using (A^T A)^(-1) A^T P
uv_solution = np.linalg.inv(A.T @ A) @ (A.T @ P)
u, v = uv_solution

print(f"Computed values: u = {u:.4f}, v = {v:.4f}")
print(f"Original values: u = {u_true:.4f}, v = {v_true:.4f}")

# Plot the vectors in 3D
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Origin
origin = np.zeros(3)

# Plot vectors from the origin
ax.quiver(*origin, *B, color='r', label='B', linewidth=2)
ax.quiver(*origin, *C, color='g', label='C', linewidth=2)
ax.quiver(*origin, *P, color='b', label='P = uB + vC', linewidth=2)

# Draw lines from origin to B, C, and P
ax.plot([0, B[0]], [0, B[1]], [0, B[2]], 'r--')
ax.plot([0, C[0]], [0, C[1]], [0, C[2]], 'g--')
ax.plot([0, P[0]], [0, P[1]], [0, P[2]], 'b--')

# Show the linear combination explicitly (uB and vC contributions)
BC = u * B + v * C  # Should be equal to P
ax.quiver(*B, *(BC - B), color='purple', linestyle='dashed', label='uB')
ax.quiver(*C, *(BC - C), color='orange', linestyle='dashed', label='vC')

# Labels and legend
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.legend()
plt.title("Linear Combination of Vectors B and C to Form P")

plt.show()
