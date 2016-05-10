#include <stdio.h>

#ifdef __cplusplus
# include <lua5.2/lua.hpp>
#else
# include <lua5.2/lua.h>
# include <lua5.2/lualib.h>
# include <lua5.2/lauxlib.h>
#endif

void print_error(lua_State* state) {
  // The error message is on top of the stack. Fetch it, print it and then pop
  // it off the stack.
  const char* message = lua_tostring(state, -1);
  puts(message);
  lua_pop(state, 1);
}

void execute(const char* filename)
{
  lua_State *state = luaL_newstate();

  // Make standard libraries available in the Lua state
  luaL_openlibs(state);

  int result;

  // Load the program; this supports both source code and bytecode files.
  result = luaL_loadfile(state, filename);
  if ( result != LUA_OK ) {
    print_error(state);
    return;
  }

  // Finally, execute the program by calling into it. You may have to change
  // the lua_pcall arguments if you're not running vanilla Lua code.
  result = lua_pcall(state, 0, LUA_MULTRET, 0);
  if ( result != LUA_OK ) {
    print_error(state);
    return;
  }
}

int main(int argc, char** argv)
{
  if ( argc <= 1 ) {
    puts("Usage: runlua file(s)");
    puts("Loads and executes Lua programs.");
    return 1;
  }

  // Execute all programs on the command line
  for ( int n=1; n<argc; ++n ) {
    execute(argv[n]);
  }

  return 0;
}
