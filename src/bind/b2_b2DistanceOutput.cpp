/**
 *
 * MACHINE GENERATED FILE. DO NOT EDIT.
 *
 * Bindings for class b2DistanceOutput
 *
 * This file has been generated by dub 2.2.0.
 */
#include "dub/dub.h"
#include <Box2D/Box2D.h>


/** Set attributes (key, value)
 * 
 */
static int b2DistanceOutput__set_(lua_State *L) {

  b2DistanceOutput *self = *((b2DistanceOutput **)dub::checksdata_n(L, 1, "b2.b2DistanceOutput"));
  const char *key = luaL_checkstring(L, 2);
  int key_h = dub::hash(key, 8);
  switch(key_h) {
    case 1: {
      if (DUB_ASSERT_KEY(key, "pointA")) break;
      self->pointA = **((b2Vec2 **)dub::checksdata_n(L, 3, "b2.b2Vec2"));
      return 0;
    }
    case 2: {
      if (DUB_ASSERT_KEY(key, "pointB")) break;
      self->pointB = **((b2Vec2 **)dub::checksdata_n(L, 3, "b2.b2Vec2"));
      return 0;
    }
    case 5: {
      if (DUB_ASSERT_KEY(key, "distance")) break;
      self->distance = luaL_checknumber(L, 3);
      return 0;
    }
    case 6: {
      if (DUB_ASSERT_KEY(key, "iterations")) break;
      self->iterations = luaL_checkint(L, 3);
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
static int b2DistanceOutput__get_(lua_State *L) {

  b2DistanceOutput *self = *((b2DistanceOutput **)dub::checksdata_n(L, 1, "b2.b2DistanceOutput", true));
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
  int key_h = dub::hash(key, 8);
  switch(key_h) {
    case 1: {
      if (DUB_ASSERT_KEY(key, "pointA")) break;
      dub::pushudata(L, &self->pointA, "b2.b2Vec2", false);
      return 1;
    }
    case 2: {
      if (DUB_ASSERT_KEY(key, "pointB")) break;
      dub::pushudata(L, &self->pointB, "b2.b2Vec2", false);
      return 1;
    }
    case 5: {
      if (DUB_ASSERT_KEY(key, "distance")) break;
      lua_pushnumber(L, self->distance);
      return 1;
    }
    case 6: {
      if (DUB_ASSERT_KEY(key, "iterations")) break;
      lua_pushnumber(L, self->iterations);
      return 1;
    }
  }
  return 0;
}

/** b2DistanceOutput()
 * 
 */
static int b2DistanceOutput_b2DistanceOutput(lua_State *L) {
  try {
    b2DistanceOutput *retval__ = new b2DistanceOutput();
    dub::pushudata(L, retval__, "b2.b2DistanceOutput", true);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "new: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "new: Unknown exception");
  }
  return dub::error(L);
}



// --=============================================== __tostring
static int b2DistanceOutput___tostring(lua_State *L) {
  b2DistanceOutput *self = *((b2DistanceOutput **)dub::checksdata_n(L, 1, "b2.b2DistanceOutput"));
  lua_pushfstring(L, "b2.b2DistanceOutput: %p", self);
  
  return 1;
}

// --=============================================== METHODS

static const struct luaL_Reg b2DistanceOutput_member_methods[] = {
  { "__newindex"   , b2DistanceOutput__set_ },
  { "__index"      , b2DistanceOutput__get_ },
  { "new"          , b2DistanceOutput_b2DistanceOutput },
  { "__tostring"   , b2DistanceOutput___tostring },
  { "deleted"      , dub::isDeleted       },
  { NULL, NULL},
};


extern "C" int luaopen_b2_b2DistanceOutput(lua_State *L)
{
  // Create the metatable which will contain all the member methods
  luaL_newmetatable(L, "b2.b2DistanceOutput");
  // <mt>

  // register member methods
  dub::fregister(L, b2DistanceOutput_member_methods);
  // setup meta-table
  dub::setup(L, "b2.b2DistanceOutput");
  // <mt>
  return 1;
}