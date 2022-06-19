# slow5_pod5_converter
slow5_pod5_converter is a conversion tool for converting (SLOW5<->POD5). 

### Usage
Converting a pod5 file to a slow5 file. 
```
./slow5tools p2s path/to/input.pod5 path/to/output.blow5
```

# Environment setup:
#### pod5:
Extensions: `.pod5`

Pod5 is the second file format released by ONT for nanopore signal data. It is based on the Apache Arrow IPC file format, and it's scheme is the read data, which then has references to the various metadata and signal chunks, which get combined on a read call. In this manner the backend works a bit like a relational SQL database, however the front end API (though still under development) simplifies the access of reads. Reads can be processed with multiprocessing, and the Arrow backend will use all available threads of the machine to help with processing. Overall, pod5 is better than fast5, however it is my opinion slow5 is a more scalable and memory efficient format.

#### slow5:
Extensions: `.slow5`-(ASCII) `.blow5`-(binary) `blow5.idx`-(index) (like sam/bam/bai)

Slow5 is a community developed file format and scheme, created from scratch, specifically for nanopore signal data and associated metadata. It is 'thread-efficient', is faster the read than fast5, and has a smaller file size when using similar compression methods. It is specifically designed to reduce memory footprint, and work efficiently with both SSD/NVME and HDD disks and how they access data. This ensures workloads scale in a performant manner, unlike both fast5 and pod5.

# Example data:

Download xxx.slow5 from xxx
