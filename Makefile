# You can either edit this file to suit your needs, or you can run
#
# 		$ LUA_INCLUDE=/your/path make -e

# (edit this) Points to directory containing the lua5.2 directory
LUA_INCLUDE := /usr/local/include
LUA_LIBPATH := /usr/local/lib
LUA_LIBS := -llua

CXXFLAGS := -W -Wall -g -I$(LUA_INCLUDE)
LDFLAGS := -L$(LUA_LIBPATH) $(LUA_LIBS)
TARGETS := runlua

all: $(TARGETS)
	./runlua lua/error.lua lua/hello.lua

clean:
	rm -f $(TARGETS)
