import serial
import time
import sys

SERIAL_PORT = "/dev/ttyUSB1"  # Change if needed
BAUDRATE = 115200             # Adjust as necessary



try:
    Serial = serial.Serial(SERIAL_PORT, BAUDRATE, timeout=1)
    time.sleep(0.1)

    command = 0x13

    while True:
        Serial.write(bytes([command]))
        value=0
        sof=0
        count=0
        while True:
            try:
                rcv_data = Serial.read(2)
                if len(rcv_data) == 2:
                    # print("> ", rcv_data)
                    value = int.from_bytes(rcv_data, byteorder="little")
                    if value == 0xAFFF:
                        print("---- SoFr ----")
                    elif value == 0x5FFF:
                        print("---- SoFf ----\n\n")
                    else:
                        print("data =", value)

            except KeyboardInterrupt:
                print("\nInterrupted by user")
                exit(0)

except serial.SerialException as e:
    print(f"Serial Error: {e}")

finally:
    if 'Serial' in locals() and Serial.is_open:
        Serial.close()
        print("Serial connection closed.")