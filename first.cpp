#ifdef __cplusplus
# include <lua5.2/lua.hpp>
#else
# include <lua5.2/lua.h>
# include <lua5.2/lualib.h>
# include <lua5.2/lauxlib.h>
#endif

int main()
{
  lua_State *state = luaL_newstate();
  lua_close(state);
  return 0;
}
