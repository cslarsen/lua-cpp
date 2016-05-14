# You can either edit this file to suit your needs, or you can run
#
# 		$ LUA_INCLUDE=/your/path make -e

# (edit this) Points to directory containing the lua5.2 directory
LUAC := luac
LUA_ROOT := /usr/local
LUA_INCLUDE := $(LUA_ROOT)/include
LUA_LIBPATH := $(LUA_ROOT)/lib
LUA_LIBS := -llua

CXXFLAGS := -W -Wall -g -I$(LUA_INCLUDE)
LDFLAGS := -L$(LUA_LIBPATH) $(LUA_LIBS)
TARGETS := first runlua lua/hello.luac callback

all: $(TARGETS)
	@echo -- Running examples
	./first
	./runlua lua/error.lua lua/hello.lua lua/hello.luac
	./callback lua/callback.lua

%.luac: %.lua
	$(LUAC) -o $@ $<

clean:
	rm -f $(TARGETS)
