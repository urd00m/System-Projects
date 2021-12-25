# Testing if Paging is Correct
It usually isn't necessary to test paging, if your code works then it works, if you have paging turned on

## Test with magic numbers 
```  unsigned *magic1=pointer_to_page(/*vaddr=*/0x00C00000);
   unsigned *magic2=pointer_to_page(/*vaddr=*/0x00C01000);

   set_page_table(/*vaddr=*/0x00C00000,/*paddr=*/0xB9000);
   set_page_table(/*vaddr=*/0x00C01000,/*paddr=*/0xB9000);

   *magic1=0xdeadbeef;
   *magic2=0xcafebabe;
   if (*magic1!=*magic2)
       PANIC("Paging test failed with %x != %x",*magic1, *magic2);```
