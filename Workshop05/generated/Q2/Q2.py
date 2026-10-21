from gpiozero import PWMLED

led = PWMLED(22)

while True:
    brightness_s = input("Enter Brightness (0.0 to 1.0):")
    brightness = float(brightness_s)
    led.value = brightness
