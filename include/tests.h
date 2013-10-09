int binary_decode(char *decoded, const char *encoded, int bits);
void binary_encode(char *encoded, const char *input, int bits);
void test(const int bits, const char *input_binary, const char *expected_encoded);
