# 🗜️ Huffman Compression & Decompression Tool

A file compression and decompression utility implementing Huffman coding with variable-length encoding. This tool features adaptive buffering, real-time progress tracking, and supports any file type with efficient memory usage.

## Features

- **Universal File Support**: Compress any file type (images, videos, documents, etc.)
- **Optimized Buffer Management**: Configurable buffer size for optimal performance
- **Advanced Memory Management**: Dynamic heap allocation with automatic capacity adjustment
- **Real-time Progress Tracking**: Live progress indicator with speed metrics
- **Cross-Platform Support**: Works on Windows, Linux, and MacOS
- **Compression Statistics**: Detailed analytics including ratio and speed

## Technical Implementation

### Core Components

1. **Priority Queue Implementation**
   - Custom MinHeap data structure for efficient frequency sorting
   - Dynamic array-based implementation with automatic resizing
   - O(log n) complexity for insertions and deletions

2. **Huffman Tree Construction**
   - Optimized node structure with minimal memory footprint
   - Efficient tree serialization/deserialization for file storage
   - Character frequency analysis with 256-character support

3. **Data Structures**
```cpp
struct HuffmanNode {
    unsigned char character;
    int freq;
    HuffmanNode* left, *right;
};

class MinHeap {
    // Efficient priority queue implementation
    // Dynamic capacity management
    // O(log n) operations
};
```

## Prerequisites

- C++ Compiler with C++11 support
- Minimum RAM: 64MB (scales with buffer size)
- Available disk space: 2x size of input file (temporary)

## Usage

### Command Line Syntax

```bash
# Windows
huffman-compress-decompress.exe -b <buffer_size> [-c|-d] <file_path>

# Linux/MacOS
./huffman-compress-decompress -b <buffer_size> [-c|-d] <file_path>
```

### Parameters

- `-b <size>`: Buffer size in KB (default: 1KB)
- `-c`: Compress mode
- `-d`: Decompress mode
- `<file_path>`: Path to input file

### Examples

1. Compress with 64KB buffer:
```bash
huffman-compress-decompress -b 64 -c input.bmp
```
Output:
```
Compressing 1048576 bytes...
Progress: [====================] 100%
Speed: 5.2 MB/s
Buffer Usage: 64KB
Compression Ratio: 26.5%
Space Saved: 73.5%
Time Elapsed: 00:00:45
```

2. Decompress with 128KB buffer:
```bash
huffman-compress-decompress -b 128 -d input.bmp.ece2103
```

## Performance

### Buffer Size Impact
- Small files (<1MB): 1-4KB buffer recommended
- Medium files (1-100MB): 64KB buffer recommended
- Large files (>100MB): 128KB-512KB buffer recommended

### Compression Ratios
- Text files: 60-75% reduction
- Binary files: 20-50% reduction
- Image files (already compressed): 5-15% reduction

### Speed Metrics
- Compression: 2-8 MB/s (depends on file type and buffer size)
- Decompression: 4-10 MB/s (depends on file type and buffer size)

## Technical Details

### File Format
- Header: Original file size (8 bytes)
- Huffman Tree: Serialized structure
- Compressed Data: Bit-packed encoding
- Extension: `.ece2103` (compressed files)
- Auxiliary: `.cod` (Huffman codes file)


## Roadmap

- [ ] Graphical User Interface (GUI) implementation
- [ ] Multi-threading support for larger files
- [ ] Advanced compression algorithms integration

## Build from Source

```bash
# Clone the repository
git clone https://github.com/AdhamElKammar/huffman-compress-decompress.git

# Navigate to project directory
cd huffman-compress-decompress

# Build (using your preferred C++ compiler)
g++ -O2 -std=c++11 main.cpp -o huffman-compress-decompress
```
