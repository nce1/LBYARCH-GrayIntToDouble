# Grayscale Image Conversion Project

## Overview
A grayscale image is internally represented as a 2 dimensional array. Size is defined by the number of pixels in a row (width), and number of pixels in a column (height). Each cell represents the pixel value. Pixel values in grayscale are represented as white, black, and shades of gray using different numerical data type representation depending on the library used.

Some Libraries represent using 8 bit unsigned integer. 0 for black, 255 for white, 64 light gray, 191 dark gray, and all other gray values in between.
Some Image Processing Libraries represent grayscale images as having double float based pixel values between 0 to 1. 0 for black, 1 for white, 0.25 light gray, 0.75 darker gray, and all other gray values in between.

## Implementation
This project uses **C** to collect inputs, allocate memory, and print output. The C program acts as the driver. It manages user input for image dimensions (width and height) and ensures that sufficient memory is dynamically allocated using `malloc`.

The core computational logic is offloaded to an external **x86-64 assembly file**. This assembly module receives the total number of pixels and a pointer to the image array and iterates through every pixel. Thus, the routine runs in linear time, O(n). It converts the integer image value to a double precision float using the following formula:

$$f = \frac{\text{pixel}}{255.0}$$

To evaluate performance differences, the same computational logic was also implemented in C for comparison with the x86-64 assembly version. This implementation also operates in O(n).

## Test Results
The two implementations were tested with four text files: the first three, which increased in size, to evaluate execution efficiency, and the last one to verify correctness.
*Note: Full data can be viewed at the bottom*

### 1. Small Scale Test (10 * 10)
* **Total Pixels:** 100
* **Correctness:** Both implementations accurately converted the integer inputs to their double-precision equivalents. Edge cases were verified successfully; for example, `0` mapped correctly to `0.00` and `255` mapped to `1.00`.
* **Performance:** The execution time for both implementations was identical and consistently recorded as `0.000 seconds` across all 30 test runs. With only 100 pixels to iterate through, this instantaneous result is expected.

### 2. Medium Scale Test (100 * 100)
* **Total Pixels:** 10,000
* **Correctness:** The conversion logic remained consistent and accurate across all 10,000 data points, mirroring the small-scale test. Edge case mapping (0 and 255) remained correct, and the input pixel count matched the output pixel count.
* **Performance:** Similar to the 10x10 case, the processing time remained negligible. All 30 runs for both implementations recorded a time of `0.000 seconds`.

### 3. Large Scale Test (1000 * 1000)
* **Total Pixels:** 1,000,000
* **Correctness:** Validity checks confirmed that arithmetic precision is maintained even at high volume. All inputs, including boundary values, were converted correctly. The input had the same number of pixels as the output.
* **Performance:** At this volume, the difference in the processing time became noticable. The C program consistely recorded results from `0.002` to `0.003`. Meanwhile, the assembly implementation was slightly slower with a recorded range from `0.004` to `0.005`. 

### 4. Correctness Test (16 x 16)
* **Total Pixels:** 256
* **Correctness:** The output appeared as expected for both implementations, confirming the intended mapping: an input of `0` corresponds to an output of `0.0`, and an input of `255` corresponds to an output of `1.0`. The double-precision output increases proportionally from `0.0` to `1.0` as the input increases from `0` to `255`. Since the double-precision output is limited to two decimal places, some distinct integer inputs, such as `0` and `1`, produce the same output value.

### Overall Analysis
The test results demonstrate that the x86-64 assembly module is highly optimized for this floating-point operation. For small and medium datasets, the computational cost is effectively zero relative to the system clock resolution. Notably, initializing the input array took way more time. Even at the large scale (1 million pixels), the conversion takes less than 5 milliseconds on average. The observation that initialization time exceeds conversion time indicates that the primary bottleneck of the program is memory access and I/O overhead, rather than the computational logic itself.

However, from the results, C outperformed the x86-64 assembly module in all thirty test runs. This is likely because modern processors like the Ryzen 7 5800U used for testing are highly optimized for compiler-generated code. The C compiler can automatically apply instruction scheduling, loop unrolling, and vectorization to take advantage of the CPU’s SIMD instructions and wide execution units. It also manages memory access efficiently, using caching and prefetching to reduce delays from memory reads and writes. In contrast, hand-written assembly, while optimized for a specific sequence of operations, may not fully utilize these microarchitectural features. As a result, the compiler-generated C code can sometimes outperform the assembly version, even when performing the same calculations.
## Appendix

**Results Table**
| 10*10 (x86) | 10*10 (C) | 100*100 (x86) | 100*100 (C) | 1000*1000 (x86) | 1000*1000 (C) |
| :---: | :---: | :---: | :---: | :---: | :---: |
| 0.000 | 0.000 | 0.000 | 0.000 | 0.004 | 0.003 |
| 0.000 | 0.000 | 0.000 | 0.000 | 0.004 | 0.003 |
| 0.000 | 0.000 | 0.000 | 0.000 | 0.004 | 0.003 |
| 0.000 | 0.000 | 0.000 | 0.000 | 0.004 | 0.003 |
| 0.000 | 0.000 | 0.000 | 0.000 | 0.005 | 0.002 |
| 0.000 | 0.000 | 0.000 | 0.000 | 0.004 | 0.002 |
| 0.000 | 0.000 | 0.000 | 0.000 | 0.004 | 0.002 |
| 0.000 | 0.000 | 0.000 | 0.000 | 0.004 | 0.003 |
| 0.000 | 0.000 | 0.000 | 0.000 | 0.005 | 0.002 |
| 0.000 | 0.000 | 0.000 | 0.000 | 0.004 | 0.003 |
| 0.000 | 0.000 | 0.000 | 0.000 | 0.004 | 0.002 |
| 0.000 | 0.000 | 0.000 | 0.000 | 0.004 | 0.002 |
| 0.000 | 0.000 | 0.000 | 0.000 | 0.004 | 0.002 |
| 0.000 | 0.000 | 0.000 | 0.000 | 0.005 | 0.003 |
| 0.000 | 0.000 | 0.000 | 0.000 | 0.005 | 0.003 |
| 0.000 | 0.000 | 0.000 | 0.000 | 0.004 | 0.002 |
| 0.000 | 0.000 | 0.000 | 0.000 | 0.004 | 0.002 |
| 0.000 | 0.000 | 0.000 | 0.000 | 0.005 | 0.003 |
| 0.000 | 0.000 | 0.000 | 0.000 | 0.004 | 0.003 |
| 0.000 | 0.000 | 0.000 | 0.000 | 0.004 | 0.003 |
| 0.000 | 0.000 | 0.000 | 0.000 | 0.004 | 0.003 |
| 0.000 | 0.000 | 0.000 | 0.000 | 0.005 | 0.003 |
| 0.000 | 0.000 | 0.000 | 0.000 | 0.004 | 0.003 |
| 0.000 | 0.000 | 0.000 | 0.000 | 0.004 | 0.003 |
| 0.000 | 0.000 | 0.000 | 0.000 | 0.005 | 0.003 |
| 0.000 | 0.000 | 0.000 | 0.000 | 0.004 | 0.002 |
| 0.000 | 0.000 | 0.000 | 0.000 | 0.004 | 0.002 |
| 0.000 | 0.000 | 0.000 | 0.000 | 0.004 | 0.002 |
| 0.000 | 0.000 | 0.000 | 0.000 | 0.004 | 0.003 |
| 0.000 | 0.000 | 0.000 | 0.000 | 0.005 | 0.003 |

**Output of Fourth _testOutput.txt_**
![Correctness of Output](image/CorrectnessOutput.png)

**Demo Link:** [YouTube](https://youtu.be/dWhsBFfm3FA)
