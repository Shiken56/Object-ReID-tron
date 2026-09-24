import socket
import struct
import numpy as np
import cv2

# Configuration
UDP_IP = "0.0.0.0" # Listen on all network interfaces
UDP_PORT = 5000
IMG_WIDTH = 224
IMG_HEIGHT = 224
CHANNELS = 3

# Create a UDP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))

print(f"Listening on UDP port {UDP_PORT} for STM32 camera stream...")

# Header structure: 4 bytes (frame_id) + 2 bytes (chunk_idx) + 2 bytes (total_chunks)
HEADER_FORMAT = "<IHH"
HEADER_SIZE = struct.calcsize(HEADER_FORMAT)

# Create a persistent frame buffer to hold the image
frame_buffer = bytearray(IMG_WIDTH * IMG_HEIGHT * CHANNELS)
current_frame_id = -1

try:
    while True:
        data, addr = sock.recvfrom(2048) # Buffer size is 2048 bytes
        
        if len(data) < HEADER_SIZE:
            continue
            
        header = data[:HEADER_SIZE]
        payload = data[HEADER_SIZE:]
        
        frame_id, chunk_idx, total_chunks = struct.unpack(HEADER_FORMAT, header)
        
        # If we get a chunk from a very old frame, ignore it
        if frame_id < current_frame_id:
            continue
            
        if frame_id > current_frame_id:
            current_frame_id = frame_id
            # We purposely do NOT clear the frame_buffer here! 
            # If a chunk drops, it will just show the pixels from the previous frame, preventing glitches!
            
        # Calculate exactly where this chunk belongs in the massive image array
        offset = chunk_idx * 1024
        end_offset = offset + len(payload)
        
        # Write the payload directly into the correct spot in the image buffer
        frame_buffer[offset:end_offset] = payload
        
        # Display the image! We update the screen every time we get the last chunk,
        # OR every 50 chunks, so you can see the image drawing live even if the last chunk is dropped!
        if chunk_idx == total_chunks - 1 or chunk_idx % 50 == 0:
            img_array = np.frombuffer(frame_buffer, dtype=np.uint8)
            img = img_array.reshape((IMG_HEIGHT, IMG_WIDTH, CHANNELS))
            
            img_bgr = cv2.cvtColor(img, cv2.COLOR_RGB2BGR)
            
            # Since 224x224 is small on a PC monitor, scale it up 3x for easy viewing!
            img_bgr_large = cv2.resize(img_bgr, (IMG_WIDTH * 3, IMG_HEIGHT * 3), interpolation=cv2.INTER_NEAREST)
            
            cv2.imshow("STM32 Live Stream", img_bgr_large)
            
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break
                
except KeyboardInterrupt:
    print("\nStream stopped by user.")
finally:
    cv2.destroyAllWindows()
    sock.close()
