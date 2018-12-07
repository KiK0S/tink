a, b, c ,d = map(int, input().split())
l = -1e9
r = 1e9
if a < 0:
	a *= -1
	b *= -1
	c *= -1
	d *= -1
for i in range(1000):
	mid = (l + r) / 2
	if a * mid ** 3 + b * mid ** 2 + c * mid + d >= 0:
		r = mid
	else:
		l = mid
print((r + l) / 2)