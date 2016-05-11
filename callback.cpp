#include <stdio.h>

#ifdef __cplusplus
# include <lua5.2/lua.hpp>
#else
# include <lua5.2/lua.h>
# include <lua5.2/lualib.h>
# include <lua5.2/lauxlib.h>
#endif

int howdy(lua_State* state)
{
  // The number of function arguments will be on top of the stack.
  int args = lua_gettop(state);

  printf("howdy() was alled with %d arguments:\n", args);

  for ( int n=1; n<=args; ++n) {
    printf("  argument %d: '%s'\n", n, lua_tostring(state, n));
  }

  // Push the return value on top of the stack. NOTE: We haven't popped the
  // input arguments to our function. To be honest, I haven't checked if we
  // must, but at least in stack machines like the JVM, the stack will be
  // cleaned between each function call.

  lua_pushnumber(state, 123);

  // Let Lua know how many return values we've passed
  return 1;
}

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

  // Make howd() available to Lua programs under the same name.
  lua_register(state, "howdy", howdy);

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
