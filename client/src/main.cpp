#include "WProgram.h"
#include <usb_dev.h>

#define LED 13

uint8_t buf[64];

void setup() { pinMode(LED, OUTPUT); }

void blink(uint8_t n, uint32_t ms) {
  for (uint8_t i = 0; i < n; i++) {
    digitalWriteFast(LED, HIGH);
    delay(ms);
    digitalWriteFast(LED, LOW);
    if (i < n - 1) {
      delay(ms);
    }
  }
}

int main() {
  setup();

  int8_t r; // received data
  uint16_t count = 0;

  digitalWriteFast(LED, HIGH);

  // Initialize the USB, and then wait for the host to set configuration.
  // If the client is powered without a PC connected to the USB port,
  // this will wait forever.
  usb_init();
  while (!usb_configuration)
    ; /* wait */

  digitalWriteFast(LED, LOW);
  blink(5, 100);

  // Wait an extra second for the server's operating system to load drivers
  // and do whatever it does to actually be ready for input
  delay(1000);

  while (1) {
    r = usb_rawhid_recv(buf, 0);
    if (r == 0) {
      continue;
    }

    // if first byte is in range '0' .. '9',
    // blink the corresponding number of times
    if (buf[0] >= '0' && buf[0] <= '9') {
      blink(buf[0] ^ 0x30, 300);
    }

    // put a count in the last 2 bytes
    buf[62] = count >> 8;
    buf[63] = count & 255;

    // send the packet
    usb_rawhid_send(buf, 50);

    // reset the buffer
    for (uint8_t i = 0; i < 63; i++) {
      buf[i] = 0;
    }
    count++;
  }
}
