lst = [1, 3, 7, 9, 21, 27, 49, 63, 77, 81, 147, 189, 243, 297, 343, 369, 441, 567, 729, 903, 1029, 1323, 1617, 1631, 1701, 2009, 2037, 2043, 2187, 2401, 2597, 2709, 3087, 3969, 5103, 6237, 6321, 6561, 7203, 8001, 8127, 9261, 10209, 11907, 13203, 15309, 15477, 16659, 16807, 18963, 19341, 19683, 21609, 24003, 24057, 24381, 27783, 29889, 33957, 35721, 37931, 38829, 39447, 39609, 44247]
# def pw(x, mod, n):
# 	if n == 0:
# 		return 1
# 	if n % 2 == 0:
# 		return pw((x * x) % mod, mod, n // 2)
# 	return (x * pw(x, mod, n - 1)) % mod
# for i in range(1, 10 ** 8):
# 	x = 1 + pw(2, i, i) + pw(3, i, i) + pw(4, i, i) + pw(5, i, i) + pw(6, i, i)
# 	if x % i == 0:
# 		lst.append(i)
# 		print(i)
# 		if len(lst) >= 65:
# 			break
n = int(input())
print(lst[n-1])