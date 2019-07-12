import logging
import json
import telegram
from telegram.ext import Updater, CommandHandler, MessageHandler, Filters
logging.basicConfig(format = u'[%(filename)s{LINE:%(lineno)d}# %(levelname)-8s [%(asctime)s]  %(message)s]', level=logging.INFO, filename = u'bot.log')
from Model import *


class Game:
	def __init__(self):
		pass
	def __init__(self, id, send, edit):
		self.id = id
		self.chat_id = id
		self.field = Field()
		self.field.gen()
		self.answers = []
		self.moves = []
		self.guesses = []
		self.reading_buffer = []
		self.send = send
		self.edit = edit
		self.left = 0
		self.status = 0
		self.field_id = 0
		self.guessers = []
		self.captains = []
		self.current_word = '-'

	def make_move(self):
		move = do_move(self)
		logging.info('{GAME = ' + str(self.chat_id) + ' MOVE = \n' + str(move) + '}')
		self.send(chat_id=self.id, text=str(move))
		self.left = move[1]
		self.current_word = move[0]

	def play(self):
		need_to_reload = False
		while True:
			if len(self.guessers) == 0:
				if self.left > 0:
					self.reading_buffer.append(do_guess(self, self.current_word).word)
					logging.info('{GAME = ' + str(self.chat_id) + ' AI_GUESS = \n' + self.reading_buffer[-1] + '}')
					need_to_reload = True
				else:
					break
			if len(self.reading_buffer) > 0:
				self.guesses.append(self.reading_buffer[-1])
				logging.info('{GAME = ' + str(self.chat_id) + ' GUESS = \n' + str(self.guesses[-1]) + '}')
				self.reading_buffer.pop()
				self.left -= 1
				logging.info(self.reading_buffer)
				logging.info(self.guesses)
				need_to_reload = True
				if do_clear(self, self.guesses[-1]):
					self.edit(self.field.print_without_markers(), self.id, self.field_id, parse_mode=telegram.ParseMode.HTML)
			if len(self.guessers) > 0:
				break
		if self.field.game_over():
			self.send(chat_id=self.id, text=self.field.print_with_markers())
			ptr = 0
			result = ''
			for i in range(len(self.moves)):
				result += '========\n'
				result += str(self.moves[i]) + '\n'
				for j in range(self.moves[i][1]):
					if ptr < len(self.guesses):
						result += str(self.guesses[ptr]) + ' '
					ptr += 1
				result += '\n' + str(self.answers[i]) + '\n'
			self.end()
			if result != '':
				self.send(chat_id=self.id, text=result)
			logging.info('{GAME = ' + str(self.chat_id) + ' STATISTICS = \n' + result + '}')
			self.send(chat_id=self.id, text='Thanks for the game :-)')
			return False
		if self.left <= 0:
			if len(self.captains) == 0:
				self.make_move()
				need_to_reload = True
			else:
				self.send(chat_id=self.id, text='waiting for captains')
		if need_to_reload:
			self.play()

	def end(self):
		self.status = 0
		self.captains = []
		self.guessers = []
		self.field = Field()
		self.field.gen()
		self.answers = []
		self.moves = []
		self.guesses = []
		self.reading_buffer = []
		self.left = 0
		self.current_word = '-'

all_games = {}

def init(update, context):
	game = Game(update.message.chat_id, context.bot.send_message, context.bot.edit_message_text)
	all_games[update.message.chat_id] = game
	context.bot.send_message(chat_id=update.message.chat_id, text='Hi!')


def start(update, context):
	context.bot.send_message(chat_id=update.message.chat_id, text='Hi!\nLet\'s start our game. We play 1-person Codenames, you are the guesser. Type the word when I will ask you. If you want to skip word, use "-". Remember I\'m bad at typo mistakes, don\'t do them. \nGood Luck!')
	game = all_games[update.message.chat_id]
	game.status = 1
	logging.info('{GAME = ' + str(game.chat_id) + ' NEW_FIELD = \n' + game.field.print_with_markers() + '}')
	logging.info('{GAME = ' + str(game.chat_id) + ' CAPTAINS = \n' + str(game.captains) + '}')
	logging.info('{GAME = ' + str(game.chat_id) + ' GUESSERS = \n' + str(game.guessers) + '}')
	for user in game.captains:
		context.bot.send_message(chat_id=user, text=game.field.print_with_markers())
	game.field_id = game.send(chat_id=game.id, text=game.field.print_without_markers(), parse_mode=telegram.ParseMode.HTML).message_id
	game.play()
	

def echo(update, context):
	game = all_games[update.message.chat_id]
	if game.status == 0:
		context.bot.send_message(chat_id=update.message.chat_id, text='Please start new game')
	else:
		if update.message.from_user.id in game.guessers:
			game.reading_buffer.append(update.message.text.lower())
		elif update.message.from_user.id in game.captains:
			try:
				word, number = update.message.text.split()
				number = int(number)
				word = word.lower()
				if game.left != 0:
					logging.error(update.message.text, word, number)
					raise Exception
			except:
				context.bot.send_message(chat_id=update.message.chat_id, text='write smth ok please')
			game.left = number
			game.current_word = word
			context.bot.send_message(chat_id=update.message.chat_id, text=word + '; ' + str(number))
		game.play()

def setup(update, context):
	s = input()
	if s.split()[0] == 'T':
		CAN_GUESS_THRESHOLD = float(s.split()[1])
		secret_data['CAN_GUESS_THRESHOLD'] = CAN_GUESS_THRESHOLD
	elif s.split[0] == 'M':
		MULTIPLY_EXP = float(s.split()[1]) 
		secret_data['MULTIPLY_EXP'] = CAN_GUESS_THRESHOLD
	else:
		PROFITS[s.split()[0]] = float(s.split()[1])
		secret_data['PROFITS'] = PROFITS
	print(secret_data)
	with open('secret_data', 'w') as f:
		json.dump(secret_data, f)

def captain(update, context):
	game = all_games[update.message.chat_id]
	game.captains.append(update.message.from_user.id)
	if update.message.from_user.id in game.guessers:
		game.guessers.remove(update.message.from_user.id)
	context.bot.send_message(chat_id=update.message.chat_id, text='OK wrote ' + str(update.message.from_user.username) + ' as captain')

def guesser(update, context):
	game = all_games[update.message.chat_id]
	game.guessers.append(update.message.from_user.id)
	if update.message.from_user.id in game.captains:
		game.captains.remove(update.message.from_user.id)
	context.bot.send_message(chat_id=update.message.chat_id, text='OK wrote ' + str(update.message.from_user.username) + ' as guesser')

def main():
	REQUEST_KWARGS={
		'proxy_url': 'http://' + secret_data['proxy_ip'] + ':' + secret_data['proxy_port'],
	}
	updater = Updater(secret_data['token'], use_context=True, request_kwargs=REQUEST_KWARGS)
	dp = updater.dispatcher
	dp.add_handler(CommandHandler("start", start))
	dp.add_handler(CommandHandler("setup", setup))
	dp.add_handler(CommandHandler("captain", captain))
	dp.add_handler(CommandHandler("guesser", guesser))
	dp.add_handler(CommandHandler("init", init))
	dp.add_handler(MessageHandler(Filters.text, echo))
	updater.start_polling()
	updater.idle()


if __name__ == '__main__':
	main()