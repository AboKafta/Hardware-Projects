#Georgy Rached Pico Project 2. Used code from github for the servo motor and the ultrasonic sensor
#importing modules needed
from machine import Pin, PWM
import utime

#defining pins to control servo
servo_pin = 0
servo = PWM(Pin(servo_pin))

#defining pwm length
servo.freq(50)

#Duty value used to rotate servo motor
max_duty = 7864   #180 degrees

#setup for LED
led = Pin(15, Pin.OUT)
led2 = Pin(14, Pin.OUT)

#setup for ultrasonic snesor
trigger = Pin(3, Pin.OUT)
echo = Pin(2, Pin.IN)

#Github Code, making the sensor length
def ultra():
    # Send out a pulse from trigger pin
    trigger.low()
    utime.sleep_us(2)
    trigger.high()
    utime.sleep_us(10)
    trigger.low()

    # Measure time of signal on vs off
    while echo.value() == 0:
        pass
    signaloff = utime.ticks_us()
    while echo.value() == 1:
        pass
    signalon = utime.ticks_us()
    # Calculate distance from speed of sound
    timepassed = signalon - signaloff
    distance = (timepassed * 0.0343) / 2  # convert to cm
    
    return distance

#this is a boolean statement used for blinking mechanism later
activated = False  # stays True once triggered

while True:
    #changing name for better understanding
    distance = ultra()
    print("Distance:", distance)

    #if statement that if the distance becomes less, it activates
    if not activated and distance <= 10.0:
        print("Within 10cm, the ghost has activated!!!")
        servo.duty_u16(max_duty)
        activated = True  # lock in activated mode

    #Telling the blinking to happen forever
    if activated:
        led.toggle()
        led2.toggle()
        utime.sleep_ms(500)  #blink speed
    else:
        #idle state
        led.off()
        led2.off()
        utime.sleep_ms(200)
