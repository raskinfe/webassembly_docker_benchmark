(module
  ;; Import the printHelloWorld function from the "env" module
  (func $printHelloWorld (import "env" "printHelloWorld") (result i32))

  ;; Declare a memory section with a single memory instance
  (memory 1)
  
  ;; Export the memory
  (export "memory" (memory 0))
  
  ;; Define the start function, which is invoked when the module is loaded
  (start $start)
  
  ;; Implementation of the start function
  (func $start
    ;; Call the imported printHelloWorld function
    (call $printHelloWorld)
    ;; Return 0 (optional, but added to satisfy the type signature)
    (i32.const 0)
  )
)
