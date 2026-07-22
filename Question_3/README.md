### Commands Executed:
1. `gcc -Wall secure_db.c -o secure_db`
2. `./secure_db`

### Explanations:
* **Direct POSIX I/O (`open` & `close`):** Bypasses high-level stdio buffering (`fopen`/`fprintf`) using POSIX system calls. File permissions set to `0600` restrict file access exclusively to the file owner at the OS level.
* **Low-Level Byte Serialization (`write` & `read`):** Transfers binary structures straight to disk memory layouts, preserving exact data structures while minimizing performance overhead.
* **Random File Access (`lseek`):** Uses relative offset math (`sizeof(Struct) * index`) with `SEEK_SET` to enable instant $O(1)$ random access updates without reading or rewriting full file contents.