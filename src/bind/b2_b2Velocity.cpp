/**
 *
 * MACHINE GENERATED FILE. DO NOT EDIT.
 *
 * Bindings for class b2Velocity
 *
 * This file has been generated by dub 2.2.0.
 */
#include "dub/dub.h"
#include <Box2D/Box2D.h>


/** Set attributes (key, value)
 * 
 */
static int b2Velocity__set_(lua_State *L) {

  b2Velocity *self = *((b2Velocity **)dub::checksdata_n(L, 1, "b2.b2Velocity"));
  const char *key = luaL_checkstring(L, 2);
  int key_h = dub::hash(key, 2);
  switch(key_h) {
    case 0: {
      if (DUB_ASSERT_KEY(key, "v")) break;
      self->v = **((b2Vec2 **)dub::checksdata_n(L, 3, "b2.b2Vec2"));
      return 0;
    }
    case 1: {
      if (DUB_ASSERT_KEY(key, "w")) break;
      self->w = luaL_checknumber(L, 3);
      return 0;
    }
  }
  if (lua_istable(L, 1)) {
    lua_rawset(L, 1);
  } else {
    luaL_error(L, KEY_EXCEPTION_MSG, key);
  }
  return 0;
}

/** Get attributes (key)
 * 
 */
static int b2Velocity__get_(lua_State *L) {

  b2Velocity *self = *((b2Velocity **)dub::checksdata_n(L, 1, "b2.b2Velocity", true));
  const char *key = luaL_checkstring(L, 2);
  // <self> "key" <mt>
  // rawget(mt, key)
  lua_pushvalue(L, 2);
  // <self> "key" <mt> "key"
  lua_rawget(L, -2);
  if (!lua_isnil(L, -1)) {
    // Found method.
    return 1;
  } else {
    // Not in mt = attribute access.
    lua_pop(L, 2);
  }
  int key_h = dub::hash(key, 2);
  switch(key_h) {
    case 0: {
      if (DUB_ASSERT_KEY(key, "v")) break;
      dub::pushudata(L, &self->v, "b2.b2Vec2", false);
      return 1;
    }
    case 1: {
      if (DUB_ASSERT_KEY(key, "w")) break;
      lua_pushnumber(L, self->w);
      return 1;
    }
  }
  return 0;
}

/** b2Velocity()
 * 
 */
static int b2Velocity_b2Velocity(lua_State *L) {
  try {
    b2Velocity *retval__ = new b2Velocity();
    dub::pushudata(L, retval__, "b2.b2Velocity", true);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "new: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "new: Unknown exception");
  }
  return dub::error(L);
}



// --=============================================== __tostring
static int b2Velocity___tostring(lua_State *L) {
  b2Velocity *self = *((b2Velocity **)dub::checksdata_n(L, 1, "b2.b2Velocity"));
  lua_pushfstring(L, "b2.b2Velocity: %p", self);
  
  return 1;
}

// --=============================================== METHODS

static const struct luaL_Reg b2Velocity_member_methods[] = {
  { "__newindex"   , b2Velocity__set_     },
  { "__index"      , b2Velocity__get_     },
  { "new"          , b2Velocity_b2Velocity },
  { "__tostring"   , b2Velocity___tostring },
  { "deleted"      , dub::isDeleted       },
  { NULL, NULL},
};


extern "C" int luaopen_b2_b2Velocity(lua_State *L)
{
  // Create the metatable which will contain all the member methods
  luaL_newmetatable(L, "b2.b2Velocity");
  // <mt>

  // register member methods
  dub::fregister(L, b2Velocity_member_methods);
  // setup meta-table
  dub::setup(L, "b2.b2Velocity");
  // <mt>
  return 1;
}
