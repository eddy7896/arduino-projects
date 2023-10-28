import RPi.GPIO as GPIO
import time

# Define the GPIO pin to which the flow sensor is connected
FLOW_SENSOR_PIN = 17  # Change this to the GPIO pin you are using

# Initialize GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setup(FLOW_SENSOR_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)

# Function to count pulses (flow rate)
def count_pulse(channel):
    global pulse_count
    pulse_count += 1

# Attach the interrupt for the flow sensor
GPIO.add_event_detect(FLOW_SENSOR_PIN, GPIO.FALLING, callback=count_pulse)

# Variables to keep track of flow data
pulse_count = 0
flow_rate = 0.0
total_volume = 0.0

try:
    while True:
        # Calculate flow rate (liters per minute)
        flow_rate = pulse_count / 7.5  # You may need to adjust the calibration factor

        # Calculate total volume (liters)
        total_volume = flow_rate / 60

        print "Flow Rate: %f L/min, Total Volume: %f L" % (flow_rate, total_volume)
        time.sleep(1)  # Read data every second

except KeyboardInterrupt:
    pass

# Clean up GPIO
GPIO.cleanup()
