with open('model.txt', 'r') as f:
	tmp = f.readline()
	with open('model_prime.txt', 'w') as out:
		out.write('249565 300\n')
		for s in f.readlines():
			lst = s.split()
			lst[0] = lst[0].split('_')[0]
			for x in lst:
				out.write(x + ' ')
			out.write('\n')
