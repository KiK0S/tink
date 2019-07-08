import json
from telegram.ext import Updater, CommandHandler, MessageHandler, Filters
from Model import *

class Game:
	def __init__(self):
		pass
	def __init__(self, id, send):
		self.id = id
		self.field = Field()
		self.field.gen()
		self.answers = []
		self.moves = []
		self.guesses = []
		self.reading_buffer = []
		self.send = send
		self.left = 0
		self.status = 0

	def make_move(self):
		print('do move')
		print(self.field)
		self.send(chat_id=self.id, text=str(self.field))
		move = do_move(self.field, self.moves, self.answers)
		self.send(chat_id=self.id, text=str(move))
		self.left = move[1]
		print('done')

	def play(self):
		print('game.play')
		if len(self.reading_buffer) > 0:
			self.guesses.append(self.reading_buffer[-1])
			self.reading_buffer.pop()
			do_clear(self.field, self.guesses[-1])
			self.left -= 1
		if self.left == 0:
			if self.field.game_over():
				self.send(chat_id=self.id, text=self.field.print_with_markers())
				print('here')
				print(self.moves)
				print(self.guesses)
				print(self.answers)
				ptr = 0
				result = ''
				self.status = 0
				for i in range(len(self.moves)):
					print('cycle - ', i)
					result += '========\n'
					result += str(self.moves[i]) + '\n'
					for j in range(self.moves[i][1]):
						print('inner cycle - ', j)
						result += str(self.guesses[ptr]) + ' '
						ptr += 1
					result += '\n' + str(self.answers[i]) + '\n'
				print(result)
				print('sending result')
				self.send(chat_id=self.id, text=result)
				self.send(chat_id=self.id, text='Thanks for the game :-)')
				print('ok i did it')
				return False
			self.make_move()

def start(update, context):
	context.bot.send_message(chat_id=update.message.chat_id, text='Hi!\nLet\'s start our game. We play 1-person Codenames, you are the guesser. Type the word when I will ask you. If you want to skip word, use "-". Remember I\'m bad at typo mistakes, don\'t do them. \nGood Luck!')
	global game
	game = Game(update.message.chat_id, context.bot.send_message)
	game.status = 1
	game.play()


def echo(update, context):
	global game
	if game.status == 0:
		context.bot.send_message(chat_id=update.message.chat_id, text='Please start new game')
	else:
		game.reading_buffer.append(update.message.text)
		game.play()

def help(update, context):
	s = input()
	PROFITS[s.split()[0]] = int(s.split()[1])

def main():
	with open('secret_data', 'r') as f:
		secret_data = json.load(f)
	REQUEST_KWARGS={
		'proxy_url': 'http://' + secret_data['proxy_ip'] + ':' + secret_data['proxy_port'],
	}
	updater = Updater(secret_data['token'], use_context=True, request_kwargs=REQUEST_KWARGS)
	dp = updater.dispatcher
	dp.add_handler(CommandHandler("start", start))
	dp.add_handler(CommandHandler("help", help))
	dp.add_handler(MessageHandler(Filters.text, echo))
	updater.start_polling()
	updater.idle()


if __name__ == '__main__':
	main()