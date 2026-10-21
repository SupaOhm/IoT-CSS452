import time, requests
from random import randint

PERIOD = 60 #seconds
BASE_URL = 'https://api.thingspeak.com/update.json'
KEY = 'Your Write API Key'

def send_data(Value):
    data = {'api_key': KEY, 'field1': Value}
    response = requests.post(BASE_URL, json=data)

while True:
    Number = randint(0, 100)
    print('Number: ' + str(Number))
    send_data(Number)
    time.sleep(PERIOD)
