"""
Mars Telemetry Ingestion Script
Author: Fulvio Favilla
Description: Fetches the latest Martian weather data from NASA's API
and processes it into a localized JSON payload for embedded consumption.
"""

import requests
import json
import logging
from typing import List, Dict, Any

# Configure logging for standard output
logging.basicConfig(level=logging.INFO, format='%(levelname)s: %(message)s')

NASA_MARS_API_URL = "https://mars.nasa.gov/rss/api/?feed=weather&category=msl&feedtype=json"
OUTPUT_FILE = "mars_weather_mock.json"

def fetch_mars_weather() -> List[Dict[str, Any]]:
    """Fetches and parses the last 7 days of Mars weather data."""
    try:
        logging.info(f"Requesting telemetry data from {NASA_MARS_API_URL}")
        response = requests.get(NASA_MARS_API_URL, timeout=10)
        response.raise_for_status()
        mars_data = response.json()

        parsed_data = []

        # Extracting the last 7 available Martian days (Sols)
        for i in range(7):
            sol = mars_data['soles'][i]
            parsed_data.append({
                'date': sol.get('terrestrial_date'),
                'min_temp': sol.get('min_temp'),
                'max_temp': sol.get('max_temp')
            })

        logging.info("Successfully parsed 7 days of Martian telemetry.")
        return parsed_data

    except requests.exceptions.RequestException as e:
        logging.error(f"Failed to fetch data from NASA API: {e}")
        return []
    except (KeyError, IndexError) as e:
        logging.error(f"Failed to parse JSON structure: {e}")
        return []

def save_telemetry_to_disk(data: List[Dict[str, Any]], filename: str) -> None:
    """Saves the parsed dictionary to a JSON file."""
    if not data:
        logging.warning("No data to save. Operation aborted.")
        return

    with open(filename, "w", encoding="utf-8") as file:
        json.dump(data, file, indent=2)
    logging.info(f"Telemetry payload successfully saved to {filename}")

if __name__ == "__main__":
    weather_payload = fetch_mars_weather()
    save_telemetry_to_disk(weather_payload, OUTPUT_FILE)
