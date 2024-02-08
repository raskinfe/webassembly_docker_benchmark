import socket

def start_client():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(("localhost", 8080))

    message = b"Hello, server! This is a test message."

    client_socket.sendall(message)
    data = client_socket.recv(1024)

    print("Received:", data.decode())

    client_socket.close()

if __name__ == "__main__":
    start_client()
