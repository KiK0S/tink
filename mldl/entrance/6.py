import random
n = int(input())
ln = int(input())
p = float(input())
x = (1 - p) /p
print(x) 
ans = 0
random.seed()
for test in range(0, n):
	cur = 1
	cnt = 0
	while cur > 0:
		cnt += 1
		if random.random() <= p:
			cur += 1
		else:
			cur -= 1
		if cnt == ln:
			break
	if cur == 0:
		ans += 1
print(ans / n)