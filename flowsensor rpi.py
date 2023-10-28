import RPi.GPIO as GPIO
import time
import requests

# ThingSpeak configuration
THINGSPEAK_API_KEY = 'YOUR_API_KEY'
THINGSPEAK_CHANNEL_ID = 'YOUR_CHANNEL_ID'
THINGSPEAK_URL = f'https://api.thingspeak.com/update?api_key={THINGSPEAK_API_KEY}&field1='

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

        print(f"Flow Rate: {flow_rate} L/min, Total Volume: {total_volume} L")

        # Send total volume data to ThingSpeak
        response = requests.get(THINGSPEAK_URL + str(total_volume))

        time.sleep(60)  # Read data and update ThingSpeak every minute

except KeyboardInterrupt:
    pass

# Clean up GPIO
GPIO.cleanup()
