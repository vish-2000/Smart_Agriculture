from boltiot import Bolt

import configuration as conf
import requests
import json
import time

mybolt = Bolt(conf.bolt_api_key2, conf.device_id2)
myBolt.serialBegin(9600)

"""Sends Message via Telegram"""
def send_telegram_message(message):
  url = "https://api.telegram.org/" + conf.telegram_bot_id + "/sendMessage"
    data = {
        "chat_id": conf.telegram_chat_id,
        "text": message
    }
    try:
        response = requests.request(
            "POST",
            url,
            params=data
        )
        print("This is the Telegram URL: "+url)
        print("This is the Telegram response: "+response.text)
        
        telegram_data = json.loads(response.text)
        
        return telegram_data["ok"]
    except Exception as e:
        print("An error occurred in sending the alert message via Telegram")
        print(e)
        return False
      
while True:
  response = mybolt.serialRead(10)
  data = json.loads(response)
  print(data)
  time.sleep(5)
