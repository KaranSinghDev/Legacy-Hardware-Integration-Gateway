import socket, threading, time, random
HOST, PORT = '0.0.0.0', 9999  # Note: 0.0.0.0 is required for Docker!

def handle_client(conn, addr):
    print(f"Connected by {addr}")
    with conn:
        while True:
            data = conn.recv(1024)
            if not data: break
            cmd = data.decode('utf-8').strip().upper()
            if cmd == "PING": resp = "PONG"
            elif cmd == "READ:VOLT": resp = f"VOLT:{random.uniform(4.9, 5.1):.2f}"
            elif "SET:VOLT" in cmd: resp = "OK: VOLT SET"
            else: resp = "ERR"
            conn.sendall((resp + "\n").encode('utf-8'))

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen()
print(f"Legacy Sim listening on {HOST}:{PORT}")
while True:
    conn, addr = s.accept()
    threading.Thread(target=handle_client, args=(conn, addr)).start()