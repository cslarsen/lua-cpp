#ifdef __cplusplus
# include <lua.hpp>
#else
# include <lua.h>
# include <lualib.h>
# include <lauxlib.h>
#endif

int main()
{
  lua_State *state = luaL_newstate();
  lua_close(state);
  return 0;
}
