/**
 *
 * MACHINE GENERATED FILE. DO NOT EDIT.
 *
 * Bindings for class b2FrictionJointDef
 *
 * This file has been generated by dub 2.2.0.
 */
#include "dub/dub.h"
#include <Box2D/Box2D.h>


/** ~b2FrictionJointDef()
 * 
 */
static int b2FrictionJointDef__b2FrictionJointDef(lua_State *L) {
  try {
    DubUserdata *userdata = ((DubUserdata*)dub::checksdata_d(L, 1, "b2.b2FrictionJointDef"));
    if (userdata->gc) {
      b2FrictionJointDef *self = (b2FrictionJointDef *)userdata->ptr;
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
static int b2FrictionJointDef__set_(lua_State *L) {

  b2FrictionJointDef *self = *((b2FrictionJointDef **)dub::checksdata_n(L, 1, "b2.b2FrictionJointDef"));
  const char *key = luaL_checkstring(L, 2);
  int key_h = dub::hash(key, 16);
  switch(key_h) {
    case 1: {
      if (DUB_ASSERT_KEY(key, "localAnchorA")) break;
      self->localAnchorA = **((b2Vec2 **)dub::checksdata_n(L, 3, "b2.b2Vec2"));
      return 0;
    }
    case 2: {
      if (DUB_ASSERT_KEY(key, "localAnchorB")) break;
      self->localAnchorB = **((b2Vec2 **)dub::checksdata_n(L, 3, "b2.b2Vec2"));
      return 0;
    }
    case 7: {
      if (DUB_ASSERT_KEY(key, "maxForce")) break;
      self->maxForce = luaL_checknumber(L, 3);
      return 0;
    }
    case 14: {
      if (DUB_ASSERT_KEY(key, "maxTorque")) break;
      self->maxTorque = luaL_checknumber(L, 3);
      return 0;
    }
    case 10: {
      if (DUB_ASSERT_KEY(key, "type")) break;
      self->type = (b2JointType)luaL_checkint(L, 3);
      return 0;
    }
    case 5: {
      if (DUB_ASSERT_KEY(key, "userData")) break;
      dub::protect(L, 1, 3, "userData");
      self->userData = *((void **)dub::checksdata_n(L, 3, "void"));
      return 0;
    }
    case 15: {
      if (DUB_ASSERT_KEY(key, "bodyA")) break;
      dub::protect(L, 1, 3, "bodyA");
      self->bodyA = *((b2Body **)dub::checksdata_n(L, 3, "b2.b2Body"));
      return 0;
    }
    case 0: {
      if (DUB_ASSERT_KEY(key, "bodyB")) break;
      dub::protect(L, 1, 3, "bodyB");
      self->bodyB = *((b2Body **)dub::checksdata_n(L, 3, "b2.b2Body"));
      return 0;
    }
    case 11: {
      if (DUB_ASSERT_KEY(key, "collideConnected")) break;
      self->collideConnected = luaL_checkboolean(L, 3);
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
static int b2FrictionJointDef__get_(lua_State *L) {

  b2FrictionJointDef *self = *((b2FrictionJointDef **)dub::checksdata_n(L, 1, "b2.b2FrictionJointDef", true));
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
  int key_h = dub::hash(key, 16);
  switch(key_h) {
    case 1: {
      if (DUB_ASSERT_KEY(key, "localAnchorA")) break;
      dub::pushudata(L, &self->localAnchorA, "b2.b2Vec2", false);
      return 1;
    }
    case 2: {
      if (DUB_ASSERT_KEY(key, "localAnchorB")) break;
      dub::pushudata(L, &self->localAnchorB, "b2.b2Vec2", false);
      return 1;
    }
    case 7: {
      if (DUB_ASSERT_KEY(key, "maxForce")) break;
      lua_pushnumber(L, self->maxForce);
      return 1;
    }
    case 14: {
      if (DUB_ASSERT_KEY(key, "maxTorque")) break;
      lua_pushnumber(L, self->maxTorque);
      return 1;
    }
    case 10: {
      if (DUB_ASSERT_KEY(key, "type")) break;
      lua_pushnumber(L, self->type);
      return 1;
    }
    case 5: {
      if (DUB_ASSERT_KEY(key, "userData")) break;
      void *retval__ = self->userData;
      if (!retval__) return 0;
      dub::pushudata(L, retval__, "void", false);
      return 1;
    }
    case 15: {
      if (DUB_ASSERT_KEY(key, "bodyA")) break;
      b2Body *retval__ = self->bodyA;
      if (!retval__) return 0;
      dub::pushudata(L, retval__, "b2.b2Body", false);
      return 1;
    }
    case 0: {
      if (DUB_ASSERT_KEY(key, "bodyB")) break;
      b2Body *retval__ = self->bodyB;
      if (!retval__) return 0;
      dub::pushudata(L, retval__, "b2.b2Body", false);
      return 1;
    }
    case 11: {
      if (DUB_ASSERT_KEY(key, "collideConnected")) break;
      lua_pushboolean(L, self->collideConnected);
      return 1;
    }
  }
  return 0;
}

/** Cast (class_name)
 * 
 */
static int b2FrictionJointDef__cast_(lua_State *L) {

  b2FrictionJointDef *self = *((b2FrictionJointDef **)dub::checksdata_n(L, 1, "b2.b2FrictionJointDef"));
  const char *key = luaL_checkstring(L, 2);
  void **retval__ = (void**)lua_newuserdata(L, sizeof(void*));
  int key_h = dub::hash(key, 2);
  switch(key_h) {
    case 1: {
      if (DUB_ASSERT_KEY(key, "b2.b2JointDef")) break;
      *retval__ = static_cast<b2JointDef *>(self);
      return 1;
    }
  }
  return 0;
}

/** b2FrictionJointDef::b2FrictionJointDef()
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/Joints/b2FrictionJoint.h:27
 */
static int b2FrictionJointDef_b2FrictionJointDef(lua_State *L) {
  try {
    b2FrictionJointDef *retval__ = new b2FrictionJointDef();
    dub::pushudata(L, retval__, "b2.b2FrictionJointDef", true);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "new: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "new: Unknown exception");
  }
  return dub::error(L);
}

/** void b2FrictionJointDef::Initialize(b2Body *bodyA, b2Body *bodyB, const b2Vec2 &anchor)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/Joints/b2FrictionJoint.h:38
 */
static int b2FrictionJointDef_Initialize(lua_State *L) {
  try {
    b2FrictionJointDef *self = *((b2FrictionJointDef **)dub::checksdata(L, 1, "b2.b2FrictionJointDef"));
    b2Body *bodyA = *((b2Body **)dub::checksdata(L, 2, "b2.b2Body"));
    b2Body *bodyB = *((b2Body **)dub::checksdata(L, 3, "b2.b2Body"));
    b2Vec2 *anchor = *((b2Vec2 **)dub::checksdata(L, 4, "b2.b2Vec2"));
    self->Initialize(bodyA, bodyB, *anchor);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "Initialize: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "Initialize: Unknown exception");
  }
  return dub::error(L);
}



// --=============================================== __tostring
static int b2FrictionJointDef___tostring(lua_State *L) {
  b2FrictionJointDef *self = *((b2FrictionJointDef **)dub::checksdata_n(L, 1, "b2.b2FrictionJointDef"));
  lua_pushfstring(L, "b2.b2FrictionJointDef: %p", self);
  
  return 1;
}

// --=============================================== METHODS

static const struct luaL_Reg b2FrictionJointDef_member_methods[] = {
  { "__gc"         , b2FrictionJointDef__b2FrictionJointDef },
  { "__newindex"   , b2FrictionJointDef__set_ },
  { "__index"      , b2FrictionJointDef__get_ },
  { "_cast_"       , b2FrictionJointDef__cast_ },
  { "new"          , b2FrictionJointDef_b2FrictionJointDef },
  { "Initialize"   , b2FrictionJointDef_Initialize },
  { "__tostring"   , b2FrictionJointDef___tostring },
  { "deleted"      , dub::isDeleted       },
  { NULL, NULL},
};


extern "C" int luaopen_b2_b2FrictionJointDef(lua_State *L)
{
  // Create the metatable which will contain all the member methods
  luaL_newmetatable(L, "b2.b2FrictionJointDef");
  // <mt>

  // register member methods
  dub::fregister(L, b2FrictionJointDef_member_methods);
  // setup meta-table
  dub::setup(L, "b2.b2FrictionJointDef");
  // <mt>
  return 1;
}
