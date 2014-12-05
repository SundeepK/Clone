/**
 *
 * MACHINE GENERATED FILE. DO NOT EDIT.
 *
 * Bindings for class b2MotorJointDef
 *
 * This file has been generated by dub 2.2.0.
 */
#include "dub/dub.h"
#include <Box2D/Box2D.h>


/** ~b2MotorJointDef()
 * 
 */
static int b2MotorJointDef__b2MotorJointDef(lua_State *L) {
  try {
    DubUserdata *userdata = ((DubUserdata*)dub::checksdata_d(L, 1, "b2.b2MotorJointDef"));
    if (userdata->gc) {
      b2MotorJointDef *self = (b2MotorJointDef *)userdata->ptr;
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
static int b2MotorJointDef__set_(lua_State *L) {

  b2MotorJointDef *self = *((b2MotorJointDef **)dub::checksdata_n(L, 1, "b2.b2MotorJointDef"));
  const char *key = luaL_checkstring(L, 2);
  int key_h = dub::hash(key, 26);
  switch(key_h) {
    case 10: {
      if (DUB_ASSERT_KEY(key, "linearOffset")) break;
      self->linearOffset = **((b2Vec2 **)dub::checksdata_n(L, 3, "b2.b2Vec2"));
      return 0;
    }
    case 17: {
      if (DUB_ASSERT_KEY(key, "angularOffset")) break;
      self->angularOffset = luaL_checknumber(L, 3);
      return 0;
    }
    case 25: {
      if (DUB_ASSERT_KEY(key, "maxForce")) break;
      self->maxForce = luaL_checknumber(L, 3);
      return 0;
    }
    case 12: {
      if (DUB_ASSERT_KEY(key, "maxTorque")) break;
      self->maxTorque = luaL_checknumber(L, 3);
      return 0;
    }
    case 23: {
      if (DUB_ASSERT_KEY(key, "correctionFactor")) break;
      self->correctionFactor = luaL_checknumber(L, 3);
      return 0;
    }
    case 16: {
      if (DUB_ASSERT_KEY(key, "type")) break;
      self->type = (b2JointType)luaL_checkint(L, 3);
      return 0;
    }
    case 11: {
      if (DUB_ASSERT_KEY(key, "userData")) break;
      dub::protect(L, 1, 3, "userData");
      self->userData = *((void **)dub::checksdata_n(L, 3, "void"));
      return 0;
    }
    case 3: {
      if (DUB_ASSERT_KEY(key, "bodyA")) break;
      dub::protect(L, 1, 3, "bodyA");
      self->bodyA = *((b2Body **)dub::checksdata_n(L, 3, "b2.b2Body"));
      return 0;
    }
    case 4: {
      if (DUB_ASSERT_KEY(key, "bodyB")) break;
      dub::protect(L, 1, 3, "bodyB");
      self->bodyB = *((b2Body **)dub::checksdata_n(L, 3, "b2.b2Body"));
      return 0;
    }
    case 7: {
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
static int b2MotorJointDef__get_(lua_State *L) {

  b2MotorJointDef *self = *((b2MotorJointDef **)dub::checksdata_n(L, 1, "b2.b2MotorJointDef", true));
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
  int key_h = dub::hash(key, 26);
  switch(key_h) {
    case 10: {
      if (DUB_ASSERT_KEY(key, "linearOffset")) break;
      dub::pushudata(L, &self->linearOffset, "b2.b2Vec2", false);
      return 1;
    }
    case 17: {
      if (DUB_ASSERT_KEY(key, "angularOffset")) break;
      lua_pushnumber(L, self->angularOffset);
      return 1;
    }
    case 25: {
      if (DUB_ASSERT_KEY(key, "maxForce")) break;
      lua_pushnumber(L, self->maxForce);
      return 1;
    }
    case 12: {
      if (DUB_ASSERT_KEY(key, "maxTorque")) break;
      lua_pushnumber(L, self->maxTorque);
      return 1;
    }
    case 23: {
      if (DUB_ASSERT_KEY(key, "correctionFactor")) break;
      lua_pushnumber(L, self->correctionFactor);
      return 1;
    }
    case 16: {
      if (DUB_ASSERT_KEY(key, "type")) break;
      lua_pushnumber(L, self->type);
      return 1;
    }
    case 11: {
      if (DUB_ASSERT_KEY(key, "userData")) break;
      void *retval__ = self->userData;
      if (!retval__) return 0;
      dub::pushudata(L, retval__, "void", false);
      return 1;
    }
    case 3: {
      if (DUB_ASSERT_KEY(key, "bodyA")) break;
      b2Body *retval__ = self->bodyA;
      if (!retval__) return 0;
      dub::pushudata(L, retval__, "b2.b2Body", false);
      return 1;
    }
    case 4: {
      if (DUB_ASSERT_KEY(key, "bodyB")) break;
      b2Body *retval__ = self->bodyB;
      if (!retval__) return 0;
      dub::pushudata(L, retval__, "b2.b2Body", false);
      return 1;
    }
    case 7: {
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
static int b2MotorJointDef__cast_(lua_State *L) {

  b2MotorJointDef *self = *((b2MotorJointDef **)dub::checksdata_n(L, 1, "b2.b2MotorJointDef"));
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

/** b2MotorJointDef::b2MotorJointDef()
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/Joints/b2MotorJoint.h:27
 */
static int b2MotorJointDef_b2MotorJointDef(lua_State *L) {
  try {
    b2MotorJointDef *retval__ = new b2MotorJointDef();
    dub::pushudata(L, retval__, "b2.b2MotorJointDef", true);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "new: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "new: Unknown exception");
  }
  return dub::error(L);
}

/** void b2MotorJointDef::Initialize(b2Body *bodyA, b2Body *bodyB)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/Joints/b2MotorJoint.h:38
 */
static int b2MotorJointDef_Initialize(lua_State *L) {
  try {
    b2MotorJointDef *self = *((b2MotorJointDef **)dub::checksdata(L, 1, "b2.b2MotorJointDef"));
    b2Body *bodyA = *((b2Body **)dub::checksdata(L, 2, "b2.b2Body"));
    b2Body *bodyB = *((b2Body **)dub::checksdata(L, 3, "b2.b2Body"));
    self->Initialize(bodyA, bodyB);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "Initialize: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "Initialize: Unknown exception");
  }
  return dub::error(L);
}



// --=============================================== __tostring
static int b2MotorJointDef___tostring(lua_State *L) {
  b2MotorJointDef *self = *((b2MotorJointDef **)dub::checksdata_n(L, 1, "b2.b2MotorJointDef"));
  lua_pushfstring(L, "b2.b2MotorJointDef: %p", self);
  
  return 1;
}

// --=============================================== METHODS

static const struct luaL_Reg b2MotorJointDef_member_methods[] = {
  { "__gc"         , b2MotorJointDef__b2MotorJointDef },
  { "__newindex"   , b2MotorJointDef__set_ },
  { "__index"      , b2MotorJointDef__get_ },
  { "_cast_"       , b2MotorJointDef__cast_ },
  { "new"          , b2MotorJointDef_b2MotorJointDef },
  { "Initialize"   , b2MotorJointDef_Initialize },
  { "__tostring"   , b2MotorJointDef___tostring },
  { "deleted"      , dub::isDeleted       },
  { NULL, NULL},
};


extern "C" int luaopen_b2_b2MotorJointDef(lua_State *L)
{
  // Create the metatable which will contain all the member methods
  luaL_newmetatable(L, "b2.b2MotorJointDef");
  // <mt>

  // register member methods
  dub::fregister(L, b2MotorJointDef_member_methods);
  // setup meta-table
  dub::setup(L, "b2.b2MotorJointDef");
  // <mt>
  return 1;
}