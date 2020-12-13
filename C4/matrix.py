import numpy as np

a = np.array([[0, 1, 0, 1, 0, 1], [0, 0, 0, 0, 0, 0, ], [0, 1, 0, 1, 0, 1], [
             0, 0, 0, 0, 0, 0, ], [0, 1, 0, 1, 0, 1], [0, 0, 0, 0, 0, 0, ]])
u = np.array([[1], [1], [1], [1], [1], [1]])

at = np.transpose(a)
a1 = np.matmul(np.transpose(a), u)
h1 = np.matmul(a, a1)
a2 = np.matmul(at, h1)
h2 = np.matmul(a, a2)

print(a2)
print(h2)
