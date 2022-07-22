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

*Explanation here*
```
static inline double realtime(void) {
    struct timeval tp;
    struct timezone tzp;
    gettimeofday(&tp, &tzp);
    return tp.tv_sec + tp.tv_usec * 1e-6;
}
```

*Explanation here*
```
typedef struct {
    size_t size;
    char const** keys;
    char const** values;
} run_info_data_t;
```

*Explanation here*
```
typedef struct {
    char* read_id;
    float offset;
    float scale;
    float median_before;
    float range;
    uint16_t channel;
    uint8_t well;
    uint64_t len_raw_signal;
    int16_t* raw_signal;
    uint32_t read_number;
    uint64_t start_sample;
    int16_t digitisation;
    uint32_t read_group;
    run_info_data_t *info_dic;
} rec_t;
```

*Explanation here*
```
typedef enum {
    FILE_INIT = 0,
    FILE_MID = 1,
    FILE_END = 2,
} file_status_t;
```

### Function calls 

**Note: Most of the functions and errors called are from the pod5-format/include/c_api (*link this*) included in src directory**

```
run_info_data_t* run_info_to_flat_dic(RunInfoDictData_t *run_info_data)
```
run_info_to_flat_dic() - function was developed by us to store the header attributes and values of the pod5 file,in a separate typedef struct - *run_info_data_t* - , which is also stored in the rec_t struct, to then call when writing the slow5 file and supply it with the same header attributes and values. 
Upon successful completion run_info_to_flat_dic returns a pointer to the struct with type *run_info_data_t*.

```
int slow5_writer(char *output_path, rec_t *pod5_data_records, size_t batch_row_count, file_status_t file_status);
```
See (*link to SLOW5WRITER.md*) for description

## Return Value

Upon successful completion, pod5_reader returns a non negative integer (>=0).


