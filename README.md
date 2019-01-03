# UUID4

A drop-in two files library to generate version 4 UUIDs.

⚠ The underlying PRNG is SplitMix which makes UUIDs produced by this library
trivially predictable. But if you're willing to generate secure "tokens", that's
not what UUIDs are made for anyway 🤷‍♂️

Supported platforms:

- Windows
- Linux
- Mac
- iOS
- Android

Just drop `uuid4.h` and `uuid4.c` into your build and get started. (see also
[customizing compilation])

[customizing compilation]: #customizing-compilation

--------------------------------------------------------------------------------

## Usage

- `uuid4_seed()` seeds the version 4 UUID generator.
- `uuid4_gen()` generates a version 4 UUID.
- `uuid4_to_s()` converts a version 4 UUID into a string.

Example usage:

```
#include <stdio.h>
#include <uuid4.h>

int main()
{
  UUID4_STATE_T state;
  UUID4_T uuid;

  uuid4_seed(&state);
  uuid4_gen(&state, &uuid);

  char buffer[UUID4_STR_BUFFER_SIZE];
  if (!uuid4_to_s(uuid, buffer, sizeof(buffer)))
    exit(EXIT_FAILURE);

  printf("%s\n", buffer);

  return EXIT_SUCCESS;
}
```

--------------------------------------------------------------------------------

## Customizing compilation

You can customize the library's behavior by defining the following macros:

- `UUID4_FUNCSPEC`
- `UUID4_PREFIX`
- `UUID4_ASSERT`

## Compiling for Windows

There is a Visual Studio 2015 solution in the `_win-vs14/` folder.

## Compiling for Linux or Mac

There is a GNU Make 3.81 `MakeFile` in the `_gnu-make/` folder:

    $ make -j -C _gnu-make/

## Compiling for Mac

See above if you want to compile from command line. Otherwise there is an Xcode
project located in the `_mac-xcode/` folder.

## Compiling for iOS

There is an Xcode project located in the `_ios-xcode/` folder.

If you prefer compiling from command line and deploying to a jailbroken device
through SSH, use:

    $ make -j -C _gnu-make/ platform=ios architecture=arm64 CC="$(xcrun --sdk iphoneos --find clang) -isysroot $(xcrun --sdk iphoneos --show-sdk-path) -arch arm64" postbuild="codesign -s 'iPhone Developer'"

## Compiling for Android

You will have to install the Android NDK, and point the `$NDK_ROOT` environment
variable to the NDK path: e.g. `export NDK_ROOT=/opt/android-ndk` (without a
trailing `/` character).

Next, the easy way is to make a standalone Android toolchain with the following
command:

    $ $NDK_ROOT/build/tools/make_standalone_toolchain.py --arch=arm64 --api 21 --install-dir=/tmp/android-toolchain

Now you can compile the example by running:

    $ make -j -C _gnu-make/ platform=android architecture=arm64 CC=/tmp/android-toolchain/bin/aarch64-linux-android-gcc CXX=/tmp/android-toolchain/bin/aarch64-linux-android-g++

--------------------------------------------------------------------------------

If you find this library useful and decide to use it in your own projects please
drop me a line [@gpakosz].

[@gpakosz]: https://twitter.com/gpakosz
