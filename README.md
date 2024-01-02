# How to Use

- Link `ec` library into your project
- Using `ec`_xxx api record some data(see [testcase](ecounter/test/simple.cc))
- Attach with gdb, source `ecounter/script/ec.gdb` script file for loading custom function
- Use command `dump_ec_var <file_path> <var_name>` to dump record data
- Parsing records by `ecounter/script/parse.py` script (User can import this file for custom record data format)

# Example

In gdb context:
```
Breakpoint 2, _GLOBAL__sub_I_ec_inst_test () at /workspaces/embedded-counter/ecounter/test/simple.cc:19
19      }
(gdb) dump_ec_var ./test.dump test
$10 = "done!"
(gdb) 
```

In shell:
```
@savent404 ➜ embedded-counter (main) $ python ecounter/script/parse.py a.out 
Machine bit length: 64
Machine bit order: little
item_size: 0x00000004
item_cap: 0x0000000A
item_base: 0x5555555CF220
item_start: 0x5555555CF220
item_end: 0x5555555CF224
item_cap_end: 0x5555555CF248
items range: 0~1
items number: 1
parsing data...from: 0x00000040 to: 0x00000044 value: 0x00001234
parsing data...from: 0x00000044 to: 0x00000048 value: 0x00000000
parsing data...from: 0x00000048 to: 0x0000004C value: 0x00000000
parsing data...from: 0x0000004C to: 0x00000050 value: 0x00000000
parsing data...from: 0x00000050 to: 0x00000054 value: 0x00000000
parsing data...from: 0x00000054 to: 0x00000058 value: 0x00000000
parsing data...from: 0x00000058 to: 0x0000005C value: 0x00000000
parsing data...from: 0x0000005C to: 0x00000060 value: 0x00000000
parsing data...from: 0x00000060 to: 0x00000064 value: 0x00000000
parsing data...from: 0x00000064 to: 0x00000068 value: 0x00000000
0000: 0x00001234
```