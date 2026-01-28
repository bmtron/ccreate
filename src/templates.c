
const char* makefile_contents = 
"CC = gcc\n"
"CFLAGS = -Wall -Wextra -std=c11 -g\n"
"LDFLAGS = -lSDL2 -lSDL2_image\n"
"\n"
"ASAN_FLAGS = -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer\n"
"ASAN_ENV = ASAN_OPTIONS=detect_leaks=1:symbolize=1\n"
"\n"
"BINDIR := bin\n"
"OBJDIR := obj\n"
"SRCDIR := src\n"
"\n"
"TARGET := $(BINDIR)/%s\n"
"SRCS := $(wildcard $(SRCDIR)/*.c $(SRCDIR)/**/*.c)\n"
"OBJS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))\n"
"\n"
"all: $(TARGET)\n"
"\n"
"debug: CFLAGS += $(ASAN_FLAGS)\n"
"debug: LDFLAGS += $(ASAN_FLAGS)\n"
"debug: $(TARGET)\n"
"\n"
"release: CFLAGS += -O2\n"
"release: $(TARGET)\n"
"\n"
"$(TARGET): $(OBJS) | $(BINDIR)\n"
"\t$(CC) $(CFLAGS) -o $@ $^\n"
"\n"
"$(OBJDIR)/%.o: $(SRCDIR)/%.c\n"
"\t@mkdir -p $(dir $@)\n"
"\t$(CC) $(CFLAGS) -c $< -o $@\n"
"\n"
"$(OBJDIR):\n"
"\tmkdir -p $(OBJDIR)\n"
"\n"
"$(BINDIR):\n"
"\tmkdir -p $(BINDIR)\n"
"\n"
"run: debug\n"
"\t$(ASAN_ENV) ./$(TARGET)\n"
"\n"
"gdb: debug\n"
"\tgdb ./$(TARGET)\n"
"\n"
"clean:\n"
"\trm -rf $(OBJDIR) $(BINDIR)\n"
"\n"
".PHONY: all debug release run gdb clean\n";

const char* getMakefileTemplate() {
    return makefile_contents;
}

const char* main_template = 
"#include <stdio.h>\n"
"\n"
"int main(int argc, char** argv) {\n"
"   printf(\"Hello, world!\\n\");\n"
"\n"
"   return 0;\n"
"}\n";

const char* getMainTemplate() {
    return main_template;
}
