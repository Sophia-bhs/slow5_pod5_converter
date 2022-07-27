# Format Specification

## Pod5 Format 

Extensions: `.pod5`

Pod5 is the second file format released by ONT for nanopore signal data, Fast5 being the first. It is based on the Apache Arrow IPC file format, and it's scheme is the read data, which then has references to the various metadata and signal chunks, which get combined on a read call. In this manner the backend works a bit like a relational SQL database, however the front end API (though still under development) simplifies the access of reads. Reads can be processed with multiprocessing, and the Arrow backend will use all available threads of the machine to help with processing. Though Pod5 is great improvement upon Fast5, it is still not as efficient as SLOW5 for high throughput data processing, and its usability and compatibility is still lacking.

See [pod5 format specification][link to pod5 specs] for more.

## Slow5 format

Extensions: `.slow5`-(ASCII) `.blow5`-(binary) `blow5.idx`-(index) (like sam/bam/bai)

Slow5 is a community developed file format and scheme, created from scratch, specifically for nanopore signal data and associated metadata. It is 'thread-efficient', is faster the read than fast5, and has a smaller file size when using similar compression methods. It is specifically designed to reduce memory footprint, and work efficiently with both SSD/NVME and HDD disks and how they access data. This ensures workloads scale in a performant manner, unlike both fast5 and pod5.

See [slow5 format specification][link to slow5 specs] for more.

[link to pod5 specs]: https://github.com/nanoporetech/pod5-file-format/blob/master/docs/SPECIFICATION.md 
[link to slow5 specs]: https://hasindu2008.github.io/slow5specs/slow5-v0.2.0.pdf 