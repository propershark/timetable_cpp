# Timetable

Purveyor of schedule information for transit agencies via GTFS feeds and WAMP procedures. This time in C++.


# Installation

This is the only compiled part of the server system. As such, it takes a bit more effort to install and set up. These are the steps I took to get a working application.

*NOTE: This project is configured to be compiled with `clang`. To use a different compiler (untested), simply edit line 5 of `Makefile` to be `CXX ?= compiler_name`. There are currently no compiler-specific flags, so everything else should work as-is.*

First, you'll need to download and compile [wamped](https://github.com/alvistar/wamped) and its dependency, [mpack](https://github.com/alvistar/mpack). It's easiest to clone msgpack into the `mpack` folder in `wamped`.

```bash
git clone https://github.com/propershark/wamped.git
cd wamped
git clone http://github.com/alvistar/mpack.git
```

Then, follow the build instructions from `wamped` to create the static libraries for your system. I've copied them here to make things simple.

```bash
mkdir build
cd build
cmake ..
make
```

After running `make`, the built libraries will be somewhat hidden away. It took me a while to find these, but we need to copy them into our `lib/` folder to link them properly when compiling `timetable`. Assuming you are in the directory for this repo (i.e., `../timetable`), and you cloned wamped to a sibling folder (i.e., `../wamped`), these commands *should* copy the library files properly.

```bash
cd /path/to/timetable/clone
cp ../wamped/build/source/wamped/libwamped.a      lib/
cp ../wamped/build/source/mpackCPP/libmpackcpp.a  lib/
cp ../wamped/build/mpack/src/mpack/libmpack.a     lib/
```

Note that the extension of the `lib*` files may depend on your system. Use tab completion in your shell and you should be able to find them pretty easily.

Now, to compile `timetable` itself, you should be able to run `make` and get a `timetable` executable.

```bash
make
./timetable
```


# Usage

Timetable is currently a dumb executable with no real capabilities. As such, it can be run with no arguments.

```
./timetable
```

As it develops, there will need to be configurations for finding GTFS files and configuring worker pools. These may be done at the command line

```
./timetable --gtfs ./data/gtfs.zip --workers 8
```

However, this will likely be done through a configuration file instead. Only time will tell.
