import socket

def start_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(("0.0.0.0", 8080))
    server_socket.listen(1)

    print("Server listening on port 8080...")

    while True:
        conn, addr = server_socket.accept()
        print("Connected by", addr)
        data = conn.recv(1024)
        if not data:
            break
        conn.sendall(data)

    conn.close()

if __name__ == "__main__":
    start_server()
