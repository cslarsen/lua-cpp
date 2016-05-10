#include <lua5.2/lua.hpp>

int main()
{
  lua_State *state = luaL_newstate();
  lua_close(state);
  return 0;
}
