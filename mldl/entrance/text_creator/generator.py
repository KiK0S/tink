import pickle
import random
import learner

class generator:
	def __init__(self):
		pass

	def load(self):
		with open('data_calc', 'rb') as f:
			self.freq = pickle.load(f)
		self.all = sum(self.freq.values())
		print('data = ' + str(self.freq))
		print('sum = ' + str(self.all))

	def gen(self, n=20):
		s = ""
		for i in range(n):
			prob = random.random()
			prob *= self.all
			# prob = int(prob)
			print(prob)
			for val in self.freq:
				if self.freq[val] >= prob:
					s += val + ' '
					break
				else:
					prob -= self.freq[val]
		print(s)

obj = generator()
obj.load()
obj.gen()