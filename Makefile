# You can either edit this file to suit your needs, or you can run
#
# 		$ LUA_INCLUDE=/your/path make -e

# (edit this) Points to directory containing lua.h
LUA_INCLUDE := /usr/local/include
LUA_LIBPATH := /usr/local/lib
LUA_LIBS := -llua

CXXFLAGS := -W -Wall -g -I$(LUA_INCLUDE)
LDFLAGS := -L$(LUA_LIBPATH) $(LUA_LIBS)
TARGETS := example1

all: $(TARGETS)
	./example1 error.lua hello.lua

clean:
	rm -f $(TARGETS)
