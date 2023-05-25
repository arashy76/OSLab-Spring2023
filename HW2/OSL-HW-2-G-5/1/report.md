# Testing Multiple Compression Algorithms and Tools

## Introduction
In this article, I'm attempting to analyze compression tools and algorithms on Linux. My topics are organized based on extensions (The conventional file suffix and usually directly related to file binary format and structure), and I provide detailed explanations of the tools and algorithms upon their first mention, with subsequent references to the complete explanations.

Due to the abundance of compression modes and degrees, all the tools have only been tested at their default settings. While this may not be fair to many tools and may not present the full picture, as some algorithms excel in terms of compression-rate over time ratio while others aim to push the boundaries of compression regardless of the ratio (in both speed and compression rate), it is essential to note that if their defaults were not well-determined to showcase their optimal performance, their strengths might not be evident. Additionally, some tools perform well under a wide range of conditions or their brilliant features require switches to be activated; Nevertheless It would be impractical for me to check all the modes for all the available tools, especially considering the vast number of options out there.

This work is motivated by my love toward studying different methods of compressing data, and although I have received assistance from AI generation tools, most of the work has been personally undertaken. Finally, the text has been edited to address grammatical and lexical issues and to enhance readability. I hope you enjoy reading it!

## Test Data
All the tools are tested on the provided file, "ingredient.csv," which may not be the best approach. Testing exclusively on a limited range of file formats, types, and entropy levels, and using just one file, is not ideal. As we will discover later, some tools leverage cross-file compression optimization or train on a set of similar data. Additionally, neural network-based compression would likely make testing more complex and less straightforward, and the only fair way to test them would be their real-life intended senario.
Name | Size | Entropy
-|-|-
`ingredient.csv` | 39M | 5.08/8

## What is Magic Number
A number used to fingerprint binary file types, used by tools like `file` commandline utility to detect file types.

## Formats, Their Tools and Possible Algorithms Under the Hood

### .LZMA (Lempel-Ziv-Markov chain Algorithm)
#### Information 
The name "LZMA" stands for Lempel-Ziv-Markov chain algorithm. It is a compression algorithm developed by Igor Pavlov in 1998 as an improvement over the existing LZ77-based compression methods using a sliding dictionary up to 4 GB in length for duplicate string elimination. The LZ stage is followed by entropy coding using a Markov-chain-based range coder and binary trees. LZMA is widely used in file compression utilities and formats, including 7z, XZ, and LZMA SDK. It's more known as algorithm used in `.7z` and `.lz` archive formats, but the pure implemention of it is also available by `xz`
#### Tools
- xz: xz utils (previously LZMA Utils), with command `xz` is mainly known for its format, `.xz` that we would get to later. Since version 5.0 onwards this package became available on windows as well. It's written in c.
- lzip: lzip uses the same algorithm, but not the same extension nor binary format, so its mentioned in its section
- 7z: similar to lzip
#### Results
##### Using `xz`
**Compression**:
```bash
xz --format=lzma ingredient.csv
```
or
```bash
lzma ingredient.csv # an alias to xz --format=lzma
```
user time | sys time | Output Size | Compression Ratio | Compression Ratio/Time
-|-|-|-|-|
 19.20 | 0.86 | 6.3M | 6.19 | 0.3
**Decompression**:
```bash
xz --format=lzma -d ingredient.csv.lzma
```
or
```bash
lzma -d ingredient.csv.lzma
```
user time | sys time 
-|-
0.361 | 0.021

### .LZ (Lzma Zip)
#### Information
Magic Number: 0x4C, 0x5A, 0x49, 0x50
`.lz` is the extension commonly used with lzip which uses LZMA under the hood.
#### Tools
The lzip suite of programs was written in C++ and C by Antonio Diaz Diaz and is being distributed as free software under the terms of version 2 or later of the GNU General Public License (GPL). It closely resemble other usual unix compression tools UX e.g.: bzip2 and gzip. 7-Zip was released in 2000; a tool employing LZMA first became available on Unix-like operating systems in 2004 when a port of the command-line version of 7-Zip (p7zip) was released. In the same year, the LZMA SDK became available, which included the program called "lzma_alone"; less than a year later, Lasse Collin released LZMA Utils, which at first only consisted of a set of wrapper scripts implementing a gzip-like interface to lzma_alone. In 2008, Antonio Diaz Diaz released lzip, which uses a container format with checksums and magic numbers instead of the raw LZMA data stream, providing a complete Unix-style solution for using LZMA. Nevertheless, LZMA Utils was extended to have similar features and then renamed to XZ Utils.
#### Results
##### Using `lzip`
**Compression**:
```bash
lzip ingredient.csv
```
user time | sys time | Output Size | Compression Ratio | Compression Ratio/Time
-|-|-|-|-|
 17.27 | 0.10 | 6.4M | 6.09 | 0.35
**Decompression**:
```bash
lzip ingredient.csv
```
user time | sys time
-|-
0.622 | 0.18

### .LZ4
#### Information
Magic number: 04 22 4d 18
The LZ4 algorithms aims to provide a good trade-off between speed and compression ratio. Typically, it has a smaller (i.e., worse) compression ratio than the similar LZO algorithm, which in turn is worse than algorithms like DEFLATE. However, LZ4 compression speed is similar to LZO and several times faster than DEFLATE, while decompression speed is significantly faster than LZO. LZ4 only uses a dictionary-matching stage (LZ77), and unlike other common compression algorithms does not combine it with an entropy coding stage (e.g. Huffman coding in DEFLATE). This format is only used for this algorithm and unlike many other extension/binary formats is not an umbrella for many other compression techniques.
#### Tools
LZ4 command line interface 64-bits, by Yann Collet works well, and is used till now. it also has multiple levels from 1 to 9 with switches in form of `-<number>`, and defaults to 1, unlike other utilites we saw, has a simple commandline util with few options, but like other cousins has an extra compressed mode (`-12` switch)
#### Results
**Compression**:
```bash
lz4 ingredient.csv
```
user time | sys time | Output Size | Compression Ratio | Compression Ratio/Time
-|-|-|-|-|
0.36007 | 0.07522 | 15M | 2.6 | 17.28
**Decompression**:
```bash
lz4 -d ingredient.csv.lz4
```
user time | sys time
-|-
0.020 | 0.021

### .ZIP
#### Information
At this point zip is an umbrella term for many zipping algos, even mixing them up in one file and abbreviating it as `.zip`. but there are 2 linux commands zip and unzip, to deal with zip files. To be clear, `.zip` is similar to C++ programming language, a vague idea of what it can mean, rather than what it surely is and work! These are the compression methods that may be hiding under a `.zip` file, based on one of the zip file standards, each one have some ID saved somewhere to tell which algorithm is actually used:
 - Deflate:
 Standard algorithm based on 32 kB LZ77 and Huffman coding. Deflate is found in several file formats including ZIP, gzip, PNG and PDF.
 - Deflate64
 Deflate64 is an extension of the Deflate algorithm designed to overcome the limitations of the original Deflate algorithm, particularly with respect to the maximum file size and the compressed size of large files. The main difference between Deflate and Deflate64 is the size of the sliding window used for compression. In Deflate, the sliding window is limited to 32KB, which means it can only reference a maximum of 32KB of data for finding repetitions. Deflate64 increases this window size to 64KB, allowing it to search for longer repetitive patterns in larger files.
 - LZMA
 - PPMd+ <!-- TODO -->
 - Bzip2
 - PKWare <!-- TODO -->
 - Zstd (support added as recent as 2020)
There are also lots of encryptions and hashing methods that may be used in `.zip` files. 
#### Tools 
There are so many many tools for working with .zip files, nearly all big general libs have support for .zip files as well.
#### Due to Lots of tools and encryption being used under the hood I wont benchmark this, because it would mean literally nothing.

### .GZ (Gnu Zip)
#### Information
Gzip, short for GNU zip, It employs a combination of the Deflate algorithm and a file format specification to achieve efficient compression and decompression. Gzip is a popular choice for compressing various types of files, including text documents, web pages, and specially due to program executables compression. It's better known in linux world and the first choice for simple tasks. Gzip was first created in 1992 by Jean-Loup Gailly and Mark Adler as a file compression utility for the Unix operating system. It was developed as a replacement for the compress utility, aiming to provide better compression ratios and faster performance.
#### Tools
##### gzip
is a widely used file compression utility, made by the same team who developed the standard to it. Gzip is compatible with multiple operating systems and is supported by most modern web browsers. it has it's own library and bineries. it supports sync and async output, for respectively more robust and faster experiences. it also has 9 levels from 1 to 9 which 9 is the best compression and 1 is the fastest. you can specify this with a `-<number>` switch in gzip commandline utility.
##### pigz (Parallel Implementation of GZip)
`pigz` as the acronym suggest, is a parallel take on gzip, for a faster compression and decompression speed. its made for modern multi-core cpus, and speeds gzip up dramatically. pigz also support zlib as compression format (.zz) with `-z` switch and compression to PKWare zip (.zip) with `-K` flag. it support sync mode as well, but obviously defaults to async. and also support huffman only mode. it supports all levels from 0 to 9 with an extra level -11 (zopfli) which is much slower but even denser. another cool feature it supports is independent block compression for robustness to file integrity damage and way more.
#### Results
##### using `gzip`
**Compression**:
```bash
gzip ingredient.csv
```
user time | sys time | Output Size | Compression Ratio | Compression Ratio/Time
-|-|-|-|-|
1.10 | 0.01 | 9.4M | 4.14 | 2.67
**Decompression**:
```bash
gzip -d ingredient.csv.gz
```
user time | sys time
-|-
0.180 | 0.023
##### using `pigz`
**Compression**:
```bash
pigz ingredient.csv
```
user time | sys time | Output Size | Compression Ratio | Compression Ratio/Time
-|-|-|-|-|
1.50 | 0.05 | 9.4M | 4.14 | 2.67
**Decompression**:
```bash
pigz -d ingredient.csv.gz
```
user time | sys time
-|-
0.111 | 0.029 

### .XZ (probably eXtreme Zip ?)
#### Information 
Magic number: FD 37 7A 58 5A 00
XZ is an improvement on LZMA algorithm, 
#### Tools
As mentioned above and as mentioned in LZMA section, the de-facto standard tool for working with XZ files is XZ Utils which used to be called as LZMA Utils, like most of other tools support multi-thread, 0 to 9 level of compression with normal `-<number>` switch form, and has two level of help available with 
 - `-h` or `--help`
 - `-H` or `--long-help`
it also support extreme mode for increasing compression ratio and options to write in stdout, list info about a file, test its integrity and way more. it also let you keep input file after compression with `-k`.
#### Results
**Compression**:
```bash
xz ingredient.csv 
```
user time | sys time | Output Size | Compression Ratio | Compression Ratio/Time
-|-|-|-|-
14.69| 0.08 | 6.3M | 6.19 | 0.42
**Decompression**: 
```bash
xz ingredient.csv 
```
user time | sys time
-|-
0.336 | 0.048

### .ZSTD (ZSTndarD)
#### Information 
The main target of zstd is real-time compression, not file compression, and tries to be the best compression in that space; In fact it's so fast that it's used to compress content on ram or swap, for faster info retrival, by zram and zswap kernel modules. The library offers in ram compression and decompression functionality. It's developed by Yann Collet at Facebook and dual-licensed under BSD and GPLv2.
#### Tools
The only tool available as far as I found is the original one developed by facebook, there are 19 compression level to it. When no argument is provided it would read standard input. It has a very fine-grained low-level control to the inner working of it, and let you pick a training data set for its dictionary or even provide it with a dictionary for better compression. It has so many switches, only in commandline utils, that its mind-bending and overkill for nearly all use-cases. it also supports extra levels in `--ultra` mode, but requires more memory for it. obviously it supports working with block devices as well. it can even adapt its compression rate to IO speed, which is crazy cool.
#### Results
**Compression**
```bash
zstd -z ingredient.csv
```
user time | sys time | Output Size | Compression Ratio | Compression Ratio/Time
-|-|-|-|-|
0.183 | 0.034 | 9.3M | 4.19 | 19.3
**Decompression**
```bash
zstd -d ingredient.csv.zst
```
user time | sys time
-|-
0.097 | 0.056

### .LRZ
#### Information
The format used by `lrzip` program, it may use any of the following encryption algorithms:
- LZMA (default, explained above)
- LZO `-l` (ultra fast, faster than zstd, but very low compression)
Lempel-Ziv-Oberhumer or LZO is a lossless data compression algorithm that is focused on decompression speed.
- ZPAQ `-z` (very slow, but great compression) <!-- TODO  -->
- BZIP `-b` (explained above)
- GZIP `-g` (explained above, uses zlib)
#### Tools
lrzip is the tool for lrz format, it supports levels 1-9 for compression but the flag unlike most other tools uses `-L <number>` format instead of `-<number>` format which in my opinion is more semantic, you can set the process nice through flags as well, and default is 19, which means there is lots of place for improvement of default speed
#### Results
**Compression**:
```bash
lrzip ingredient.csv
```
user time | sys time | Output Size | Compression Ratio | Compression Ratio/Time
-|-|-|-|-|
 17.55 | 0.73 | 6.8M | 5.73 | 0.31
**Decompression**:
user time | sys time
-|-
0.46 | 1.01

### .RAR (Roshal ARchive)
#### Information 
Unlike rest of the items mentioned above, which were fully open-source and free, this one is actually a property software licensed by winrar GmbH. It was initially developed in 1993 by Russian software engineer Eugene Roshal. For linux users, there is freeware and an opensource implemention available, but the freeware functionality is better than open-source version of it. And for windows, there is winrar, which is famous for everyone ignoring its demands to be licensed.
#### Tools
##### rar and unrar
It allows you to create RAR archives with various compression options, including solid compression, password protection, and recovery records. However, please note that `rar` is not open source and may require a license for full functionality.
##### unrar
`unrar` and `rar` are proprietary utilities developed by RARLAB. these tools can extract and make `.rar` archives and are optimized for performance and reliability. `unrar` and `rar` support various features, including solid compression, archive locking, and optional encryption. These are available as a command-line tool and has versions for different operating systems, including Linux, macOS, and Windows. However, `unrar` and `rar` are not open source, and some versions may require a license for full functionality.
##### unar
`unar` is an open-source utility developed by Dag Ågren. It supports a wide range of archive formats, including RAR, ZIP, TAR, and 7z. It is designed to be simple and straightforward, offering a user-friendly interface and automatic format detection. `unar` can handle both single-file and multi-part archives and supports password-protected archives. It is available for various platforms, including Linux, macrar a ingredient.csv.rar ingredient.csv OS, and Windows.
#### Results
##### using `rar`
**Compression**:
```bash
rar a ingredient.csv.rar ingredient.csv 
```
user time | sys time | Output Size | Compression Ratio | Compression Ratio/Time
-|-|-|-|-|
8.73 | 0.22 | 7.7M | 5.06 | 0.56
##### using `unrar`
**Decompression**:
```bash
unrar ingredient.csv.rar
```
user time | sys time
-|-
0.164 | 0.027
##### using `unar`
**Decompression**:
```bash
unar ingredient.csv.rar
```
user time | sys time
-|-
0.400 | 0.076


## Conclusions
For my daily use, I used to rely on `xz` and `gzip`. However, after conducting this research, I have discovered the benefits of using `zstd` and `lrzip` as well. I have particularly found `zstd` to be highly effective in time-demanding scenarios such as full SSD compression and zram.
It is important to note that this research does not cover all the available tools, formats, and algorithms. Instead, it is aimed at intermediate-level Linux users as a starting point for learning and further exploration. It also serves as a personal guide for me to refer back to in the future.
There are widely-used archive makers such as tar and cpio that are commonly used in combination with compression tools. Recently, there have been emerging utility tools that aim to streamline the usage of various formats, algorithms, and binary structures into a single command-line interface, making it more convenient for end-users (e.g.: `ouch`). I had to pass over both of those topics to meet the deadline.


<!-- TODO  -->

<!-- collect all magic numbers -->
<!-- in tect todo -->
<!-- per section check -->
<!-- best and worst benchmark -->
<!-- bench mean -->

<!-- ### .BZ2
#### Information
The algorithm behind this format is Burrows-Wheeler algorithm. 
#### Tools
##### bzip
`bzip2` is the utility for 
##### 7z lrzip all zip opener 
#### Results
**Compression**
```bash
bzip2 ingredient.csv
```
user time | sys time | Output Size | Compression Ratio | Compression Ratio/Time
-|-|-|-|-|
2.28 | 0.04 | 6.7M | 5.82 | 2.5
**Decompression**
```bash
bzip2 -d ingredient.csv
```
user time | sys time
-|-
0.891 | 0.054 -->
<!-- ### Compress ? 
#### History 
(TODO: test)  -->
<!-- ### .7Z (7zip)
#### Information 
7zip actually uses LZMA under the hood, atleast by default. but the file structure may be a bit different. so its better to research more about it before trying to open sensetive data, because maybe file structure be different.
The other algorithms it supports are:
 - LZMA2: modified version of LZMA providing better multithreading support and less expansion of incompressible data.
 - Bzip2: The standard Burrows-Wheeler transform algorithm. Bzip2 uses two reversible transformations; BWT, then Move to front with Huffman coding for symbol reduction (the actual compression element).
 - PPMd Dmitry Shkarin's 2002 PPMdH (PPMII (Prediction by Partial Matching with Information Inheritance) and cPPMII (complicated PPMII)) with small changes: PPMII is an improved version of the 1984 PPM compression algorithm (Prediction by Partial Matching).
 - DEFLATE: 7-Zip contains a from-scratch DEFLATE encoder that frequently beats the de facto standard zlib version in compression size, but at the expense of CPU usage. for more info on DEFLATE, check its section in `.zip` file -->