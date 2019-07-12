with open('model.txt', 'r') as f:
	tmp = f.readline()
	with open('model_prime.txt', 'w') as out:
		out.write('207788 300\n')
		st = set()
		for s in f.readlines():
			lst = s.split()
			lst[0], t = lst[0].split('_')
			if lst[0] in st:
				continue
			st.add(lst[0])
			for x in lst:
				out.write(x + ' ')
			out.write('\n')
		print(len(st))
