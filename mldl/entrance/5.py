import random

n = int(input())
ans = 0
for test in range(0, n):
	cur = 1
	while 1:
		if random.random() < 0.25:
			break
		cur += 1
	ans += cur / n
print(ans)