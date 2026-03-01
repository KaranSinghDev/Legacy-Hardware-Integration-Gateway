import socket
import threading
import time
import random
import json

HOST = '0.0.0.0'
PORT = 9999

class PowerSupplyDevice:
    def __init__(self):
        self.voltage = 5.0
        self.current = 0.5
        self.status = "STABLE"
        self.temp_sensors = [25.1, 25.3, 24.9]
        self.lock = threading.Lock()

    def process_command(self, command):
        cmd = command.strip().upper()
        
        with self.lock:
            time.sleep(0.001) # Simulate low hardware latency for stress test

            if cmd == "READ:VOLT":
                return f"VOLT:{self.voltage + random.uniform(-0.01, 0.01):.4f}"
            
            elif cmd == "READ:CURRENT":
                return f"CURR:{self.current + random.uniform(-0.01, 0.01):.4f}"

            elif cmd == "READ:STATUS":
                return f"STAT:{self.status}"
            
            # New Complex Type: JSON
            elif cmd == "READ:SENSORS":
                data = {
                    "unit": "Celsius",
                    "values": [t + random.uniform(-0.1, 0.1) for t in self.temp_sensors]
                }
                return f"JSON:{json.dumps(data)}"
            
            # Command to test error handling
            elif cmd == "TRIGGER:ERROR":
                self.status = "ERROR_STATE"
                return "OK: STATUS SET TO ERROR"

            else:
                return "ERR:UNKNOWN_CMD"

def handle_client(conn, addr, device):
    with conn:
        while True:
            try:
                data = conn.recv(1024)
                if not data: break
                command = data.decode('utf-8')
                response = device.process_command(command)
                conn.sendall((response + "\n").encode('utf-8'))
            except ConnectionResetError:
                break

def main():
    device = PowerSupplyDevice()
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((HOST, PORT))
    s.listen()
    print(f"Advanced Legacy Simulator running on {HOST}:{PORT}")
    while True:
        conn, addr = s.accept()
        threading.Thread(target=handle_client, args=(conn, addr, device)).start()

if __name__ == "__main__":
    main()