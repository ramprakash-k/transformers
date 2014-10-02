LIBS=-lGL -lGLEW -lglfw -lGLU
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include

BIN=transformers
SRCS=render_drawing.cpp gl_framework.cpp main.cpp transformers.cpp
INCLUDES=render_drawing.hpp gl_framework.hpp transformers.hpp transformers_defs.hpp

all: $(BIN)


$(BIN): $(SRCS) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LIBS)

clean:
	rm -f $(BIN)
	rm -f *.o
	rm -f *~


