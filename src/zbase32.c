#include <stdio.h>
#include "binary.h"
#include "zbase32.h"

#define ALPHABET "ybndrfg8ejkmcpqxot1uwisza345h769"

int zbase32_decode(char *decoded, const char *encoded, int bits) {
  return 0;
}


void debug_print_char(int intvalue) {
  char value_bits[6];
  int value = intvalue << 3;

  binary_encode(value_bits,&value,5);
  value_bits[5] = '\0';

  printf("> %s (%d) => %c\n",value_bits,intvalue,ALPHABET[intvalue]);
}

int zbase32_encode(char *encoded, const char *input, int bits) {
  char debug_msg[1000], debug_bytes[1000];
  int debug_bits;

  char *output = encoded;

  int character_index,
      excess_bits,
      unencoded_bits = bits,
      working_bits = 0,
      working_bit_count = 0;

  while (unencoded_bits > 0) {
    debug_bytes[0] = (char)(working_bits >> 8);
    debug_bytes[1] = (char) working_bits;
    binary_encode(debug_msg,debug_bytes,16);
    debug_bytes[16] = '\0';

    printf("* We have %d bits (%s), there are %d bits left to process\n",
      working_bit_count,
      debug_msg,
      unencoded_bits
    );

    if (working_bit_count >= 5) {
      /* There are enough bits in working_bits to encode a character */

      excess_bits = working_bit_count - 5;

      character_index = (working_bits >> excess_bits) & 31;
      *output = ALPHABET[character_index];
      output++;

      debug_print_char(character_index);

      working_bit_count = excess_bits;
      unencoded_bits -= 5;
    } else if (unencoded_bits == working_bit_count) {
      /* There are no more bits beyond those in working_bits */

      character_index = (working_bits << (5 - unencoded_bits)) & 31;
      *output = ALPHABET[character_index];
      output++;

      debug_print_char(character_index);

      break;
    } else if ((unencoded_bits - working_bit_count) >= 8) {
      /* Add a byte of input to working_bits */

      binary_encode(debug_msg,input,8);
      debug_msg[8] = '\0';
      printf("< Fetching a byte: %s\n",debug_msg);

      working_bits = (working_bits << 8) | (*input & 255);
      working_bit_count += 8;
      input++;
    } else {
      /* Add trailing input bits to working_bits */

      excess_bits = bits % 8;

      working_bits = (working_bits << excess_bits) |
                     ((*input >> (8 - excess_bits)) &
                      ((1 << excess_bits) - 1));
      working_bit_count += excess_bits;

      debug_bits = working_bits << (8 - excess_bits);
      binary_encode(debug_msg,&debug_bits,excess_bits);
      debug_msg[excess_bits] = '\0';
      printf("< Fetching %d trailing bits: %s\n",excess_bits,debug_msg);
    }
  }

  return (output - encoded);
}
