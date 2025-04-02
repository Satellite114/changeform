# --- Automatic Path Configuration ---
ROOT_DIRS = User
EXCLUDE_DIRS = build
AUTO_INCLUDES = auto_includes.mk
INCLUDE_FILE = auto_includes_paths.mk

.PHONY: generate_includes
generate_includes:
	@echo "Generating includes..."
	@echo "# Auto-generated include paths" > $(AUTO_INCLUDES)
	@echo "C_SOURCES = \\" >> $(AUTO_INCLUDES)
	@find $(ROOT_DIRS) -type d -name $(EXCLUDE_DIRS) -prune -o -type f -name '*.c' -print | while IFS= read -r file; do \
		echo "$$file \\" >> $(AUTO_INCLUDES); \
	done
	@echo "C_INCLUDES = \\" > $(INCLUDE_FILE)
	@find $(ROOT_DIRS) -type d -name $(EXCLUDE_DIRS) -prune -o -type f -name '*.c' -print | xargs dirname | sort -u | while IFS= read -r dir; do \
		echo "-I$$dir \\" >> $(INCLUDE_FILE); \
	done
	@awk 'NR>1{print prev} {prev=$$0} END{print prev}' $(AUTO_INCLUDES) > $(AUTO_INCLUDES).tmp && mv $(AUTO_INCLUDES).tmp $(AUTO_INCLUDES)
	@awk 'NR>1{print prev} {prev=$$0} END{print prev}' $(INCLUDE_FILE) > $(INCLUDE_FILE).tmp && mv $(INCLUDE_FILE).tmp $(INCLUDE_FILE)

-include $(AUTO_INCLUDES)
-include $(INCLUDE_FILE)

# 示例默认目标，确保生成包含文件
.PHONY: all
all: generate_includes
	@echo "Building with:"
	@echo "C_SOURCES: $(C_SOURCES)"
	@echo "C_INCLUDES: $(C_INCLUDES)"

# paths