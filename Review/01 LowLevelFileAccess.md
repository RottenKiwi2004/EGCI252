# Low Level File Access

** <u>File Descriptor</u> = Abstract key or reference for accessing a file; (File Pointer)

When program starts, three file descriptors are automatically opened

- `0: stdin`
- `1: stdout`
- `2: stderr`

## Interacting with files
* ### `open()` : Create new file descriptor
    #### Syntax:
    `int open(const char * path, int oflags);`

    `int open(const char * path, int oflags, mode_t mode);`

    - `path`: Path to file
    - `oflags`: Access mode and other optional flags <u>(use bitwise OR for multiple flags)</u>
    - `mode`: Set file permission (use with `OCREAT`)

    #### Return:
    - `-1` if fails
    - `File descriptor`

* ### `write()` : Write data from memory to file
    #### Syntax:
    `size_t write(int fd, const void *buf, size_t count);`

    - `fd`: File descriptor
    - `buf`: Pointer to the location of data
    - `count`: Number of bytes

    #### Return:
    - `-1` if error
    - `Number of bytes written`

* ### `read()` : Read data from file to memory
    #### Syntax:
    `size_t write(int fd, void *buf, size_t count);`

    - `fd`: File descriptor
    - `buf`: Pointer to the location of data
    - `count`: Number of bytes

    #### Return:
    - `-1` if error
    - `0` if End-Of-File `EOF`
    - `Number of bytes read`

* ### `close()` : Close system call; Terminate association between file descriptor and its file
    #### Syntax:
    `int close(int fd);`

    - `fd`: File descriptor

    #### Return:
    - `-1` if error
    - `0` if success

Example:
```c
int in, out, nread;
in = open("file.in", O_RDONLY);
out = open("file.out", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
while (
    (nread = read(in, block, sizeof(block) )) > 0
)
    write(out, block, nread);
return 0;
```

**<u>Note</u>:** Read & Write moves pointer of file descriptor

* ### `lseek()` : Set read / write pointer
    #### Syntax:
    `off_t lseek(int fd, off_t offset, int whence);`
    
    - `fd`: File descriptor
    - `offset`: length in bytes from ref. position
    - `whence`: specifies ref. position
        - `SEEK_SET`: beginning of file
        - `SEEK_CUR`: current position
        - `SEEK_END`: end of file

* ### `setbuf()`: Change buffering type
    #### Syntax:
    `void setbuf(FILE * fp, char * buf);`