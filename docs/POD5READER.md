# Reading a Pod5 file 

## NAME

pod5_reader - reads a pod5 file and stores field data in memory 

## SYNOPSIS

```
int pod5_reader(int argc, char *argv[]) 
```

## DESCRIPTION

`pod5_reader()` takes a input paramaters args - the pod5 file name - and passes them through various c_api functions associated with reading a pod5 file developed by Oxford Nanopore technology. This process is ran through a for loop where the pod5 data is read batch by batch, and then through a for loop again to store all the data of each row of each batch in a struct record. 

### Data Structures 

The *run_info_data_t* structure stores pod5 file header attributes and values. The structure has the following form:
```
typedef struct {
    size_t size;
    char const** keys;			// header attributes
    char const** values;		// header values	
} run_info_data_t;
```

The *rec_t* structure stores a parsed pod5 record. The structure has the following form:
```
typedef struct {
    char* read_id;		// the read ID
    float offset;		// the offset parameter for the calibration
    float scale;		// the scale parameter for the calibration
    double median_before;	// the median before level
    float range;		// the range of the calibrated channel in pA
    char* channel;		// the channel the pore type uses
    uint8_t well;		// the well the pore type uses
    uint64_t len_raw_signal;	// length of the raw signal array
    int16_t* raw_signal;	// the actual raw signal array
    int32_t read_number;	// the read number
    uint64_t start_sample;	// the start sample
    int16_t digitisation;	// the digitisation value used by the sequencer, equal to: adc_max-adc_min+1
    uint32_t read_group;	// the read group
    run_info_data_t *info_dic;	// run_info_data_t struct containing header data
} rec_t;
```

The *file_status_t* structure keeps track of the file's status during the conversion. The structure has the following form:
```
typedef enum {
    FILE_INIT = 0,	// file has not been initialised 
    FILE_MID = 1,	// file has been initialised
} file_status_t;
```

### Function calls 

**Note: Most of the functions and errors called are from the [pod5-format/include/c_api][c_api link] included in src directory**

```
run_info_data_t* run_info_to_flat_dic(RunInfoDictData_t *run_info_data)
```
run_info_to_flat_dic() - function was developed by us to store the header attributes and values of the pod5 file,in a separate typedef struct - *run_info_data_t* - , which is also stored in the rec_t struct, to then call when writing the slow5 file and supply it with the same header attributes and values. 
Upon successful completion run_info_to_flat_dic returns a pointer to the struct with type *run_info_data_t*.

```
int slow5_writer(char *output_path, rec_t *pod5_data_records, size_t batch_row_count, file_status_t file_status);
```
See [SLOW5WRITER.md][slow5writer.md link] for description

## Return Value

Upon successful completion, pod5_reader returns a non negative integer (>=0).

[c_api link]: https://github.com/nanoporetech/pod5-file-format/blob/master/c%2B%2B/pod5_format/c_api.h
[slow5writer.md link]: https://github.com/Sophia-bhs/slow5_pod5_converter/blob/main/docs/SLOW5WRITER.md

