from gpiozero import LED
from time import sleep
LED_PIN = 22
led = LED(LED_PIN)

while True:
    print ("on")
    led.on()
    sleep(2)
    print ("off")
    led.off()
    sleep(2)
