import numpy as np

a = np.array(range(1, 15*6+1))
for i in range(6):
  aa = a[15*i: 15*i+15]
  aa = aa.reshape((3, 5))
  b = np.array(range(1, 11))
  b = b.reshape((5, 2))
  print np.dot(aa, b)