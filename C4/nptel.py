count = 0
for i in range(1, 1001):
    if(i % 11 == 0 or i % 13 == 0):
        count += 1
print(count)
