# Writing a Slow5 file 

## NAME

slow5_writer - writes data stored by pod5_reader to a slow5 file 

## SYNOPSIS

```
int slow5_writer(char *output_path, rec_t *pod5_data_records, size_t batch_row_count, file_status_t file_status)
```

## DESCRIPTION

`slow5_writer()` opens a slow5 file, *output_path*, using *slow5_open()* and writes pod5 header data, using *slow5_hdr_write*, and, for each batch row tracked by *batch_row_count*, appends pod5 record data, pointed to by *pod5_data_records*, using *slow5_write*, to the slow5 file. This process is done one batch at a time. 

### Function calls 

**Note: A lot the functions called are from the slow5/slow5.h file (*link this*) included in slow5lib subdirectory**
```
void set_header_attr(slow5_file_t *sp, rec_t *pod5_data_records);
```
set_header_attr() - void function developed by us which adds, using *slow5_hdr_add()*, and sets, using *slow5_hdr_set()*, the pod5 header attributes and values, pointed to by *info_dic* which is a field in the *rec_t* struct pointed to by *pod5_data_records*, to store in the slow5 header struct, *sp->header*. 

```
void set_header_aux(slow5_file_t *sp);
```
set_header_aux() - void function developed by us which adds, using *slow5_aux_add*, the auxillary fields to the header, to then be written to the slow5 file pointed to by *sp*.

```
void set_record_primary_fields(slow5_rec_t *slow5_record, slow5_file_t *sp, rec_t pod5_data_record);
```
set_record_primary_fields() - void function developed by us which passes the *slow5_rec_t* struct pointed to by slow5_record initlialised in *slow5_writer()* using *slow5_rec_init()*. Let each primary field value in the *slow5_record* equal the corresponding primary field value in *pod5_data_record*.

```
void set_record_aux_fields(slow5_rec_t *slow5_record, slow5_file_t *sp, rec_t pod5_data_record);
```
set_record_aux_fields() - void function developed by us which sets aux field values in *pod5_data_record* to aux field values in *slow5_record* using *slow5_aux_set*.

## Return Value

Returns 0 upon successful batch write.
