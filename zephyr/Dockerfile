FROM ubuntu:latest
ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update && apt-get upgrade
RUN apt-get install -y --no-install-recommends cargo ccache cmake curl \
  device-tree-compiler dfu-util file gcc gcc-arm-none-eabi gcc-multilib \
  gdb-multiarch git g++-multilib gperf libffi-dev libjpeg-dev \
  libnewlib-arm-none-eabi libsdl2-dev libssl-dev make musl-dev ninja-build \
  python3-dev python3-pip python3-setuptools python3-tk python3-wheel \
  qemu-system-arm unzip wget xz-utils zlib1g-dev

RUN pip3 install west

RUN west init /zephyrproject --mr v1.14.1
RUN cd /zephyrproject && west update
RUN pip3 install -r /zephyrproject/zephyr/scripts/requirements.txt

ENV ZEPHYR_BASE=/zephyrproject/zephyr/
ENV ZEPHYR_TOOLCHAIN_VARIANT=gnuarmemb
ENV GNUARMEMB_TOOLCHAIN_PATH=/usr/

## Add emulator wrapper files and set CMD to run the emulator

COPY emulator_files/* /
# Alternatively, run the /debug script
RUN chmod +x /debug
CMD ["sh", "/wrapper.sh", "/zephyr.elf"]

## Now build a project using the prepared toolchain

COPY toys /toys

# EITHER give --build-arg sample=... to select a sample application
ARG sample=subsys/shell/shell_module

# OR specify --build-arg proj=... to select a custom application
ARG proj="$ZEPHYR_BASE"samples/"$sample"

ARG build_path=$proj"/build/"

RUN mkdir -p $build_path && cd $build_path && cmake -GNinja -DBOARD=qemu_cortex_m3 ..
RUN cd $build_path && ninja all
RUN cp $build_path"/zephyr/zephyr.elf" /zephyr.elf
