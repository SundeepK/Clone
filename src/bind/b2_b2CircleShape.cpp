/**
 *
 * MACHINE GENERATED FILE. DO NOT EDIT.
 *
 * Bindings for class b2CircleShape
 *
 * This file has been generated by dub 2.2.0.
 */
#include "dub/dub.h"
#include <Box2D/Box2D.h>


/** ~b2CircleShape()
 * 
 */
static int b2CircleShape__b2CircleShape(lua_State *L) {
  try {
    DubUserdata *userdata = ((DubUserdata*)dub::checksdata_d(L, 1, "b2.b2CircleShape"));
    if (userdata->gc) {
      b2CircleShape *self = (b2CircleShape *)userdata->ptr;
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
static int b2CircleShape__set_(lua_State *L) {

  b2CircleShape *self = *((b2CircleShape **)dub::checksdata_n(L, 1, "b2.b2CircleShape"));
  const char *key = luaL_checkstring(L, 2);
  int key_h = dub::hash(key, 7);
  switch(key_h) {
    case 1: {
      if (DUB_ASSERT_KEY(key, "m_p")) break;
      self->m_p = **((b2Vec2 **)dub::checksdata_n(L, 3, "b2.b2Vec2"));
      return 0;
    }
    case 2: {
      if (DUB_ASSERT_KEY(key, "m_type")) break;
      self->m_type = (b2Shape::Type)luaL_checkint(L, 3);
      return 0;
    }
    case 4: {
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
static int b2CircleShape__get_(lua_State *L) {

  b2CircleShape *self = *((b2CircleShape **)dub::checksdata_n(L, 1, "b2.b2CircleShape", true));
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
  int key_h = dub::hash(key, 7);
  switch(key_h) {
    case 1: {
      if (DUB_ASSERT_KEY(key, "m_p")) break;
      dub::pushudata(L, &self->m_p, "b2.b2Vec2", false);
      return 1;
    }
    case 2: {
      if (DUB_ASSERT_KEY(key, "m_type")) break;
      lua_pushnumber(L, self->m_type);
      return 1;
    }
    case 4: {
      if (DUB_ASSERT_KEY(key, "m_radius")) break;
      lua_pushnumber(L, self->m_radius);
      return 1;
    }
  }
  return 0;
}

/** Cast (class_name)
 * 
 */
static int b2CircleShape__cast_(lua_State *L) {

  b2CircleShape *self = *((b2CircleShape **)dub::checksdata_n(L, 1, "b2.b2CircleShape"));
  const char *key = luaL_checkstring(L, 2);
  void **retval__ = (void**)lua_newuserdata(L, sizeof(void*));
  int key_h = dub::hash(key, 2);
  switch(key_h) {
    case 1: {
      if (DUB_ASSERT_KEY(key, "b2.b2Shape")) break;
      *retval__ = static_cast<b2Shape *>(self);
      return 1;
    }
  }
  return 0;
}

/** b2CircleShape::b2CircleShape()
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/Shapes/b2CircleShape.h:28
 */
static int b2CircleShape_b2CircleShape(lua_State *L) {
  try {
    b2CircleShape *retval__ = new b2CircleShape();
    dub::pushudata(L, retval__, "b2.b2CircleShape", true);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "new: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "new: Unknown exception");
  }
  return dub::error(L);
}

/** b2Shape * b2CircleShape::Clone(b2BlockAllocator *allocator) const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/Shapes/b2CircleShape.h:31
 */
static int b2CircleShape_Clone(lua_State *L) {
  try {
    b2CircleShape *self = *((b2CircleShape **)dub::checksdata(L, 1, "b2.b2CircleShape"));
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

/** int32 b2CircleShape::GetChildCount() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/Shapes/b2CircleShape.h:34
 */
static int b2CircleShape_GetChildCount(lua_State *L) {
  try {
    b2CircleShape *self = *((b2CircleShape **)dub::checksdata(L, 1, "b2.b2CircleShape"));
    lua_pushnumber(L, self->GetChildCount());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetChildCount: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetChildCount: Unknown exception");
  }
  return dub::error(L);
}

/** bool b2CircleShape::TestPoint(const b2Transform &transform, const b2Vec2 &p) const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/Shapes/b2CircleShape.h:37
 */
static int b2CircleShape_TestPoint(lua_State *L) {
  try {
    b2CircleShape *self = *((b2CircleShape **)dub::checksdata(L, 1, "b2.b2CircleShape"));
    b2Transform *transform = *((b2Transform **)dub::checksdata(L, 2, "b2.b2Transform"));
    b2Vec2 *p = *((b2Vec2 **)dub::checksdata(L, 3, "b2.b2Vec2"));
    lua_pushboolean(L, self->TestPoint(*transform, *p));
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "TestPoint: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "TestPoint: Unknown exception");
  }
  return dub::error(L);
}

/** bool b2CircleShape::RayCast(b2RayCastOutput *output, const b2RayCastInput &input, const b2Transform &transform, int32 childIndex) const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/Shapes/b2CircleShape.h:40
 */
static int b2CircleShape_RayCast(lua_State *L) {
  try {
    b2CircleShape *self = *((b2CircleShape **)dub::checksdata(L, 1, "b2.b2CircleShape"));
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

/** void b2CircleShape::ComputeAABB(b2AABB *aabb, const b2Transform &transform, int32 childIndex) const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/Shapes/b2CircleShape.h:44
 */
static int b2CircleShape_ComputeAABB(lua_State *L) {
  try {
    b2CircleShape *self = *((b2CircleShape **)dub::checksdata(L, 1, "b2.b2CircleShape"));
    b2AABB *aabb = *((b2AABB **)dub::checksdata(L, 2, "b2.b2AABB"));
    b2Transform *transform = *((b2Transform **)dub::checksdata(L, 3, "b2.b2Transform"));
    int32 childIndex = dub::checkint(L, 4);
    self->ComputeAABB(aabb, *transform, childIndex);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "ComputeAABB: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "ComputeAABB: Unknown exception");
  }
  return dub::error(L);
}

/** void b2CircleShape::ComputeMass(b2MassData *massData, float32 density) const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/Shapes/b2CircleShape.h:47
 */
static int b2CircleShape_ComputeMass(lua_State *L) {
  try {
    b2CircleShape *self = *((b2CircleShape **)dub::checksdata(L, 1, "b2.b2CircleShape"));
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

/** int32 b2CircleShape::GetSupport(const b2Vec2 &d) const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/Shapes/b2CircleShape.h:50
 */
static int b2CircleShape_GetSupport(lua_State *L) {
  try {
    b2CircleShape *self = *((b2CircleShape **)dub::checksdata(L, 1, "b2.b2CircleShape"));
    b2Vec2 *d = *((b2Vec2 **)dub::checksdata(L, 2, "b2.b2Vec2"));
    lua_pushnumber(L, self->GetSupport(*d));
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetSupport: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetSupport: Unknown exception");
  }
  return dub::error(L);
}

/** const b2Vec2 & b2CircleShape::GetSupportVertex(const b2Vec2 &d) const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/Shapes/b2CircleShape.h:53
 */
static int b2CircleShape_GetSupportVertex(lua_State *L) {
  try {
    b2CircleShape *self = *((b2CircleShape **)dub::checksdata(L, 1, "b2.b2CircleShape"));
    b2Vec2 *d = *((b2Vec2 **)dub::checksdata(L, 2, "b2.b2Vec2"));
    dub::pushudata(L, const_cast<b2Vec2*>(&self->GetSupportVertex(*d)), "b2.b2Vec2", false);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetSupportVertex: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetSupportVertex: Unknown exception");
  }
  return dub::error(L);
}

/** int32 b2CircleShape::GetVertexCount() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/Shapes/b2CircleShape.h:56
 */
static int b2CircleShape_GetVertexCount(lua_State *L) {
  try {
    b2CircleShape *self = *((b2CircleShape **)dub::checksdata(L, 1, "b2.b2CircleShape"));
    lua_pushnumber(L, self->GetVertexCount());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetVertexCount: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetVertexCount: Unknown exception");
  }
  return dub::error(L);
}

/** const b2Vec2 & b2CircleShape::GetVertex(int32 index) const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/Shapes/b2CircleShape.h:59
 */
static int b2CircleShape_GetVertex(lua_State *L) {
  try {
    b2CircleShape *self = *((b2CircleShape **)dub::checksdata(L, 1, "b2.b2CircleShape"));
    int32 index = dub::checkint(L, 2);
    dub::pushudata(L, const_cast<b2Vec2*>(&self->GetVertex(index)), "b2.b2Vec2", false);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetVertex: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetVertex: Unknown exception");
  }
  return dub::error(L);
}

/** b2Shape::Type b2Shape::GetType() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/Shapes/b2Shape.h:62
 */
static int b2CircleShape_GetType(lua_State *L) {
  try {
    b2CircleShape *self = *((b2CircleShape **)dub::checksdata(L, 1, "b2.b2CircleShape"));
    lua_pushnumber(L, self->GetType());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetType: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetType: Unknown exception");
  }
  return dub::error(L);
}



// --=============================================== __tostring
static int b2CircleShape___tostring(lua_State *L) {
  b2CircleShape *self = *((b2CircleShape **)dub::checksdata_n(L, 1, "b2.b2CircleShape"));
  lua_pushfstring(L, "b2.b2CircleShape: %p", self);
  
  return 1;
}

// --=============================================== METHODS

static const struct luaL_Reg b2CircleShape_member_methods[] = {
  { "__gc"         , b2CircleShape__b2CircleShape },
  { "__newindex"   , b2CircleShape__set_  },
  { "__index"      , b2CircleShape__get_  },
  { "_cast_"       , b2CircleShape__cast_ },
  { "new"          , b2CircleShape_b2CircleShape },
  { "Clone"        , b2CircleShape_Clone  },
  { "GetChildCount", b2CircleShape_GetChildCount },
  { "TestPoint"    , b2CircleShape_TestPoint },
  { "RayCast"      , b2CircleShape_RayCast },
  { "ComputeAABB"  , b2CircleShape_ComputeAABB },
  { "ComputeMass"  , b2CircleShape_ComputeMass },
  { "GetSupport"   , b2CircleShape_GetSupport },
  { "GetSupportVertex", b2CircleShape_GetSupportVertex },
  { "GetVertexCount", b2CircleShape_GetVertexCount },
  { "GetVertex"    , b2CircleShape_GetVertex },
  { "GetType"      , b2CircleShape_GetType },
  { "__tostring"   , b2CircleShape___tostring },
  { "deleted"      , dub::isDeleted       },
  { NULL, NULL},
};


extern "C" int luaopen_b2_b2CircleShape(lua_State *L)
{
  // Create the metatable which will contain all the member methods
  luaL_newmetatable(L, "b2.b2CircleShape");
  // <mt>

  // register member methods
  dub::fregister(L, b2CircleShape_member_methods);
  // setup meta-table
  dub::setup(L, "b2.b2CircleShape");
  // <mt>
  return 1;
}