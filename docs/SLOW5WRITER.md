# Writing a Slow5 file 

## NAME

slow5_writer - writes data stored by pod5_reader to a slow5 file 

## SYNOPSIS

```
int slow5_writer(char *output_path, rec_t *pod5_data_records, size_t batch_row_count, file_status_t file_status)
```

## DESCRIPTION

`slow5_writer()`