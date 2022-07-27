# slow5_pod5_converter
slow5_pod5_converter is a conversion tool for converting (POD5->SLOW5). 

## Quick Start
Converting a pod5 file to a slow5 file. 

**Clone via ssh:**
```
git clone --recurse-submodules git@github.com:Sophia-bhs/slow5_pod5_converter.git
```

**Clone via https:**
```
git clone --recurse-submodules https://github.com/Sophia-bhs/slow5_pod5_converter.git 
```

**Compilation and Usage**
```
cd slow5_pod5_converter
make clean 
make p2s
./p2s path/to/input.pod5 path/to/output.blow5
```

**Please note**: The team at Oxford nanopore Technology are often updating their pod5-format module through new releases, and since we include their libraries within our module, it is important that we stay up to date with their changes. 
See there releases [here][releases page pod5].

**How to update a *pod5-format* to the latest release**
- create a directory in your local environment to hold the new pod5-format release 
- download and unzip the new release from the link above 
- replace pod5-format files/directories present in our repo with new release versions 

## Project Breakdown

The Pod5 file format, developed by Oxford Nanopore Technology, and Slow5 file format, developed by the team at Garvan Institute of Medical Research, both have their benefits, however slow5 format prevails in it's memory efficiency, scalability and it's variety of extensions. This project aims to establish a format conversion tool which will allows users to convert their pod5 files to slow5 and reap the technical benefits. The primary languages used to build this project are C and C++ which ensures a reliable, safe and, principally, a fast conversion. 

For more on the Pod5 and Slow5 formats visit SPECIFICATION.md

See [DESIGN.md][design.md link] for details on the structure of the project 

### Example data

Convert single pod5 file with 10 reads using slow5-pod5-converter. 

```
> mkdir test/mySlow5
> ./p2s test/examplefile.pod5 test/mySlow5/output.blow5 
```

# Inspecting results:

### How to view a slow5/blow5 file 

`slow5tools` is a toolkit developed by used to visualise and manipulate slow5 files.

**Install slow5tools**
Follow instructions on setup/install here: https://github.com/hasindu2008/slow5tools
Garvan's most recent release of slow5tools is *slow5tools-v0.5.0*.

```
> cd slow5tools-v0.5.0
> ./slow5tools view ../slow5_pod5_converter/test/mySlow5/output.blow5 | grep -v ^@ | | head -n 10 | cut -f1-7,9-16

#slow5_version  0.2.0
#num_read_groups        1
#char*  uint32_t        double  double  double  double  uint64_t        char*   double  int32_t uint8_t uint64_t
#read_id        read_group      digitisation    offset  range   sampling_rate   len_raw_signal  channel_number  median_before   read_number     start_mux       start_time
0000173c-bf67-44e7-9a9c-1ad0bc728e74    0       8192    21      1437.697632     4000    123627  109     183.107742     1093     4      4534321
002fde30-9e23-4125-9eae-d112c18a81a7    0       8192    4       1437.697632     4000    37440   463     174.630371     75       2       122095
006d1319-2877-4b34-85df-34de7250a47b    0       8192    6       1437.697632     4000    337876  489     193.573578     1053     4       4347870
00728efb-2120-4224-87d8-580fbb0bd4b2    0       8192    2       1437.697632     4000    161547  147     194.65097      657      2       7231572
007cc97e-6de2-4ff6-a0fd-1c1eca816425    0       8192    23      1437.697632     4000    505057  126     198.097534     1625     2       7820030
008468c3-e477-46c4-a6e2-7d021a4ebf0b    0       8192    4       1437.697632     4000    206976  2       219.046417     411      2       2510647
```

[design.md link]: https://github.com/Sophia-bhs/slow5_pod5_converter/blob/main/docs/DESIGN.md
[releases page pod5]: https://github.com/nanoporetech/pod5-file-format/tags
