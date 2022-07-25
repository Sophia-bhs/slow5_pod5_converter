# slow5_pod5_converter
slow5_pod5_converter is a conversion tool for converting (POD5->SLOW5). 

### Usage
Converting a pod5 file to a slow5 file. 
```
make clean 
make p2s
./p2s path/to/input.pod5 path/to/output.blow5
```

# Environment setup:

*Include instructions to setup the c and c++ related environments!!*

## Format Context 

### pod5:
Extensions: `.pod5`

Pod5 is the second file format released by ONT for nanopore signal data, Fast5 being the first. It is based on the Apache Arrow IPC file format, and it's scheme is the read data, which then has references to the various metadata and signal chunks, which get combined on a read call. In this manner the backend works a bit like a relational SQL database, however the front end API (though still under development) simplifies the access of reads. Reads can be processed with multiprocessing, and the Arrow backend will use all available threads of the machine to help with processing. Though Pod5 is great improvement upon Fast5, it is still not as efficient as SLOW5 for high throughput data processing, and its usability and compatibility is still lacking.

See SPECIFICATION.md for more details on the pod5 format. - **need to add link**

### slow5:
Extensions: `.slow5`-(ASCII) `.blow5`-(binary) `blow5.idx`-(index) (like sam/bam/bai)

Slow5 is a community developed file format and scheme, created from scratch, specifically for nanopore signal data and associated metadata. It is 'thread-efficient', is faster the read than fast5, and has a smaller file size when using similar compression methods. It is specifically designed to reduce memory footprint, and work efficiently with both SSD/NVME and HDD disks and how they access data. This ensures workloads scale in a performant manner, unlike both fast5 and pod5.

See SPECIFICATION.md for more details on the pod5 format. **need to add link**

## Project Breakdown

Conclusively the Pod5 and Slow5 file format both have their benefits, however Slow5 format prevails in it's memory efficiency, scalability and it's robustness across platforms. This project aims to establish is a format conversion tool which will allows users to convert their pod5 files to slow5 and reap the technical benefits. The primary languages used to build this project are C and C++ which ensures a reliable, safe and, principally, a fast conversion. 

#See [DESIGN.md][design.md link] for details on the structure of the project 

# Example data:

Download xxx.pod5 from xxx


[design.md link]: https://github.com/Sophia-bhs/slow5_pod5_converter/blob/main/docs/DESIGN.md
