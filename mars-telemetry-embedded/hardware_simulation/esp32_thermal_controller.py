"""
ESP32 Thermal LED Controller (MicroPython)
Author: Fulvio Favilla
Description: Simulates Martian temperature readings by controlling an RGB LED
via PWM, mapping temperature scales to light intensity.
"""

import machine
import network
import time
import ujson as json
# import urequests as requests # Uncomment if fetching directly from ESP32

# --- Hardware Configuration ---
LED_PIN_R = 14
LED_PIN_G = 13
LED_PIN_B = 12

PWM_FREQ = 500
MAX_DUTY_CYCLE = 1023
MIN_DUTY_CYCLE = 0

# Initialize PWM channels
pwm_r = machine.PWM(machine.Pin(LED_PIN_R), freq=PWM_FREQ)
pwm_g = machine.PWM(machine.Pin(LED_PIN_G), freq=PWM_FREQ)
pwm_b = machine.PWM(machine.Pin(LED_PIN_B), freq=PWM_FREQ)

def test_leds():
    """Cycles LEDs to maximum brightness for hardware verification."""
    print("Testing RGB LEDs...")
    pwm_r.duty(MAX_DUTY_CYCLE)
    pwm_g.duty(MAX_DUTY_CYCLE)
    pwm_b.duty(MAX_DUTY_CYCLE)
    time.sleep(1)
    # Reset after test
    pwm_r.duty(MIN_DUTY_CYCLE)
    pwm_g.duty(MIN_DUTY_CYCLE)
    pwm_b.duty(MIN_DUTY_CYCLE)

# --- Temperature Processing Logic ---
# Mocking Mars Temperature Data (Celsius)
MOCK_TEMP_MAX_C = 20
MOCK_TEMP_MIN_C = 5
CURRENT_TEMP_C = 15

def celsius_to_kelvin(temp_celsius: float) -> float:
    """Converts Celsius to Kelvin to avoid negative temperature logic in PWM."""
    return temp_celsius + 273.15

def calculate_pwm_duty(current_temp_k: float, min_k: float, max_k: float) -> int:
    """
    Maps a given Kelvin temperature to a 10-bit PWM duty cycle (0-1023).
    Limits output to valid boundaries to prevent hardware errors.
    """
    if current_temp_k <= min_k: return MIN_DUTY_CYCLE
    if current_temp_k >= max_k: return MAX_DUTY_CYCLE

    ratio = (current_temp_k - min_k) / (max_k - min_k)
    return int(ratio * MAX_DUTY_CYCLE)

# --- Main Execution ---
def main():
    print("Initializing Aerospace Thermal Simulator...")
    test_leds()

    # Calculate limits in Kelvin
    temp_max_k = celsius_to_kelvin(MOCK_TEMP_MAX_C)
    temp_min_k = celsius_to_kelvin(MOCK_TEMP_MIN_C)
    current_temp_k = celsius_to_kelvin(CURRENT_TEMP_C)

    # Map to PWM scale
    target_pwm = calculate_pwm_duty(current_temp_k, temp_min_k, temp_max_k)

    print(f"Current Temp: {CURRENT_TEMP_C}C ({current_temp_k}K)")
    print(f"Applying PWM Duty Cycle: {target_pwm}/{MAX_DUTY_CYCLE}")

    # Apply to Red channel as an example of thermal visualization
    pwm_r.duty(target_pwm)

if __name__ == "__main__":
    main()
