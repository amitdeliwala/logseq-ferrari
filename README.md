Logseq rM Paper Pro Integration
===============================

This repository contains a minimal skeleton of a Qt Quick application for
the reMarkable Paper Pro tablet. The project integrates basic pen handling,
OCR processing, and a small Logseq CLI.

See the `logseq-rm` directory for the source code.

Building with the Ferrari SDK
-----------------------------

1. Install the Ferrari SDK under `~/sdk-ferrari` as described at <https://developer.remarkable.com/>.
2. Either source the environment script or pass the provided toolchain file:

```bash
source ~/sdk-ferrari/environment-setup-cortexa53-crypto-remarkable-linux
cmake -S logseq-rm -B build -GNinja
cmake --build build
```

or

```bash
cmake -S logseq-rm -B build -GNinja \
      -DCMAKE_TOOLCHAIN_FILE=logseq-rm/toolchains/ferrari.cmake
cmake --build build
```

The resulting binaries can then be deployed using `logseq-rm/deploy.sh`.
