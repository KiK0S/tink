import logging
import json
from telegram.ext import Updater, CommandHandler, MessageHandler, Filters
from Model import *

logging.basicConfig(format = u'%(filename)s[LINE:%(lineno)d]# %(levelname)-8s [%(asctime)s]  %(message)s', level = logging.DEBUG, filename = u'bot.log')

class Game:
	def __init__(self):
		pass
	def __init__(self, id, send, edit):
		self.id = id
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

	def make_move(self):
		self.field_id = self.send(chat_id=self.id, text=str(self.field)).message_id
		move = do_move(self.field, self.moves, self.answers)
		print('do move')
		print(move)
		self.send(chat_id=self.id, text=str(move))
		self.left = move[1]

	def play(self):
		if len(self.reading_buffer) > 0:
			self.guesses.append(self.reading_buffer[-1])
			self.reading_buffer.pop()
			self.left -= 1
			if do_clear(self.field, self.guesses[-1]):
				self.edit(str(self.field), self.id, self.field_id)
		if self.field.game_over():
			self.send(chat_id=self.id, text=self.field.print_with_markers())
			ptr = 0
			result = ''
			self.status = 0
			for i in range(len(self.moves)):
				result += '========\n'
				result += str(self.moves[i]) + '\n'
				for j in range(self.moves[i][1]):
					if ptr < len(self.guesses):
						result += str(self.guesses[ptr]) + ' '
					ptr += 1
				result += '\n' + str(self.answers[i]) + '\n'
			print('sending result')
			self.send(chat_id=self.id, text=result)
			self.send(chat_id=self.id, text='Thanks for the game :-)')
			return False
		if self.left <= 0:
			self.make_move()

all_games = {}

def start(update, context):
	context.bot.send_message(chat_id=update.message.chat_id, text='Hi!\nLet\'s start our game. We play 1-person Codenames, you are the guesser. Type the word when I will ask you. If you want to skip word, use "-". Remember I\'m bad at typo mistakes, don\'t do them. \nGood Luck!')
	game = Game(update.message.chat_id, context.bot.send_message, context.bot.edit_message_text)
	game.status = 1
	game.play()
	all_games[update.message.chat_id] = game


def echo(update, context):
	game = all_games[update.message.chat_id]
	if game.status == 0:
		context.bot.send_message(chat_id=update.message.chat_id, text='Please start new game')
	else:
		game.reading_buffer.append(update.message.text)
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

def main():
	REQUEST_KWARGS={
		'proxy_url': 'http://' + secret_data['proxy_ip'] + ':' + secret_data['proxy_port'],
	}
	updater = Updater(secret_data['token'], use_context=True, request_kwargs=REQUEST_KWARGS)
	dp = updater.dispatcher
	dp.add_handler(CommandHandler("start", start))
	dp.add_handler(CommandHandler("setup", setup))
	dp.add_handler(MessageHandler(Filters.text, echo))
	updater.start_polling()
	updater.idle()


if __name__ == '__main__':
	main()