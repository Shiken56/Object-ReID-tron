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

current_frame_id = -1
frame_chunks = {}
expected_chunks = 0

try:
    while True:
        data, addr = sock.recvfrom(2048) # Buffer size is 2048 bytes
        
        if len(data) < HEADER_SIZE:
            continue
            
        header = data[:HEADER_SIZE]
        payload = data[HEADER_SIZE:]
        
        frame_id, chunk_idx, total_chunks = struct.unpack(HEADER_FORMAT, header)
        
        # If we get a chunk for a new frame, clear old partial frames
        if frame_id > current_frame_id:
            current_frame_id = frame_id
            frame_chunks = {}
            expected_chunks = total_chunks
            
        # Ignore delayed chunks from older frames
        if frame_id < current_frame_id:
            continue
            
        frame_chunks[chunk_idx] = payload
        
        # Check if we have received all chunks for the current frame
        if len(frame_chunks) == expected_chunks:
            # Reassemble the frame byte array
            frame_data = b"".join(frame_chunks[i] for i in range(expected_chunks))
            
            # Make sure the length matches exactly what we expect (224 * 224 * 3)
            expected_bytes = IMG_WIDTH * IMG_HEIGHT * CHANNELS
            if len(frame_data) == expected_bytes:
                # Convert bytes to numpy array
                img_array = np.frombuffer(frame_data, dtype=np.uint8)
                img = img_array.reshape((IMG_HEIGHT, IMG_WIDTH, CHANNELS))
                
                # OpenCV expects BGR format by default, but STM32 might be sending RGB
                # Convert RGB to BGR for display
                img_bgr = cv2.cvtColor(img, cv2.COLOR_RGB2BGR)
                
                # Resize it so it's easier to see on PC (e.g., 2x or 3x scale)
                img_bgr_large = cv2.resize(img_bgr, (IMG_WIDTH * 3, IMG_HEIGHT * 3), interpolation=cv2.INTER_NEAREST)
                
                cv2.imshow("STM32 Camera Stream", img_bgr_large)
                
                # Press 'q' to quit
                if cv2.waitKey(1) & 0xFF == ord('q'):
                    break
            else:
                print(f"Warning: Reassembled frame size {len(frame_data)} doesn't match expected {expected_bytes}")
                
except KeyboardInterrupt:
    print("\nStream stopped by user.")
finally:
    cv2.destroyAllWindows()
    sock.close()
