import itertools

a = [1, 2, 3, 4]

b = set(itertools.permutations(a))

print(len(b))

ans = 0

for i in b:
	for j in b:
		for k in b:
			for z in b:
				flag = False
				for id in range(4):
					if (i[id] != j[id] and i[id] != k[id]
					and i[id] != z[id] and j[id] != k[id]
					and j[id] != z[id] and k[id] != z[id]):
						flag = False
					else:
						flag = True
				if(flag == False):
					ans += 1
print(ans)