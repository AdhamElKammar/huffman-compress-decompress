# Huffman Compressor and Decompressor (C/C++)


## Overview

This repository contains a C/C++ implementation of a Huffman compressor and decompressor. Huffman coding is a widely used lossless data compression technique that assigns variable-length binary codes to input symbols based on their frequencies. More frequent symbols receive shorter codes, leading to reduced data size without any loss of information.

This project provides:

* A command-line executable for compressing and decompressing files.
* A well-structured and commented C/C++ codebase demonstrating the Huffman algorithm.

## Features

* **Compression:** Compresses an input file into a smaller output file using Huffman coding.
* **Decompression:** Reconstructs the original file from its compressed version.
* **Dynamic Frequency Analysis:** Calculates symbol frequencies from the input data during compression.
* **Huffman Tree Construction:** Builds an optimal binary tree based on the calculated frequencies.
* **Code Generation:** Generates variable-length binary codes for each unique symbol.

## Getting Started

### Prerequisites

* A C/C++ compiler (e.g., GCC, Clang).
* CMake (optional, for build system management).

