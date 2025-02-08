import http.server
import socketserver
from urllib.parse import urlparse, parse_qs
import asyncio
from bleak import BleakScanner, BleakClient

# Replace with your ESP32's service and characteristic UUIDs
SERVICE_UUID = "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
CHAR_UUID = "beb5483e-36e1-4688-b7f5-ea07361b26a8"

# Replace with your ESP32's device name
DEVICE_NAME = "LED Controller"

class RequestHandler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        parsed_path = urlparse(self.path)
        if parsed_path.path == '/led':
            query = parse_qs(parsed_path.query)
            state = query.get('state', [None])[0]
            if state:
                print(f"Received request to turn LED {state}")
                asyncio.run(self.control_led(state))
                self.send_response(200)
                self.send_header('Content-type', 'application/json')
                self.end_headers()
                self.wfile.write(bytes(f'{{"status": "LED {state}"}}', 'utf-8'))
            else:
                self.send_response(500)
                self.send_header('Content-type', 'application/json')
                self.end_headers()
                self.wfile.write(bytes('{"error": "Invalid state"}', 'utf-8'))
        else:
            self.path = 'index.html'
            return http.server.SimpleHTTPRequestHandler.do_GET(self)

    async def control_led(self, state):
        device = await self.find_device()
        if device:
            print(f"Found device: {device}")
            async with BleakClient(device) as client:
                value = b'start' if state == 'on' else b'pause'
                print(f"Writing value {value} to characteristic {CHAR_UUID}")
                await client.write_gatt_char(CHAR_UUID, value)
        else:
            print("Device not found")

    async def find_device(self):
        print("Scanning for devices...")
        devices = await BleakScanner.discover(timeout=10.0)  # Increase scan duration to 10 seconds
        for device in devices:
            print(f"Discovered device: {device.name} ({device.address})")
            if device.name == DEVICE_NAME:
                return device
        return None

def run(server_class=http.server.HTTPServer, handler_class=RequestHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting server on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()