#!/home/kikos/anaconda3/bin/python3
t = int(input())
for _ in range(t):
	n, a1 = map(int, input().split())
	a = [0] * (n + 1)
	a[1] = a1
	A = (2 ** n) * a1 * n
	B = (n * (2 ** (n - 1)) + 1)
	if not A % B == 0:
		print('-1')
		continue
	s = A // B
	if not s % n == 0:
		print('-1')
		continue
	bad = 0
	_r = s - a[1]
	for i in range(2, n + 1):
		l = 0
		r = _r
		while l + 1 < r:
			mid = (l + r) // 2
			x = (mid * 2 ** (i) - s) * 2 ** (n - i)
			if x < s // n:
				l = mid
			else:
				r = mid
		if not (r * 2 ** (i) - s) * 2 ** (n - i) == s // n:
			print('-1')
			bad = 1
			break
		a[i] = r
		_r -= r
	if bad:
		continue
	for i in range(1, n + 1):
		print(a[i], end = ' ')
	print()