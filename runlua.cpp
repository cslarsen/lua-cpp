#include <iostream>

// Be specific about which version of Lua we compile against.
// The Lua interface has had incompatible changes over the years.
#include <lua5.2/lua.hpp>

void print_error(lua_State* state) {
  // Fetch error message from the top of the stack
  const char* message = lua_tostring(state, -1);
  std::cout << message << std::endl;

  // Remove the message from the stack
  lua_pop(state, 1);
}

// Loads and executes a Lua program (handles both source and byte code)
void execute(const char* filename)
{
  lua_State *state = luaL_newstate();

  // Make standard libraries available in `state`
  luaL_openlibs(state);

  int result;

  // Load Lua prorgram into `state`
  result = luaL_loadfile(state, filename);
  if ( result != LUA_OK ) {
    print_error(state);
    return;
  }

  // Execute Lua program in `state`
  result = lua_pcall(state, 0, LUA_MULTRET, 0);
  if ( result != LUA_OK ) {
    print_error(state);
    return;
  }
}

int main(int argc, char** argv)
{
  if ( argc <= 1 ) {
    std::cout
      << "Usage: runlua filename(s)"
      << "Loads and executes Lua programs."
      << std::endl;
    return 1;
  }

  // Execute all programs on the command line
  for ( int n=1; n<argc; ++n ) {
    execute(argv[n]);
  }

  return 0;
}
