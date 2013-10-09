#include "binary.h"

static int read_ascii_bits(const unsigned char *ascii_bits, unsigned int bits) {
  unsigned char current;
  const unsigned char *end = ascii_bits + bits;
  int output = 0;

  for (; ascii_bits != end; ascii_bits++) {
    current = *ascii_bits;

    if (current == '1')
      output = (output << 1) | 1;
    else if (current == '0')
      output <<= 1;
    else
      return -1;
  }

  if (bits < 8)
    output <<= 8 - bits;

  return output;
}

int binary_decode(unsigned char *decoded,
                  const unsigned char *encoded,
                  unsigned int bits) {
  const unsigned char *end;
  unsigned int bytes = bits / 8,
               decoded_value,
               extra_bits = bits % 8;

  for (end = decoded + bytes; decoded != end; decoded++, encoded += 8) {
    decoded_value = read_ascii_bits(encoded,8);
    if (decoded_value == -1)
      return -1;

    *decoded = decoded_value;
  }

  if (extra_bits > 0) {
    bytes++;

    decoded_value = read_ascii_bits(encoded,extra_bits);
    if (decoded_value == -1)
      return -1;

    *decoded = decoded_value;
  }

  return bytes;
}


static void record_ascii_bits(unsigned char *output,
                              unsigned char byte,
                              unsigned int bits) {
  int bit;
  for (bit = 0; bit < bits; bit++, output++) {
    if ((byte >> (7 - bit)) & 1)
      *output = '1';
    else
      *output = '0';
  }
}

void binary_encode(unsigned char *encoded,
                   const unsigned char *input,
                   unsigned int bits) {
  const unsigned char *end;
  unsigned int bytes = bits / 8,
               extra_bits = bits % 8;

  for (end = input + bytes; input != end; encoded += 8, input++)
    record_ascii_bits(encoded,*input,8);

  if (extra_bits > 0)
    record_ascii_bits(encoded,*input,extra_bits);
}
