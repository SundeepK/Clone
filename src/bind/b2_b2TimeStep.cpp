/**
 *
 * MACHINE GENERATED FILE. DO NOT EDIT.
 *
 * Bindings for class b2TimeStep
 *
 * This file has been generated by dub 2.2.0.
 */
#include "dub/dub.h"
#include <Box2D/Box2D.h>


/** Set attributes (key, value)
 * 
 */
static int b2TimeStep__set_(lua_State *L) {

  b2TimeStep *self = *((b2TimeStep **)dub::checksdata_n(L, 1, "b2.b2TimeStep"));
  const char *key = luaL_checkstring(L, 2);
  int key_h = dub::hash(key, 9);
  switch(key_h) {
    case 6: {
      if (DUB_ASSERT_KEY(key, "dt")) break;
      self->dt = luaL_checknumber(L, 3);
      return 0;
    }
    case 7: {
      if (DUB_ASSERT_KEY(key, "inv_dt")) break;
      self->inv_dt = luaL_checknumber(L, 3);
      return 0;
    }
    case 0: {
      if (DUB_ASSERT_KEY(key, "dtRatio")) break;
      self->dtRatio = luaL_checknumber(L, 3);
      return 0;
    }
    case 4: {
      if (DUB_ASSERT_KEY(key, "velocityIterations")) break;
      self->velocityIterations = luaL_checkint(L, 3);
      return 0;
    }
    case 3: {
      if (DUB_ASSERT_KEY(key, "positionIterations")) break;
      self->positionIterations = luaL_checkint(L, 3);
      return 0;
    }
    case 5: {
      if (DUB_ASSERT_KEY(key, "warmStarting")) break;
      self->warmStarting = luaL_checkboolean(L, 3);
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
static int b2TimeStep__get_(lua_State *L) {

  b2TimeStep *self = *((b2TimeStep **)dub::checksdata_n(L, 1, "b2.b2TimeStep", true));
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
  int key_h = dub::hash(key, 9);
  switch(key_h) {
    case 6: {
      if (DUB_ASSERT_KEY(key, "dt")) break;
      lua_pushnumber(L, self->dt);
      return 1;
    }
    case 7: {
      if (DUB_ASSERT_KEY(key, "inv_dt")) break;
      lua_pushnumber(L, self->inv_dt);
      return 1;
    }
    case 0: {
      if (DUB_ASSERT_KEY(key, "dtRatio")) break;
      lua_pushnumber(L, self->dtRatio);
      return 1;
    }
    case 4: {
      if (DUB_ASSERT_KEY(key, "velocityIterations")) break;
      lua_pushnumber(L, self->velocityIterations);
      return 1;
    }
    case 3: {
      if (DUB_ASSERT_KEY(key, "positionIterations")) break;
      lua_pushnumber(L, self->positionIterations);
      return 1;
    }
    case 5: {
      if (DUB_ASSERT_KEY(key, "warmStarting")) break;
      lua_pushboolean(L, self->warmStarting);
      return 1;
    }
  }
  return 0;
}

/** b2TimeStep()
 * 
 */
static int b2TimeStep_b2TimeStep(lua_State *L) {
  try {
    b2TimeStep *retval__ = new b2TimeStep();
    dub::pushudata(L, retval__, "b2.b2TimeStep", true);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "new: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "new: Unknown exception");
  }
  return dub::error(L);
}



// --=============================================== __tostring
static int b2TimeStep___tostring(lua_State *L) {
  b2TimeStep *self = *((b2TimeStep **)dub::checksdata_n(L, 1, "b2.b2TimeStep"));
  lua_pushfstring(L, "b2.b2TimeStep: %p", self);
  
  return 1;
}

// --=============================================== METHODS

static const struct luaL_Reg b2TimeStep_member_methods[] = {
  { "__newindex"   , b2TimeStep__set_     },
  { "__index"      , b2TimeStep__get_     },
  { "new"          , b2TimeStep_b2TimeStep },
  { "__tostring"   , b2TimeStep___tostring },
  { "deleted"      , dub::isDeleted       },
  { NULL, NULL},
};


extern "C" int luaopen_b2_b2TimeStep(lua_State *L)
{
  // Create the metatable which will contain all the member methods
  luaL_newmetatable(L, "b2.b2TimeStep");
  // <mt>

  // register member methods
  dub::fregister(L, b2TimeStep_member_methods);
  // setup meta-table
  dub::setup(L, "b2.b2TimeStep");
  // <mt>
  return 1;
}