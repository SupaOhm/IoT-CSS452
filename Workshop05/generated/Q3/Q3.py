from gpiozero import Button, LED

button = Button(18, pull_up=True)
led = LED(22)

while True:
    if button.is_pressed:
        led.on()
    else:
        led.off()
