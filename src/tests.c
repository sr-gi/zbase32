#include <stdio.h>
#include <stdlib.h>
#include "binary.h"
#include "tests.h"
#include "zbase32.h"


/*
 * Data that exceeds this size (in bytes) as a binary string will cause
 * a buffer overflow
 */
#define BUFFER_SIZE 512 /* bytes */


int main(int argc, char *argv[]) {
  test(0,"","");

  /*
   * Reference examples from
   * http://philzimmermann.com/docs/human-oriented-base-32-encoding.txt
   */
  test(1,"0","y");
  test(1,"1","o");
  test(2,"01","e");
  test(2,"11","a");
  test(10,"0000000000","yy");
  test(10,"1000000010","on");
  test(20,"10001011100010001000","tqre");
  test(24,"111100001011111111000111","6n9hq");
  test(24,"110101000111101000000100","4t7ye");
  /* This says 6im5sd in the spec, but the second to last quint is
   * 11010, which corresponds to 4. */
  test(30,"111101010101011110111101000011","6im54d");

  /* ASCII: "Lorem ipsum dolor sit amet, consectetur adipiscing elit." */
  test(448,
    "01001100011011110111001001100101011011010010000001"
    "10100101110000011100110111010101101101001000000110"
    "01000110111101101100011011110111001000100000011100"
    "11011010010111010000100000011000010110110101100101"
    "01110100001011000010000001100011011011110110111001"
    "11001101100101011000110111010001100101011101000111"
    "01010111001000100000011000010110010001101001011100"
    "00011010010111001101100011011010010110111001100111"
    "001000000110010101101100011010010111010000101110",
    "jtzzr3mprbwzyh5ipwoge55cp73nyh5jqoogn5mfqosnya5xp3"
    "3ska5wci48khtycf1g1hdjqpts15u8rb1sa4mwfa");

  return 0;
}


void test(const int bits, const char *input_binary, const char *expected_encoded) {
  static char decoded[BUFFER_SIZE],
              decoded_binary[BUFFER_SIZE],
              encoded[BUFFER_SIZE],
              input[BUFFER_SIZE];

  int encoded_length;

  binary_decode(input,input_binary,bits);

  encoded_length = zbase32_encode(encoded,input,bits);
  encoded[encoded_length] = '\0';
  if (strcmp(encoded,expected_encoded) != 0) {
    fprintf(stderr,"%s: Bad encode (%s)",expected_encoded,encoded);
    exit(1);
  }

  if (zbase32_decode(decoded,encoded,bits) < 0) {
    fprintf(stderr,"%s: Decode failed\n",expected_encoded);
    exit(1);
  }

  binary_encode(decoded_binary,decoded,bits);
  decoded_binary[bits] = '\0';

  if (strcmp(decoded_binary,input_binary) != 0) {
    fprintf(stderr,"%s: %s != %s\n",
      expected_encoded,
      decoded_binary,
      input_binary
    );
    exit(1);
  }
}
