#include "WProgram.h"

#include <Print.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <usb_desc.h>
#include <usb_dev.h>
#include <usb_rawhid.h>
#include <util/delay.h>

volatile uint8_t do_output = 0;
uint8_t buffer[64];

extern "C" int main(void) {
  int8_t r;
  uint8_t i;
  uint16_t val, count = 0;
  pinMode(13, OUTPUT);
  digitalWriteFast(13, HIGH);

  // Initialize the USB, and then wait for the host to set configuration.
  // If the Teensy is powered without a PC connected to the USB port,
  // this will wait forever.
  usb_init();
  while (!usb_configuration)
    ; /* wait */

  digitalWriteFast(13, LOW);
  delay(500);
  digitalWriteFast(13, HIGH);
  delay(100);
  digitalWriteFast(13, LOW);
  delay(100);
  digitalWriteFast(13, HIGH);
  delay(100);
  digitalWriteFast(13, LOW);

  // Wait an extra second for the PC's operating system to load drivers
  // and do whatever it does to actually be ready for input
  _delay_ms(1000);

  /* print("Begin rawhid example program\n"); */
  while (1) {
    // if received data, do something with it
    r = usb_rawhid_recv(buffer, 0);
    // quick blink to show status
    digitalWriteFast(13, HIGH);
    delay(100);
    digitalWriteFast(13, LOW);
    delay(100);
    digitalWriteFast(13, HIGH);
    delay(100);
    digitalWriteFast(13, LOW);

    if (r > 0) {
      // output 4 bits to D0, D1, D2, D3 pins
      // DDRD = 0x0F;
      // PORTD = (PORTD & 0xF0) | (buffer[0] & 0x0F);
      // ignore the other 63.5 bytes....
      /* print("receive packet, buffer[0]="); */
      /* phex(buffer[0]); */
      /* print("\n"); */
    }
    // if time to send output, transmit something interesting
    do_output = 0;
    // send a packet, first 2 bytes 0xABCD
    buffer[0] = 0xAB;
    buffer[1] = 0xCD;
    // put A/D measurements into next 24 bytes
    for (i = 0; i < 12; i++) {
      val = analogRead(i);
      buffer[i * 2 + 2] = val >> 8;
      buffer[i * 2 + 3] = val & 255;
    }
    // most of the packet filled with zero
    for (i = 26; i < 62; i++) {
      buffer[i] = 0;
    }
    // put a count in the last 2 bytes
    buffer[62] = count >> 8;
    buffer[63] = count & 255;
    // send the packet
    usb_rawhid_send(buffer, 50);
    /* print("transmit packet "); */
    /* phex16(count); */
    /* print(", r="); */
    /* phex(r); */
    /* print("\n"); */
    count++;
    delay(500);
  }
}
