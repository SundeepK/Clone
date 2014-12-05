/**
 *
 * MACHINE GENERATED FILE. DO NOT EDIT.
 *
 * Bindings for class b2Shape
 *
 * This file has been generated by dub 2.2.0.
 */
#include "dub/dub.h"
#include <Box2D/Box2D.h>


/** Set attributes (key, value)
 * 
 */
static int b2Shape__set_(lua_State *L) {

  b2Shape *self = *((b2Shape **)dub::checksdata_n(L, 1, "b2.b2Shape"));
  const char *key = luaL_checkstring(L, 2);
  int key_h = dub::hash(key, 5);
  switch(key_h) {
    case 2: {
      if (DUB_ASSERT_KEY(key, "m_type")) break;
      self->m_type = (b2Shape::Type)luaL_checkint(L, 3);
      return 0;
    }
    case 0: {
      if (DUB_ASSERT_KEY(key, "m_radius")) break;
      self->m_radius = luaL_checknumber(L, 3);
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
static int b2Shape__get_(lua_State *L) {

  b2Shape *self = *((b2Shape **)dub::checksdata_n(L, 1, "b2.b2Shape", true));
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
  int key_h = dub::hash(key, 5);
  switch(key_h) {
    case 2: {
      if (DUB_ASSERT_KEY(key, "m_type")) break;
      lua_pushnumber(L, self->m_type);
      return 1;
    }
    case 0: {
      if (DUB_ASSERT_KEY(key, "m_radius")) break;
      lua_pushnumber(L, self->m_radius);
      return 1;
    }
  }
  return 0;
}

/** virtual b2Shape::~b2Shape()
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/Shapes/b2Shape.h:55
 */
static int b2Shape__b2Shape(lua_State *L) {
  try {
    DubUserdata *userdata = ((DubUserdata*)dub::checksdata_d(L, 1, "b2.b2Shape"));
    if (userdata->gc) {
      b2Shape *self = (b2Shape *)userdata->ptr;
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

/** virtual b2Shape* b2Shape::Clone(b2BlockAllocator *allocator) const =0
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/Shapes/b2Shape.h:58
 */
static int b2Shape_Clone(lua_State *L) {
  try {
    b2Shape *self = *((b2Shape **)dub::checksdata(L, 1, "b2.b2Shape"));
    b2BlockAllocator *allocator = *((b2BlockAllocator **)dub::checksdata(L, 2, "b2.b2BlockAllocator"));
    b2Shape *retval__ = self->Clone(allocator);
    if (!retval__) return 0;
    dub::pushudata(L, retval__, "b2.b2Shape", false);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "Clone: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "Clone: Unknown exception");
  }
  return dub::error(L);
}

/** b2Shape::Type b2Shape::GetType() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/Shapes/b2Shape.h:62
 */
static int b2Shape_GetType(lua_State *L) {
  try {
    b2Shape *self = *((b2Shape **)dub::checksdata(L, 1, "b2.b2Shape"));
    lua_pushnumber(L, self->GetType());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetType: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetType: Unknown exception");
  }
  return dub::error(L);
}

/** virtual int32 b2Shape::GetChildCount() const =0
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/Shapes/b2Shape.h:65
 */
static int b2Shape_GetChildCount(lua_State *L) {
  try {
    b2Shape *self = *((b2Shape **)dub::checksdata(L, 1, "b2.b2Shape"));
    lua_pushnumber(L, self->GetChildCount());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetChildCount: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetChildCount: Unknown exception");
  }
  return dub::error(L);
}

/** virtual bool b2Shape::TestPoint(const b2Transform &xf, const b2Vec2 &p) const =0
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/Shapes/b2Shape.h:70
 */
static int b2Shape_TestPoint(lua_State *L) {
  try {
    b2Shape *self = *((b2Shape **)dub::checksdata(L, 1, "b2.b2Shape"));
    b2Transform *xf = *((b2Transform **)dub::checksdata(L, 2, "b2.b2Transform"));
    b2Vec2 *p = *((b2Vec2 **)dub::checksdata(L, 3, "b2.b2Vec2"));
    lua_pushboolean(L, self->TestPoint(*xf, *p));
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "TestPoint: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "TestPoint: Unknown exception");
  }
  return dub::error(L);
}

/** virtual bool b2Shape::RayCast(b2RayCastOutput *output, const b2RayCastInput &input, const b2Transform &transform, int32 childIndex) const =0
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/Shapes/b2Shape.h:77
 */
static int b2Shape_RayCast(lua_State *L) {
  try {
    b2Shape *self = *((b2Shape **)dub::checksdata(L, 1, "b2.b2Shape"));
    b2RayCastOutput *output = *((b2RayCastOutput **)dub::checksdata(L, 2, "b2.b2RayCastOutput"));
    b2RayCastInput *input = *((b2RayCastInput **)dub::checksdata(L, 3, "b2.b2RayCastInput"));
    b2Transform *transform = *((b2Transform **)dub::checksdata(L, 4, "b2.b2Transform"));
    int32 childIndex = dub::checkint(L, 5);
    lua_pushboolean(L, self->RayCast(output, *input, *transform, childIndex));
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "RayCast: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "RayCast: Unknown exception");
  }
  return dub::error(L);
}

/** virtual void b2Shape::ComputeAABB(b2AABB *aabb, const b2Transform &xf, int32 childIndex) const =0
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/Shapes/b2Shape.h:84
 */
static int b2Shape_ComputeAABB(lua_State *L) {
  try {
    b2Shape *self = *((b2Shape **)dub::checksdata(L, 1, "b2.b2Shape"));
    b2AABB *aabb = *((b2AABB **)dub::checksdata(L, 2, "b2.b2AABB"));
    b2Transform *xf = *((b2Transform **)dub::checksdata(L, 3, "b2.b2Transform"));
    int32 childIndex = dub::checkint(L, 4);
    self->ComputeAABB(aabb, *xf, childIndex);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "ComputeAABB: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "ComputeAABB: Unknown exception");
  }
  return dub::error(L);
}

/** virtual void b2Shape::ComputeMass(b2MassData *massData, float32 density) const =0
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/Shapes/b2Shape.h:90
 */
static int b2Shape_ComputeMass(lua_State *L) {
  try {
    b2Shape *self = *((b2Shape **)dub::checksdata(L, 1, "b2.b2Shape"));
    b2MassData *massData = *((b2MassData **)dub::checksdata(L, 2, "b2.b2MassData"));
    float32 density = dub::checknumber(L, 3);
    self->ComputeMass(massData, density);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "ComputeMass: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "ComputeMass: Unknown exception");
  }
  return dub::error(L);
}



// --=============================================== __tostring
static int b2Shape___tostring(lua_State *L) {
  b2Shape *self = *((b2Shape **)dub::checksdata_n(L, 1, "b2.b2Shape"));
  lua_pushfstring(L, "b2.b2Shape: %p", self);
  
  return 1;
}

// --=============================================== METHODS

static const struct luaL_Reg b2Shape_member_methods[] = {
  { "__newindex"   , b2Shape__set_        },
  { "__index"      , b2Shape__get_        },
  { "__gc"         , b2Shape__b2Shape     },
  { "Clone"        , b2Shape_Clone        },
  { "GetType"      , b2Shape_GetType      },
  { "GetChildCount", b2Shape_GetChildCount },
  { "TestPoint"    , b2Shape_TestPoint    },
  { "RayCast"      , b2Shape_RayCast      },
  { "ComputeAABB"  , b2Shape_ComputeAABB  },
  { "ComputeMass"  , b2Shape_ComputeMass  },
  { "__tostring"   , b2Shape___tostring   },
  { "deleted"      , dub::isDeleted       },
  { NULL, NULL},
};

// --=============================================== CONSTANTS
static const struct dub::const_Reg b2Shape_const[] = {
  { "e_circle"     , b2Shape::e_circle    },
  { "e_edge"       , b2Shape::e_edge      },
  { "e_polygon"    , b2Shape::e_polygon   },
  { "e_chain"      , b2Shape::e_chain     },
  { "e_typeCount"  , b2Shape::e_typeCount },
  { NULL, 0},
};

extern "C" int luaopen_b2_b2Shape(lua_State *L)
{
  // Create the metatable which will contain all the member methods
  luaL_newmetatable(L, "b2.b2Shape");
  // <mt>
  // register class constants
  dub::register_const(L, b2Shape_const);

  // register member methods
  dub::fregister(L, b2Shape_member_methods);
  // setup meta-table
  dub::setup(L, "b2.b2Shape");
  // <mt>
  return 1;
}