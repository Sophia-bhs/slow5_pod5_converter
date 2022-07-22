# Slow5_pod5_converter Project Design

## Design Goals

- Easy to comprehend and execute compilation and usage 
- Fast and reliable conversion 
- Consistent across various platforms and compilers
- Use minimal/controllable memory for peak memory effiicency

### Easy to comprehend and execute compilation and usage 

Aided by:
- Well documented environment setup considering different computing systems 
- A succinct and detailed makefile which will allow users to run "make" rather than a convulated compilation command
- Usage command takes a maximum of two arguments - the infile and outfile
- Informative and detailed error messages that span all aspects of the execution 

### Fast and reliable conversion

Aided by:
- Writing the src code in the C programming languagea, low-level time-efficient programming language, as well as referencing the appropriate c_apis and libraries 
The program should ideally be able to to convert a pod5 file of 4000 reeds to slow5 in under 10 seconds.


### Consistent across various platforms 

Aided by:
- A well documented environment setup which considers running the program on different computing systems (linux/windows/MacOS)
- Slow5 which works efficiently with both SSD/NVME and HDD disks and how they access data
- Makefile which keeps the compilation method consistent across all platforms 

### Use minimal/controllable memory for peak memory effiicency

Aided by:
- Coding in the C programming language allows us to dynamically allocate memory across structures to store reads and their records 
- The above ensures we do not use unnecessary space or memory, keeping it minimal

## Program structure 

The core of the project is based in the src directory which contains our src code for the project:
- Pod5_reader.c/h (*link this to pod5_reader.md*) which reads an inputted Pod5 file 
- Slow5_writer.c/h (*link this to slow5_writer.md*) which writes Pod5 data to a slow5 formatted file 

main->(pod5_reader->slow5_writer)x(number of batches)->pod5_reader->main (*write this elegantly*)
