SRC_DIR := src
BUILD_DIR := build
EXE := tempest


all: $(BUILD_DIR)
	cd build && cmake .. && make -j 8 && cp $(EXE) .. 

$(BUILD_DIR):
	mkdir -p $@

c clean:
	@echo "Cleaning..."
	@rm -rf $(BUILD_DIR) $(EXE)

run: clean main
	clear
	./bin/main

format: .clang-format
	@echo "Formatting the source code ..."
	clang-format -i \
		$(SRC_DIR)/*.cpp \
		$(SRC_DIR)/*/*.cpp \
		$(SRC_DIR)/*/*.h*
#$(SRC_DIR)/*.h \

.clang-format:
	@echo "Dumping mozilla config into .clang-format file"
	@clang-format -style=mozilla -dump-config > .clang-format
