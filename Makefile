RELEASE_FLAGS    = -O2 -std=c++2a
SANITIZER_FLAGS  = -std=c++2a -g -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,leak,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
DEBUG_FLAGS      = -D _DEBUG -ggdb3 -g -std=c++2a -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wstack-usage=8192 -pie -fPIE -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,leak,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
SFML_FLAGS       = -lsfml-graphics -lsfml-window -lsfml-system
COMPILER         = g++

HEADER_FILES_DIR = include/
INCLUDE_FLAGS    = -I $(HEADER_FILES_DIR)

BUILD_FLAGS      = $(DEBUG_FLAGS) $(SANITIZER_FLAGS)
LINKER_FLAGS     = $(SFML_FLAGS) -lasan

OBJECT_FILES = graphics.o log.o

all: $(OBJECT_FILES)
	$(COMPILER) $(SFML_FLAGS) $(SANITIZER_FLAGS) $(INCLUDE_FLAGS) $(OBJECT_FILES) main.cpp -o planet_sim

graphics.o:
	$(COMPILER) -c $(DEBUG_FLAGS) $(INCLUDE_FLAGS) src/graphics.cpp

wind:
	g++ -std=c++23 -D WIND -IC:\SFML-2.5.1\include -LC:\SFML-2.5.1\lib $(INCLUDE_FLAGS)						\
	main.cpp ./src/graphics.cpp ./src/log.cpp 															\
	-lm -o test.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-main -mwindows

log.o:
	$(COMPILER) -c $(DEBUG_FLAGS) $(INCLUDE_FLAGS) src/log.cpp

clean:
	rm *.o