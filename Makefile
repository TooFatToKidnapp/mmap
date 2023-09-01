FILES = code_injection code_to_inject  file_manipulation  inter_process_communication memory_allocation

all: $(FILES)

code_to_inject:
	nasm -o code_to_inject code_to_inject.asm

%: %.c
	gcc -Wall -Wextra -Werror -ggdb -o $@ $<

clean:
	rm -frv $(FILES)
