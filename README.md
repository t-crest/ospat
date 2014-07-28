ospat
=====

An ARINC653 real-time operating system for the Patmos processor.

Examples
--------

The `examples` directory contains three sample applications running on ospat:

* `arinc653-1event-O1`: consists of a single partition made of 2 periodic and 2 sporadic threads synchronizing on an ARINC event
* `arinc653-1part`: consists of a single partition made of 2 periodic threads
* `arinc653-2parts`: consists of a 2 partitions each made of 2 periodic threads
* `arinc653-3parts`: consists of a 3 partitions of 1 periodic thread
* `arinc653-4parts`: consists of a 4 partitions of 1 periodic thread

Building
--------

Examples can be build using the build.sh script from the project's root directory:

```shell
sh build.sh {EXAMPLE}
```

Where `{EXAMPLE}` is the example's name (`arinc653-1event-O1`, `arinc653-1part`, `arinc653-2parts`, `arinc653-3parts`, `arinc653-4parts`)

Running
-------

After building an example `{EXAMPLE}` with `build.sh` a directory will be created in the project's root named `build-{EXAMPLE}`. Assuming that patmos simulator (`pasim`) and emulator (`patmos-emulator`) are in the path, the compiled application can be run with either:

```shell
pasim build-{EXAMPLE}/kernel.elf
```

or

```shell
patmos-emulator build-{EXAMPLE}/kernel.elf
```
