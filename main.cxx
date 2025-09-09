#include <vector>
#include <cstring>
#include <cstdio>

using namespace std;


// Check if a number is a power of 2.
inline bool isPow2(int x) {
  return (x & (x-1)) == 0;
}


// Parse a binary string into a vector of bits.
inline vector<bool> parseBits(const char *str) {
  int N = strlen(str);
  vector<bool> bits(N);
  for (int i=0; i<N; i++)
    bits[N-1-i] = (str[i] == '1');
  return bits;
}


// Convert a vector of bits back into a binary string.
inline void stringifyBits(char *buf, const vector<bool> &bits) {
  int N = bits.size();
  for (int i=0; i<N; i++)
    buf[i] = bits[N-1-i]? '1' : '0';
  buf[N] = '\0';
}


// Calculate the number of parity bits needed for a given message length.
inline int hammingBitsNeeded(int M) {
  int R = 0;
  while ((1 << R) < (M + R + 1))
    R++;
  return R;
}


// Find the parity bit for a given position.
inline bool hammingBit(const vector<bool>& cod, int r) {
  int  C = cod.size();
  bool prty = false;
  for (int j=r; j<=C; ++j)
    if (j & r) prty ^= cod[j-1];
  return prty ^ cod[r-1];
}


// Add Hamming parity bits to the message.
inline vector<bool> addHammingBits(const vector<bool>& msg, int R) {
  int M = msg.size();
  int C = M + R;
  vector<bool> cod(C);
  for (int i=0, j=1; i<M; ++i) {
    while (isPow2(j)) j++;
    cod[(j++)-1] = msg[i];
  }
  for (int r=1; r<C; r<<=1)
    cod[r-1] = hammingBit(cod, r);
  return cod;
}


// Remove Hamming parity bits from the received code.
inline vector<bool> removeHammingBits(const vector<bool>& cod, int R) {
  int C = cod.size();
  int M = C - R;
  vector<bool> msg(M);
  for (int i=0, j=1; i<M; ++i) {
    while (isPow2(j)) j++;
    msg[i] = cod[(j++)-1];
  }
  return msg;
}


// Find the position of a single bit error in the received Hamming code.
inline int bitErrorPosition(const vector<bool>& cod, int R) {
  int C = cod.size();
  int p = 0;
  for (int r=1; r<C; r<<=1) {
    bool parity = hammingBit(cod, r);
    if (parity != cod[r-1]) p |= r;
  }
  return p-1;
}


// Main function.
int main() {
  char xmsg[256];
  printf("Enter the message bits: ");
  scanf_s("%s", xmsg, sizeof(xmsg));
  vector<bool> msg = parseBits(xmsg);
  int M = msg.size();
  int R = hammingBitsNeeded(M);
  printf("Message length: %d bits\n", M);
  printf("Number of parity bits: %d bits\n", R);
  vector<bool> cod = addHammingBits(msg, R);
  int  C = cod.size();
  char buf[256];
  stringifyBits(buf, cod);
  printf("Transmitted data length: %d bits\n", C);
  printf("Transmitted bits: %s\n", buf);
  printf("\n");

  // Simulate a single bit error in the transmitted code.
  int flip;
  printf("Enter bit position to flip to simulate error (0-%d): ", C - 1);
  scanf_s("%d", &flip, sizeof(flip));
  if (flip>=0 && flip<C) cod[flip] = !cod[flip];
  stringifyBits(buf, cod);
  printf("Received bits:    %s\n", buf);
  printf("\n");

  // Process received bits.
  int err = bitErrorPosition(cod, R);
  if (err>=0) printf("Single bit error detected at position: %d\n", err);
  else printf("No error detected.\n");
  if (err>=0 && err<C) cod[err] = !cod[err];
  stringifyBits(buf, cod);
  printf("Corrected bits:   %s\n", buf);
  vector<bool> rmsg = removeHammingBits(cod, R);
  stringifyBits(buf, rmsg);
  printf("Received message: %s\n", buf);
  printf("Received message length: %d bits\n", rmsg.size());
  return 0;
}
