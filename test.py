a = [64, 87, 50, 71, 44, 56, 42, 60]
b = [5, 2, 12, 9, 15, 6, 25, 16]
m = 0
s = 0
for i in range(8):
    m = m + a[i]
    s = s + b[i]
avg1 = m / 8.0
avg2 = s / 8.0
cov = 0
for i in range(8):
    c = (a[i] - avg1)*(b[i] - avg2)
    print(c)
    cov = cov + c
print(cov)
