/**
 *
 * MACHINE GENERATED FILE. DO NOT EDIT.
 *
 * Bindings for class b2Mat33
 *
 * This file has been generated by dub 2.2.0.
 */
#include "dub/dub.h"
#include <Box2D/Box2D.h>


/** ~b2Mat33()
 * 
 */
static int b2Mat33__b2Mat33(lua_State *L) {
  try {
    DubUserdata *userdata = ((DubUserdata*)dub::checksdata_d(L, 1, "b2.b2Mat33"));
    if (userdata->gc) {
      b2Mat33 *self = (b2Mat33 *)userdata->ptr;
      delete self;
    }
    userdata->gc = false;
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "__gc: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "__gc: Unknown exception");
  }
  return dub::error(L);
}

/** Set attributes (key, value)
 * 
 */
static int b2Mat33__set_(lua_State *L) {

  b2Mat33 *self = *((b2Mat33 **)dub::checksdata_n(L, 1, "b2.b2Mat33"));
  const char *key = luaL_checkstring(L, 2);
  int key_h = dub::hash(key, 3);
  switch(key_h) {
    case 2: {
      if (DUB_ASSERT_KEY(key, "ex")) break;
      self->ex = **((b2Vec3 **)dub::checksdata_n(L, 3, "b2.b2Vec3"));
      return 0;
    }
    case 0: {
      if (DUB_ASSERT_KEY(key, "ey")) break;
      self->ey = **((b2Vec3 **)dub::checksdata_n(L, 3, "b2.b2Vec3"));
      return 0;
    }
    case 1: {
      if (DUB_ASSERT_KEY(key, "ez")) break;
      self->ez = **((b2Vec3 **)dub::checksdata_n(L, 3, "b2.b2Vec3"));
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
static int b2Mat33__get_(lua_State *L) {

  b2Mat33 *self = *((b2Mat33 **)dub::checksdata_n(L, 1, "b2.b2Mat33", true));
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
  int key_h = dub::hash(key, 3);
  switch(key_h) {
    case 2: {
      if (DUB_ASSERT_KEY(key, "ex")) break;
      dub::pushudata(L, &self->ex, "b2.b2Vec3", false);
      return 1;
    }
    case 0: {
      if (DUB_ASSERT_KEY(key, "ey")) break;
      dub::pushudata(L, &self->ey, "b2.b2Vec3", false);
      return 1;
    }
    case 1: {
      if (DUB_ASSERT_KEY(key, "ez")) break;
      dub::pushudata(L, &self->ez, "b2.b2Vec3", false);
      return 1;
    }
  }
  return 0;
}

/** b2Mat33::b2Mat33()
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Common/b2Math.h:260
 */
static int b2Mat33_b2Mat33(lua_State *L) {
  try {
    int top__ = lua_gettop(L);
    if (top__ >= 3) {
      b2Vec3 *c1 = *((b2Vec3 **)dub::checksdata(L, 1, "b2.b2Vec3"));
      b2Vec3 *c2 = *((b2Vec3 **)dub::checksdata(L, 2, "b2.b2Vec3"));
      b2Vec3 *c3 = *((b2Vec3 **)dub::checksdata(L, 3, "b2.b2Vec3"));
      b2Mat33 *retval__ = new b2Mat33(*c1, *c2, *c3);
      dub::pushudata(L, retval__, "b2.b2Mat33", true);
      return 1;
    } else {
      b2Mat33 *retval__ = new b2Mat33();
      dub::pushudata(L, retval__, "b2.b2Mat33", true);
      return 1;
    }
  } catch (std::exception &e) {
    lua_pushfstring(L, "new: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "new: Unknown exception");
  }
  return dub::error(L);
}

/** void b2Mat33::SetZero()
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Common/b2Math.h:271
 */
static int b2Mat33_SetZero(lua_State *L) {
  try {
    b2Mat33 *self = *((b2Mat33 **)dub::checksdata(L, 1, "b2.b2Mat33"));
    self->SetZero();
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "SetZero: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "SetZero: Unknown exception");
  }
  return dub::error(L);
}

/** b2Vec3 b2Mat33::Solve33(const b2Vec3 &b) const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Common/b2Math.h:280
 */
static int b2Mat33_Solve33(lua_State *L) {
  try {
    b2Mat33 *self = *((b2Mat33 **)dub::checksdata(L, 1, "b2.b2Mat33"));
    b2Vec3 *b = *((b2Vec3 **)dub::checksdata(L, 2, "b2.b2Vec3"));
    dub::pushudata(L, new b2Vec3(self->Solve33(*b)), "b2.b2Vec3", true);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "Solve33: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "Solve33: Unknown exception");
  }
  return dub::error(L);
}

/** b2Vec2 b2Mat33::Solve22(const b2Vec2 &b) const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Common/b2Math.h:285
 */
static int b2Mat33_Solve22(lua_State *L) {
  try {
    b2Mat33 *self = *((b2Mat33 **)dub::checksdata(L, 1, "b2.b2Mat33"));
    b2Vec2 *b = *((b2Vec2 **)dub::checksdata(L, 2, "b2.b2Vec2"));
    dub::pushudata(L, new b2Vec2(self->Solve22(*b)), "b2.b2Vec2", true);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "Solve22: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "Solve22: Unknown exception");
  }
  return dub::error(L);
}

/** void b2Mat33::GetInverse22(b2Mat33 *M) const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Common/b2Math.h:289
 */
static int b2Mat33_GetInverse22(lua_State *L) {
  try {
    b2Mat33 *self = *((b2Mat33 **)dub::checksdata(L, 1, "b2.b2Mat33"));
    b2Mat33 *M = *((b2Mat33 **)dub::checksdata(L, 2, "b2.b2Mat33"));
    self->GetInverse22(M);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetInverse22: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetInverse22: Unknown exception");
  }
  return dub::error(L);
}

/** void b2Mat33::GetSymInverse33(b2Mat33 *M) const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Common/b2Math.h:293
 */
static int b2Mat33_GetSymInverse33(lua_State *L) {
  try {
    b2Mat33 *self = *((b2Mat33 **)dub::checksdata(L, 1, "b2.b2Mat33"));
    b2Mat33 *M = *((b2Mat33 **)dub::checksdata(L, 2, "b2.b2Mat33"));
    self->GetSymInverse33(M);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetSymInverse33: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetSymInverse33: Unknown exception");
  }
  return dub::error(L);
}



// --=============================================== __tostring
static int b2Mat33___tostring(lua_State *L) {
  b2Mat33 *self = *((b2Mat33 **)dub::checksdata_n(L, 1, "b2.b2Mat33"));
  lua_pushfstring(L, "b2.b2Mat33: %p", self);
  
  return 1;
}

// --=============================================== METHODS

static const struct luaL_Reg b2Mat33_member_methods[] = {
  { "__gc"         , b2Mat33__b2Mat33     },
  { "__newindex"   , b2Mat33__set_        },
  { "__index"      , b2Mat33__get_        },
  { "new"          , b2Mat33_b2Mat33      },
  { "SetZero"      , b2Mat33_SetZero      },
  { "Solve33"      , b2Mat33_Solve33      },
  { "Solve22"      , b2Mat33_Solve22      },
  { "GetInverse22" , b2Mat33_GetInverse22 },
  { "GetSymInverse33", b2Mat33_GetSymInverse33 },
  { "__tostring"   , b2Mat33___tostring   },
  { "deleted"      , dub::isDeleted       },
  { NULL, NULL},
};


extern "C" int luaopen_b2_b2Mat33(lua_State *L)
{
  // Create the metatable which will contain all the member methods
  luaL_newmetatable(L, "b2.b2Mat33");
  // <mt>

  // register member methods
  dub::fregister(L, b2Mat33_member_methods);
  // setup meta-table
  dub::setup(L, "b2.b2Mat33");
  // <mt>
  return 1;
}
