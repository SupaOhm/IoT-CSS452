from gpiozero import LED
from guizero import App, PushButton

led = LED(22)

def start():
    start_button.disable()
    stop_button.enable()
    led.on()

def stop():
    start_button.enable()
    stop_button.disable()
    led.off()

app = App(width=100, height=150)
start_button = PushButton(app, command=start, text="On")
start_button.text_size = 30
stop_button = PushButton(app, command=stop, text="Off", enabled=False)
stop_button.text_size = 30
app.display()
