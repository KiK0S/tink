import logging
import json
from telegram import *
from telegram.ext import Updater, CommandHandler, MessageHandler, Filters, CallbackQueryHandler
logging.basicConfig(format = u'[%(filename)s{LINE:%(lineno)d}# %(levelname)-8s [%(asctime)s]  %(message)s]', level=logging.INFO, filename = u'bot.log')
from Model import *


class Game:
	def __init__(self):
		pass
	def __init__(self, id, send, edit, edit_markup):
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
		self.edit_markup = edit_markup
		self.left = 0
		self.mode = 0
		self.status = 0
		self.field_id = 0
		self.move_id = 0
		self.guessers = []
		self.captains = []
		self.red_captain = False
		self.blue_captain = False
		self.red_guesser = False
		self.blue_guesser = False
		self.current_move = 'b'
		self.current_turn = 'c'
		self.current_word = '-'

	def make_move(self):
		move = do_move(self)
		logging.info('{GAME = ' + str(self.chat_id) + ' MOVE = \n' + str(move) + '}')
		try:
			self.edit(str(move), self.id, self.move_id)
			self.left = int(move[1])
			self.current_word = ''.join(str(move[0]))
		except:
			pass
	def play(self):
		need_to_reload = False
		if self.mode == 1:
			if len(self.guessers) == 0:
				if self.left > 0:
					self.reading_buffer.append(do_guess(self, self.current_word).word)
					logging.info('{GAME = ' + str(self.chat_id) + ' AI_GUESS = \n' + self.reading_buffer[-1] + '}')
					need_to_reload = True
		else:
			if self.left > 0:
				if self.current_move == 'r' and self.red_guesser == False or self.current_move == 'b' and self.blue_guesser == False:
					self.reading_buffer.append(do_guess(self, self.current_word).word)
					logging.info('{GAME = ' + str(self.chat_id) + ' AI_GUESS = \n' + self.reading_buffer[-1] + '}')
					need_to_reload = True
		if len(self.reading_buffer) > 0:
			self.guesses.append(self.reading_buffer[-1])
			logging.info('{GAME = ' + str(self.chat_id) + ' GUESS = \n' + str(self.guesses[-1]) + '}')
			self.reading_buffer.pop()
			logging.info(self.reading_buffer)
			logging.info(self.guesses)
			need_to_reload = True
			if do_clear(self, self.guesses[-1]):
				self.left -= 1
				if self.move_id != 0:
					self.edit(str((self.current_word, self.left)), self.id, self.move_id)
				try:
					self.edit('Let\'s start the game!\nCurrent move — ' + get_emoji(self.current_move), self.id, self.field_id, reply_markup=get_markup(self))
					self.edit_markup(chat_id=self.id, message_id=self.field_id, reply_markup=get_markup(self))
				except:
					pass

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
		if self.left <= 0 and len(self.reading_buffer) == 0:
			self.current_turn = 'c'
			if self.mode == 2:
				if self.current_move == 'r':
					self.current_move = 'b'
				else:
					self.current_move = 'r'
				try:
					self.edit('Let\'s start the game!\nCurrent move — ' + get_emoji(self.current_move), self.id, self.field_id, reply_markup=get_markup(self))
				except:
					pass
		if self.current_turn == 'c':
			if self.mode == 1:
				if len(self.captains) == 0:
					try:
						self.edit('Please wait for AI to move', self.id, self.move_id)
					except:
						pass
					self.make_move()
					self.current_turn = 'g'
					need_to_reload = True
				else:
					if not need_to_reload:
						self.edit('waiting for captains', self.id, self.move_id)
			else:
				if self.current_move == 'r' and self.red_captain == False or self.current_move == 'b' and self.blue_captain == False:
					try:
						self.edit('Please wait for AI to move', self.id, self.move_id)
					except:
						pass
					self.make_move()
					self.current_turn = 'g'
					need_to_reload = True
				else:
					if not need_to_reload:
						self.edit('waiting for captains', self.id, self.move_id)
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
		self.red_captain = False
		self.blue_captain = False
		self.red_guesser = False
		self.blue_guesser = False
		self.current_word = '-'
		self.move_id = 0
		logging.info('{GAME = ' + str(self.chat_id) + ' END}')

all_games = {}

def init(update, context):
	game = Game(update.message.chat_id, context.bot.send_message, context.bot.edit_message_text, context.bot.edit_message_reply_markup)
	all_games[update.message.chat_id] = game
	context.bot.send_message(chat_id=update.message.chat_id, text='Hi!\nChoose mode.', reply_markup=InlineKeyboardMarkup([[InlineKeyboardButton('1 team', callback_data='(1)'), InlineKeyboardButton('2 teams (in development)', callback_data='(2)')]]))

def roles(update, context):
	game = all_games[update.effective_chat.id]
	if game.mode == 1:
		context.bot.send_message(chat_id=update.effective_chat.id, text='Choose your role. When it\'s over, use /start', reply_markup=InlineKeyboardMarkup([[InlineKeyboardButton('guesser', callback_data='guesser'), InlineKeyboardButton('captain', callback_data='captain')]]))
	else:
		context.bot.send_message(chat_id=update.effective_chat.id, text='Choose your role&team. When it\'s over, use /start', reply_markup=InlineKeyboardMarkup([[InlineKeyboardButton('captain' + get_emoji('r'), callback_data='captain' + get_emoji('r')), InlineKeyboardButton('captain' + get_emoji('b'), callback_data='captain' + get_emoji('b'))], [InlineKeyboardButton('guesser' + get_emoji('r'), callback_data='guesser' + get_emoji('r')), InlineKeyboardButton('guesser' + get_emoji('b'), callback_data='guesser' + get_emoji('b'))]]))

def get_markup(game):
	menu = []
	words = [str(x) for x in game.field.all] + ['-']
	ptr = 0
	for i in range(game.field.n // 3 + 1):
		buttons = []
		for j in range(3):
			if ptr < len(words):
				buttons.append(InlineKeyboardButton(words[ptr], callback_data=str(ptr)))
			ptr += 1
		menu.append(buttons)
	keyboard_markup = InlineKeyboardMarkup(menu)
	return keyboard_markup
	

def start(update, context):
	if not update.message.chat_id in all_games:
		context.bot.send_message(chat_id=update.message.chat_id, text='First set the game up using /init')
		return
	if all_games[update.message.chat_id].status:
		context.bot.send_message(chat_id=update.message.chat_id, text='First end previous game or set the new game up using /init')
		return
	game = all_games[update.message.chat_id]
	if len(game.captains) + len(game.guessers) == 0:
		context.bot.send_message(chat_id=update.message.chat_id, text='/init first')
		return
	game.status = 1
	logging.info('{GAME = ' + str(game.chat_id) + ' NEW_FIELD = \n' + game.field.print_with_markers() + '}')
	logging.info('{GAME = ' + str(game.chat_id) + ' CAPTAINS = \n' + str(game.captains) + '}')
	logging.info('{GAME = ' + str(game.chat_id) + ' GUESSERS = \n' + str(game.guessers) + '}')
	for user in game.captains:
		context.bot.send_message(chat_id=user, text=game.field.print_with_markers())
	if game.mode == 1:
		game.current_move = 'r'
	game.field_id = game.send(chat_id=game.id, text='Let\'s start the game!\nCurrent move — ' + get_emoji(game.current_move), reply_markup=get_markup(game)).message_id
	if len(game.captains) == 0:
		game.move_id = game.send(chat_id=game.id, text='Please wait for AI to move').message_id
	else:
		game.move_id = game.send(chat_id=game.id, text='Waiting for captain').message_id
	game.play()

def echo(update, context):
	try:
		if not update.message.chat_id in all_games:
			context.bot.send_message(chat_id=update.message.chat_id, text='First set the game up using /init')
			return
	except:
		pass
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
				pass
			game.left = number
			game.current_word = word
			game.answers += [['_user_'] * game.left]
			game.moves.append((word, number))
			game.current_turn = 'g'
			game.edit(str((word, number)), game.id, game.move_id)
			game.edit('Let\'s start the game!\nCurrent move — ' + get_emoji(game.current_move), game.id, game.field_id)
		game.play()

def setup(update, context):
	s = input()
	if s.split()[0] == 'T':
		CAN_GUESS_THRESHOLD = float(s.split()[1])
		secret_data['CAN_GUESS_THRESHOLD'] = CAN_GUESS_THRESHOLD
	elif s.split()[0] == 'M':
		MULTIPLY_EXP = float(s.split()[1]) 
		secret_data['MULTIPLY_EXP'] = CAN_GUESS_THRESHOLD
	else:
		PROFITS[s.split()[0]] = float(s.split()[1])
		secret_data['PROFITS'] = PROFITS
	print(secret_data)
	with open('secret_data', 'w') as f:
		json.dump(secret_data, f)

def captain_callback(update, context, game, role):
	game.captains.append(update.effective_user.id)
	if update.effective_user.id in game.guessers:
		game.guessers.remove(update.effective_user.id)
	context.bot.send_message(chat_id=game.chat_id, text='OK wrote ' + str(update.effective_user.username) + ' as ' + role)

def guesser_callback(update, context, game, role):
	game.guessers.append(update.effective_user.id)
	if update.effective_user.id in game.captains:
		game.captains.remove(update.effective_user.id)
	context.bot.send_message(chat_id=game.chat_id, text='OK wrote ' + str(update.effective_user.username) + ' as ' + role)

def tik(update, context):
	word = update.callback_query.data
	game = all_games[update.effective_chat.id]
	if word == '(1)':
		game.mode = 1
		roles(update, context)
		return
	if word == '(2)':
		game.mode = 2
		roles(update, context)
		return
	if word == 'captain' + get_emoji('r'):
		game.red_captain = True
	if word == 'captain' + get_emoji('b'):
		game.blue_captain = True
	if word == 'guesser' + get_emoji('r'):
		game.red_guesser = True
	if word == 'guesser' + get_emoji('b'):
		game.blue_guesser = True
	if word.startswith('guesser'):
		guesser_callback(update, context, game, word)
		return
	if word.startswith('captain'):
		captain_callback(update, context, game, word)
		return
	if not update.effective_user.id in game.guessers:
		return	
	word = int(word)
	if word < game.field.n:
		logging.info('{GAME = ' + str(game.chat_id) + ' USER_TRY = \n' + game.field.all[int(word)].word + '}')
		if not game.field.all[word].used:
			game.reading_buffer.append(game.field.all[word].word)
	else:
		game.reading_buffer.append('-')
	game.play()

def main():
	REQUEST_KWARGS={
		'proxy_url': 'http://' + secret_data['proxy_ip'] + ':' + secret_data['proxy_port'],
	}
	updater = Updater(secret_data['token'], use_context=True, request_kwargs=REQUEST_KWARGS)
	dp = updater.dispatcher
	dp.add_handler(CommandHandler("start", start))
	dp.add_handler(CommandHandler("setup", setup))
	dp.add_handler(CommandHandler("init", init))
	dp.add_handler(CallbackQueryHandler(tik))
	dp.add_handler(MessageHandler(Filters.text, echo))
	updater.start_polling()
	updater.idle()


if __name__ == '__main__':
	main()
