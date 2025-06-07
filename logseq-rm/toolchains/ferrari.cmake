set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# Adjust these paths if your SDK is installed elsewhere
set(SDK_ROOT $ENV{HOME}/sdk-ferrari)
set(SYSROOT  ${SDK_ROOT}/sysroots/cortexa53-crypto-remarkable-linux)

set(CMAKE_C_COMPILER   ${SDK_ROOT}/sysroots/x86_64-remarkable-linux/usr/bin/aarch64-remarkable-linux-gcc)
set(CMAKE_CXX_COMPILER ${SDK_ROOT}/sysroots/x86_64-remarkable-linux/usr/bin/aarch64-remarkable-linux-g++)
set(CMAKE_SYSROOT      ${SYSROOT})

set(ENV{PKG_CONFIG_SYSROOT_DIR} ${SYSROOT})
set(ENV{PKG_CONFIG_PATH}        ${SYSROOT}/usr/lib/pkgconfig)

list(APPEND CMAKE_PREFIX_PATH ${SYSROOT}/usr/lib/cmake)
