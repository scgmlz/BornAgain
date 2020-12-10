#### BornAgain tests

All tests are under CTest control.

We usually run them with the command

```
ctest
```

There is little advantage in running ctest multi-threaded (flag `-j<n>`)
because each single simulation test uses multi-threading internally.

## How to debug

To find out how CTest is running a specific test, use

```
ctest -V -N -R <test_name>
```

The answer typically looks like

```
<build>/bin/<test_binary> --gtest_filter=<test_name>" <minor_options>
```

So we start the debugger with

```
gdb <build>/bin/<test_binary>
run --gtest_filter=<test_name>
```
