# Task 10 – std::variant Benchmark

The captured one-million-element run reported equal totals (1,774,000,000), with variant 1.289 ms and virtual dispatch 3.383 ms. This is a measured result for the supplied program and environment. The PDF asks for a 10,000,000-element comparison against both prior implementations; the captured run is one million, so the ten-million variant measurement remains outstanding.

Compile: `g++ -std=c++17 -Wall -Wextra source.cpp -o program`; run: `./program`.
