# Exporting TiCOS variables
export ARCH=patmos
export POK_PATH=`pwd`

echo "[SH] Reading input data"
EXAMPLE=$1

echo "[SH] Creating build directory"
mkdir -p build-${EXAMPLE}

# Moving to elf2uart directory, creating build dir and building
echo "[SH] Creating elf2uart utility"
cd $POK_PATH/elf2uart/
mkdir -p build
cd build
cmake ..
make
cp elf2uart $POK_PATH/build-${EXAMPLE}/elf2uart

# Moving to kernel directory
cd $POK_PATH

echo "[SH] Building example ${EXAMPLE}"
# Moving to sample application and building it
cd ./examples/${EXAMPLE}/generated-code
make
cd $POK_PATH
mv ./examples/${EXAMPLE}/generated-code/cpu/part1/part1.elf ./build-${EXAMPLE}/part1.elf

if [ "${EXAMPLE}" = "arinc653-2parts" ]; then
  mv ./examples/${EXAMPLE}/generated-code/cpu/part2/part2.elf ./build-${EXAMPLE}/part2.elf
fi
if [ "${EXAMPLE}" = "arinc653-3parts" ]; then
  mv -p ./examples/${example}/generated-code/cpu/part2/part2.elf ./build-${example}/part2.elf
  mv -p ./examples/${example}/generated-code/cpu/part3/part3.elf ./build-${example}/part3.elf
fi

# Moving to kernel directory
cd $POK_PATH

# Moving kernel. partitions and elf2uart util to deploy directory
mv examples/${EXAMPLE}/generated-code/cpu/pok.elf build-${EXAMPLE}/kernel.elf

# Move to deploy directory
#cd build-${EXAMPLE}

# Stream partition to the UART file
#./elf2uart part1.elf --output=part1.sec
#if [ "${EXAMPLE}" = "arinc653-2parts" ]; then
#  ./elf2uart part2.elf --output=part2.sec
#fi
#if [ "${EXAMPLE}" = "arinc653-3parts" ]; then
#  ./elf2uart part2.elf --output=part2.sec
#  ./elf2uart part3.elf --output=part3.sec
#fi
# Run example
#pasim --in=deploy.uart --interrupt=1 kernel.elf
