#include <iostream>

extern "C" {
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
}

class LuaState {
public:
  LuaState():
    state(luaL_newstate())
  {
  }

  ~LuaState() {
    lua_close(state);
  }

  operator lua_State*() {
    return state;
  }

private:
  lua_State *state;
  LuaState(const LuaState&); // DENY
  LuaState& operator=(const LuaState&); // DENY
};

void print_error(lua_State* state) {
  // Fetch string on top of the return stack
  const char* error = lua_tostring(state, -1);
  std::cout << error << std::endl;

  // Remove item on top of the stack
  lua_pop(state, 1);
}

// Load and execute Lua program
void execute(const char* filename)
{
  LuaState state;
  luaL_openlibs(state);

  int result;

  result = luaL_loadfile(state, filename);
  if ( result != LUA_OK ) {
    print_error(state);
    return;
  }

  result = lua_pcall(state, 0, LUA_MULTRET, 0);
  if ( result != LUA_OK ) {
    print_error(state);
    return;
  }
}

int main(int argc, char** argv)
{
  for ( int n=1; n<argc; ++n )
    execute(argv[n]);

  return 0;
}
