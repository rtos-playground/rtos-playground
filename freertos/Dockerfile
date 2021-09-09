FROM ubuntu:latest
ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update && apt-get upgrade
RUN apt-get install -y --no-install-recommends cargo ccache cmake curl \
  device-tree-compiler dfu-util file gcc gcc-arm-none-eabi gcc-multilib \
  gdb-multiarch git g++-multilib gperf libffi-dev libjpeg-dev \
  libnewlib-arm-none-eabi libsdl2-dev libssl-dev make musl-dev ninja-build \
  python3-dev python3-pip python3-setuptools python3-tk python3-wheel \
  qemu-system-arm unzip wget xz-utils zlib1g-dev

RUN git clone https://github.com/FreeRTOS/FreeRTOS.git --recurse-submodules

#run curl -L -k https://interactive.freertos.org/attachments/token/xupqqaau9ixtslj/?name=LPC1769_FreeRTOS_Plus_Featured_Demo_002.zip > demo.zip
#run unzip demo.zip
#run sed -i s/lpc17xx.h/LPC17xx.h/  /LPC1769_FreeRTOS_Plus_Featured_Demo_002/lpc17xx.cmsis.driver.library/Include/lpc17xx_*.h

## Add emulator wrapper files and set CMD to run the emulator

COPY emulator_files/* /
# Alternatively, run the /debug script
RUN chmod +x /debug
CMD ["sh", "/wrapper.sh", "/FreeRTOS.elf"]

## Now build a project using the prepared toolchain

COPY toys /toys

# specify --build-arg proj=... to select a custom application
ARG proj=/toys/stack_bof

ARG build_path=$proj"/build"
RUN cd $proj && make && cp $build_path"/FreeRTOS.elf" /
