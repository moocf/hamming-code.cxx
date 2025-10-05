Find hamming code for message bits, corrupt a single bit, and then correct the error.

> Run this on: [OnlineGDB](https://onlinegdb.com/FueKuu9eL)

<br>


```bash
$ clang main.cxx
$ ./a.out

# Enter the message bits: 1001101
# Message length: 7 bits
# Number of parity bits: 4 bits
# Transmitted data length: 11 bits
# Transmitted bits: 10011100101
#
# Enter bit position to flip to simulate error (0-10): 8
# Received bits:    10111100101
#
# Single bit error detected at position: 8
# Corrected bits:   10011100101
# Received message: 1001101
# Received message length: 7 bits
```

<br>


```bash
$ clang main.cxx
$ ./a.out

# Enter the message bits: 10011100101
# Message length: 11 bits
# Number of parity bits: 4 bits
# Transmitted data length: 15 bits
# Transmitted bits: 100111000101111
#
# Enter bit position to flip to simulate error (0-14): 10
# Received bits:    100101000101111
#
# Single bit error detected at position: 10
# Corrected bits:   100111000101111
# Received message: 10011100101
# Received message length: 11 bits
```

<br>
<br>


[![](https://raw.githubusercontent.com/qb40/designs/gh-pages/0/image/11.png)](https://wolfram77.github.io)<br>
[![ORG](https://img.shields.io/badge/org-moocf-green?logo=Org)](https://moocf.github.io)
![](https://ga-beacon.deno.dev/G-G1E8HNDZYY:v51jklKGTLmC3LAZ4rJbIQ/github.com/moocf/hamming-code.cxx)
