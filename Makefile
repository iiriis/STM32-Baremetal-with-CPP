programmer=C:/Program\ Files/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin

CC = arm-none-eabi-g++
CC_CPU = cortex-m4
FPU_FLAGS = -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Wdouble-promotion -Wfloat-conversion -fsingle-precision-constant
OPTIMIZATION_FLAGS = -O0 -ffreestanding -fno-exceptions -specs=nano.specs -specs=nosys.specs
COVERAGE_FLAGS = -fstack-usage --coverage
CC_FLAGS = -Wall -Wpedantic -Wextra -Werror=overflow -mthumb -ffunction-sections -fdata-sections -fanalyzer $(FPU_FLAGS) -g3 $(OPTIMIZATION_FLAGS) $(COVERAGE_FLAGS) 
#-fcyclomatic-complexity

LD_FLAGS = -Wl,--gc-sections -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 $(OPTIMIZATION_FLAGS) -Wl,--print-memory-usage \
-Wl,--start-group -lc -lm -Wl,--end-group --entry=Reset_Handler $(COVERAGE_FLAGS) #-Wl,-u,_printf_float 

LINKER_SCRIPT = ./linker.ld

APP_DIRECTORY = ./build/binaries
APP_NAME = firmware

SRC_DIRECTORY = ./src
SRC = $(wildcard $(SRC_DIRECTORY)/*.cpp)

OBJ_DIRECTORY = ./build/src
OBJ = $(SRC:$(SRC_DIRECTORY)/%.cpp=$(OBJ_DIRECTORY)/%.o)

INC_DIRECTORY = ./includes

.PHONY: configure build mem_report
build: configure $(OBJ)
	@echo Linking...
	@$(CC) -mcpu=$(CC_CPU) $(LD_FLAGS) $(OBJ) -o $(APP_DIRECTORY)/$(APP_NAME).elf -Wl,-Map=$(APP_DIRECTORY)/$(APP_NAME).map -Wl,-T$(LINKER_SCRIPT) 
	@arm-none-eabi-objcopy -O ihex $(APP_DIRECTORY)/$(APP_NAME).elf $(APP_DIRECTORY)/$(APP_NAME).hex
	@arm-none-eabi-objdump -D -S -C -h $(APP_DIRECTORY)/$(APP_NAME).elf | grep -v ".debug" > $(APP_DIRECTORY)/$(APP_NAME).lst

	+@$(MAKE) mem_report --no-print-directory
	@printf "\e[1;96mBuild Successful  !!\e[0m\n"

$(OBJ_DIRECTORY)/%.o: $(SRC_DIRECTORY)/%.cpp
	@mkdir -p $(@D)
	$(CC) -mcpu=$(CC_CPU) $(CC_FLAGS) $< -c -o $@ -I$(INC_DIRECTORY)

configure:
	@mkdir -p $(OBJ_DIRECTORY) $(APP_DIRECTORY)

flash: build
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "init; reset init; program $(APP_DIRECTORY)/$(APP_NAME).elf; reset; shutdown"

show_flash_info:
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "init; reset init; flash info 0; reset; shutdown"
	
erase:
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "init; reset init; stm32f4x mass_erase 0; reset; shutdown"

.PHONY: debug
debug: build
# Start OpenOCD in the background, redirecting output to null to keep the terminal clean
	@echo "Starting OpenOCD..."
	@openocd -s scripts -f interface/stlink.cfg -f target/stm32f4x.cfg 2>&1 >/dev/null & \
    echo $$! > openocd.pid
    # Give OpenOCD time to start
	@sleep 0
    # Start arm-none-eabi-gdb and connect to OpenOCD
	@echo "Starting GDB..."
	@gdb-multiarch $(APP_DIRECTORY)/$(APP_NAME).elf -x ./gdb-config.gdb --silent
	@kill $$(cat openocd.pid) && rm -f openocd.pid
	
.PHONY: mem_report
mem_report:
	@echo "--------------------------------------------------------"
	@echo "| 	Section Name  	|    Address    |  Size (Bytes)|"
	@echo "--------------------------------------------------------"
	@arm-none-eabi-objdump -h $(APP_DIRECTORY)/$(APP_NAME).elf | \
    awk '/^\s+[0-9]+/ { if (strtonum($$(4)) > 0) printf("| %-21s | 0x%-10s 	| %-12d |\n", $$2, $$(4), strtonum("0x"$$3)); }'
	@echo "--------------------------------------------------------"

.PHONY: clean_build
clean_build:
	+@make clean --no-print-directory
	+@make build --no-print-directory


program: build
	$(programmer)/STM32_Programmer_CLI -c port=USB1 -w firmware.elf 0x08000000
# /cygdrive/c/Program\ Files/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin/STM32_Programmer_CLI -c port=USB1 -w firmware.elf 0x08000000

clean:
	rm -f $(OBJ_DIRECTORY)/* $(APP_DIRECTORY)/*