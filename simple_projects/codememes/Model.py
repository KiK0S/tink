import gensim
import random
import itertools
import logging
from math import exp, log2
from sklearn.utils.extmath import softmax
from gensim.models.keyedvectors import KeyedVectors
from Levenshtein import distance as levenshtein_distance
import json
import emoji

with open('secret_data', 'r') as f:
	secret_data = json.load(f)
PROFITS = secret_data['PROFITS']
CAN_GUESS_THRESHOLD = secret_data['CAN_GUESS_THRESHOLD']
model = KeyedVectors.load_word2vec_format('model_prime.txt')
MULTIPLY_EXP = secret_data['MULTIPLY_EXP']

def get_emoji(s):
	if s == 'r':
		return emoji.emojize(':red_circle:')

	if s == 'w':
		return emoji.emojize(':white_circle:')

	if s == 'b':
		return emoji.emojize(':blue_circle:')
	if s == 'd':
		return emoji.emojize(':black_circle:')

class Word:
	def __init__(self):
		self.word = ''
		self.marker = ''
		self.used = False
	
	def __init__(self, s, marker=''):
		self.word = s.lower().replace('\xad', '').replace('ё', 'е')
		self.marker = marker
		self.used = False
	
	def __repr__(self):
		if self.used:
			return self.word + get_emoji(self.marker)
		return self.word
	
	def make_random(self):
		self.cnt = 0
		self.dict = {}
	
	def calc_profit(self):
		self.profit = 0
		if self.cnt == 0:
			return
		for a, b in PROFITS.items():
			if not a in self.dict:
				self.dict[a] = 0
			self.profit += (self.dict[a] / self.cnt) * b

class Field:
	def __init__(self):
		self.current = 0
		self.n = 25
		self.all = []
	
	def __iter__(self):
		self.current = 0
		return self
	
	def __next__(self):
		if self.current == self.n:
			raise StopIteration
		result = self.all[self.current]
		self.current += 1
		return result

	def __len__(self):
		return len(self.all)
	
	def gen(self):
		with open('words.txt') as f:
			wordlist = f.readline().split()
			wordlist = [x for x in wordlist]
			markers = ['r'] * 9 + ['b'] * 8 + ['d'] * 1 + ['w'] * 7
			self.all = [Word(x, y) for x, y in zip(random.sample(wordlist, self.n), markers)]
		random.shuffle(self.all)
	
	def game_over(self):
		ok_r = False
		for s in self:
			if s.used:
				continue
			if s.marker == 'r':
				ok_r = True
		ok_b = False
		for s in self:
			if s.used:
				continue
			if s.marker == 'b':
				ok_b = True
		ok_d = True
		for s in self:
			if s.marker == 'd' and s.used:
				ok_d = False
		return (not ok_r) or (not ok_b) or (not ok_d)
	
	def print_without_markers(self):
		res = ''
		for s in self:
			if s.used:
				res += '<b>'
			res += s.word
			if s.used:
				res += '_' + s.marker
			if s.used:
				res += '</b>'
			res += '\n'
		return res

	def print_with_markers(self):
		res = ''
		for s in self:
			res += s.word + get_emoji(s.marker) + '\n'
		return res
	
	def __repr__(self):
		res = ''
		for s in self:
			res += str(s) + '\n'
		return res

	def unused(self):
		cnt = 0
		for s in self:
			if not s.used:
				cnt += 1
		return cnt

def similar_list(wordlist):
	if len(wordlist) == 0:
		return []
	return model.most_similar(positive=wordlist)

LEVENSHTEIN_THRESHOLD = 4
def filtered_similars(wordlist, forbidden):
	unfiltered = similar_list(wordlist)
	result = []
	for s, dist in unfiltered:
		ok = True
		for parent in forbidden:
			if levenshtein_distance(parent, s) <= LEVENSHTEIN_THRESHOLD or parent in s:
				ok = False
		if ok:
			result.append((s, dist))
	return result

def query(wordlist, forbidden):
	return filtered_similars(wordlist, forbidden)

def find_candidates(field, marker='r'):
	good_words = [x.word for x in field if x.marker == marker and x.used == False]
	result = set()
	for i in range(1, len(good_words) + 1):
		for lists in [query(_, [x.word for x in field]) for _ in list(itertools.combinations(good_words, i))]:
			for value in lists:
				result.add(value[0])
	return result

def scaling(x):
	return exp(x * MULTIPLY_EXP)


def guess(field, word, top_n=-1):
	pairs = []
	random_word = Word('', 'random')
	random_word.make_random()
	try:
		for item in field:
			if item.used:
				continue
			val = scaling(model.similarity(word, item.word))
			if val > scaling(CAN_GUESS_THRESHOLD) or top_n == -1:
				pairs.append((val, item))
			else:
				random_word.cnt += 1
				if not item.marker in random_word.dict:
					random_word.dict[item.marker] = 0
				random_word.dict[item.marker] += 1
		random_word.calc_profit()
		if top_n != -1:
			result = [(b, a) for a, b in sorted(pairs)[::-1]]
			while len(result) < top_n:
				result.append((random_word, scaling(CAN_GUESS_THRESHOLD)))
			return result
		else:
			return sorted(pairs)[::-1]
	except:
		pairs = []
		for item in field:
			if item.used:
				continue
			pairs.append(item)
		random.shuffle(pairs)
		return pairs

def calc_profit(wordlist, marker, coefficients):
	result = 0
	current_iter = 1
	for x, y in zip(wordlist, coefficients):
		if x.marker == 'random':
			result += x.profit * y / log2(current_iter + 1)
		else:
			result += PROFITS[x.marker] * y / log2(current_iter + 1)
		current_iter += 1
	return result

def bruteforce(game, marker):
	field = game.field
	candidates = find_candidates(field, marker)
	logging.info('{GAME = ' + str(game.chat_id) + ' CANDIDATES = \n' + str(candidates) + '}')
	all_moves = []
	for number in range(1, field.unused() + 1):
		for word in candidates:
			guessed = guess(field, word, number)
			logging.debug('{GAME = ' + str(game.chat_id) + ' TRY_MOVE = \n' + str(field) + ' ' + str(word) + ' ' + str(number) + '}')
			logging.debug('{GAME = ' + str(game.chat_id) + ' GUESSED = \n' + str(guessed) + '}')
			wordlist = [x for x, _ in guessed]
			probs = [x for _, x in guessed]
			all_moves.append((calc_profit(wordlist[:number], marker, probs[:number]), (word, number), [str(x) for x in wordlist]))
	return sorted(all_moves)[::-1][:game.field.n]

def do_move(game):
	if game.current_move == 'b':
		PROFITS['b'], PROFITS['r'] = PROFITS['r'], PROFITS['b']
	moves = bruteforce(game, game.current_move)
	if game.current_move == 'b':
		PROFITS['b'], PROFITS['r'] = PROFITS['r'], PROFITS['b']
	logging.info('{GAME = ' + str(game.chat_id) + ' POSSIBLE_MOVES = \n' + str(moves) + '}')
	forb_set = {x[0] for x in game.moves}
	for _, move, ans in moves:
		if not move[0] in forb_set:
			game.moves.append(move)
			game.answers.append((_, ans))
			return move
	return ('-', 1)

def do_guess(game, word):
	sorted_list = guess(game.field, word)
	return sorted_list[0][1]

def do_clear(game, word):
	if word == '-':
		return True
	field = game.field
	for i, w in enumerate(field):
		if w.used:
			continue
		if w.word == word:
			logging.info('{GAME = ' + str(game.chat_id) + ' FOUND = \n' + str(w) + '}')
			field.all[i].used = True
			return True
	return False

def start_game():
	field = Field()
	field.gen()
	answers = []
	moves = []
	guesses = []
	while not field.game_over():
		clear_output()
		print(field)
		move = do_move(field, moves, answers)
		print(move)
		for i in range(move[1]):
			inp = input()
			guesses.append(inp)
			do_clear(field, inp)
	clear_output()
	field.print_with_markers()
	ptr = 0
	for i in range(len(moves)):
		print('========')
		print(moves[i])
		for j in range(moves[i][1]):
			print(guesses[ptr], end=' ')
			ptr += 1
		print()
		print(anxswers[i])
print('import ok')