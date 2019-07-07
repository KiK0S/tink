import logging
import json
from telegram.ext import Updater, CommandHandler, MessageHandler, Filters

# Enable logging
logging.basicConfig(format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
                    level=logging.INFO)

logger = logging.getLogger(__name__)


# Define a few command handlers. These usually take the two arguments bot and
# update. Error handlers also receive the raised TelegramError object in error.
def start(update, context):
    """Send a message when the command /start is issued."""
    context.bot.send_message(chat_id=update.message.chat_id, text='Hi!')


def help(update, context):
    """Send a message when the command /help is issued."""
    context.bot.send_message(chat_id=update.message.chat_id, text='Help!')


def echo(update, context):
    """Echo the user message."""
    context.bot.send_message(chat_id=update.message.chat_id, text=update.message.text)


def error(update, context):
    """Log Errors caused by Updates."""
    logger.warning('Update "%s" caused error "%s"', update, context.error)


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
	dp.add_error_handler(error)
	updater.start_polling()
	updater.idle()


if __name__ == '__main__':
	main()