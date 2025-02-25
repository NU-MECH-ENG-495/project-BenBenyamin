import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.art3d import Poly3DCollection
from matplotlib.patches import Patch

# Define the vertices of the triangle in 3D space
A = np.array([0, 0, 0])  # Vertex A
B = np.array([1, 0, 1])  # Vertex B
C = np.array([0, 1, 2])  # Vertex C

# Define the normal vector of the projection plane
n = np.array([0, 0, 1])  # Normal vector (already normalized)
n = 1.0 * n / np.linalg.norm(n)  # Normalize the normal vector

# Function to project a 3D point onto a plane
def project_point_to_plane(point, plane_normal):
    """
    Projects a 3D point onto a plane defined by its normal vector.
    """
    # Projection formula: P_proj = P - (P · n) * n
    dot_product = np.dot(point, plane_normal)
    projection = point - dot_product * plane_normal
    return projection

# Project the triangle vertices onto the plane
A_proj = project_point_to_plane(A, n)
B_proj = project_point_to_plane(B, n)
C_proj = project_point_to_plane(C, n)

# Function to check if a 2D point lies on the projected plane
def is_point_on_plane(point_2d, triangle_vertices):
    """
    Checks if a 2D point lies on the plane defined by the projected triangle.
    """
    # Extract the projected triangle vertices
    A_proj, B_proj, C_proj = triangle_vertices

    # Compute the barycentric coordinates of the point
    def barycentric_coords(p, a, b, c):
        v0 = b - a
        v1 = c - a
        v2 = p - a
        d00 = np.dot(v0, v0)
        d01 = np.dot(v0, v1)
        d11 = np.dot(v1, v1)
        d20 = np.dot(v2, v0)
        d21 = np.dot(v2, v1)
        denom = d00 * d11 - d01 * d01
        v = (d11 * d20 - d01 * d21) / denom
        w = (d00 * d21 - d01 * d20) / denom
        u = 1.0 - v - w
        return u, v, w

    u, v, w = barycentric_coords(point_2d, A_proj[:2], B_proj[:2], C_proj[:2])

    # Check if the point lies inside the triangle
    return u >= 0 and v >= 0 and w >= 0

# Example: Check if a 2D point lies on the projected plane
point_2d = np.array([0.5, 0.5])  # Example 2D point

if is_point_on_plane(point_2d, (A_proj, B_proj, C_proj)):
    print(f"The point {point_2d} lies on the projected plane.")
else:
    print(f"The point {point_2d} does not lie on the projected plane.")

# Convert the 2D point to 3D by assuming it lies on the projection plane
point_3d = np.array([point_2d[0], point_2d[1], 0])  # z = 0 because projection plane is XY

# Plot the original and projected triangles
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Plot the original triangle
original_triangle = np.array([A, B, C])
original_poly = Poly3DCollection([original_triangle], color='blue', alpha=0.5)
ax.add_collection3d(original_poly)

# Plot the projected triangle
projected_triangle = np.array([A_proj, B_proj, C_proj])
projected_poly = Poly3DCollection([projected_triangle], color='red', alpha=0.5)
ax.add_collection3d(projected_poly)

# Plot the 2D point projected onto the 3D plane
ax.scatter(point_3d[0], point_3d[1], point_3d[2], color='green', s=100, marker='x', label='Projected Point')

# Create custom legend handles
original_patch = Patch(color='blue', label='Original Triangle')
projected_patch = Patch(color='red', label='Projected Triangle')

# Add the legend
ax.legend(handles=[original_patch, projected_patch])

# Set plot limits and labels
ax.set_xlim([-1, 2])
ax.set_ylim([-1, 2])
ax.set_zlim([-1, 3])
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

plt.show()
