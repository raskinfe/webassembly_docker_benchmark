(module
  (import "wasi_snapshot_preview1" "fd_write" (func $fd_write (param i32 i32 i32 i32) (result i32)))
  (import "wasi_snapshot_preview1" "fd_read" (func $fd_read (param i32 i32 i32 i32) (result i32)))
  (import "wasi_snapshot_preview1" "fd_seek" (func $fd_seek (param i32 i64 i32 i32) (result i32)))
  (import "wasi_snapshot_preview1" "fd_fdstat_get" (func $fd_fdstat_get (param i32 i32) (result i32)))

  (memory $memory 1)
  (data (i32.const 0) "Hello, WebAssembly!\n")

  (func $write_hello
    (i32.const 1) ; File descriptor for stdout
    (i32.const 4) ; Pointer to the string
    (i32.const 20) ; Length of the string
    (i32.const 0) ; Offset (unused)
    call $fd_write
  )

  (func $read_hello
    (i32.const 0) ; File descriptor for stdin
    (i32.const 4) ; Buffer to read into
    (i32.const 20) ; Buffer size
    (i32.const 0) ; Offset (unused)
    call $fd_read
  )

  (func $seek_beginning
    (i32.const 0) ; File descriptor for stdin
    (i64.const 0) ; Offset
    (i32.const 0) ; Whence (SEEK_SET)
    (i32.const 0) ; Result pointer (unused)
    call $fd_seek
  )

  (func $get_fd_flags
    (i32.const 0) ; File descriptor for stdin
    (i32.const 0) ; Result pointer (unused)
    call $fd_fdstat_get
  )

  (func $benchmark
    ;; Write to stdout
    call $write_hello

    ;; Read from stdin
    call $seek_beginning
    call $read_hello

    ;; Check file descriptor flags
    call $get_fd_flags
  )

  (start $benchmark)
)
