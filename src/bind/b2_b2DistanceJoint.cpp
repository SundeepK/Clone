/**
 *
 * MACHINE GENERATED FILE. DO NOT EDIT.
 *
 * Bindings for class b2DistanceJoint
 *
 * This file has been generated by dub 2.2.0.
 */
#include "dub/dub.h"
#include <Box2D/Box2D.h>


/** ~b2DistanceJoint()
 * 
 */
static int b2DistanceJoint__b2DistanceJoint(lua_State *L) {
  try {
    DubUserdata *userdata = ((DubUserdata*)dub::checksdata_d(L, 1, "b2.b2DistanceJoint"));
    if (userdata->gc) {
      b2DistanceJoint *self = (b2DistanceJoint *)userdata->ptr;
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

/** Cast (class_name)
 * 
 */
static int b2DistanceJoint__cast_(lua_State *L) {

  b2DistanceJoint *self = *((b2DistanceJoint **)dub::checksdata_n(L, 1, "b2.b2DistanceJoint"));
  const char *key = luaL_checkstring(L, 2);
  void **retval__ = (void**)lua_newuserdata(L, sizeof(void*));
  int key_h = dub::hash(key, 2);
  switch(key_h) {
    case 0: {
      if (DUB_ASSERT_KEY(key, "b2.b2Joint")) break;
      *retval__ = static_cast<b2Joint *>(self);
      return 1;
    }
  }
  return 0;
}

/** b2Vec2 b2DistanceJoint::GetAnchorA() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/Joints/b2DistanceJoint.h:71
 */
static int b2DistanceJoint_GetAnchorA(lua_State *L) {
  try {
    b2DistanceJoint *self = *((b2DistanceJoint **)dub::checksdata(L, 1, "b2.b2DistanceJoint"));
    dub::pushudata(L, new b2Vec2(self->GetAnchorA()), "b2.b2Vec2", true);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetAnchorA: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetAnchorA: Unknown exception");
  }
  return dub::error(L);
}

/** b2Vec2 b2DistanceJoint::GetAnchorB() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/Joints/b2DistanceJoint.h:72
 */
static int b2DistanceJoint_GetAnchorB(lua_State *L) {
  try {
    b2DistanceJoint *self = *((b2DistanceJoint **)dub::checksdata(L, 1, "b2.b2DistanceJoint"));
    dub::pushudata(L, new b2Vec2(self->GetAnchorB()), "b2.b2Vec2", true);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetAnchorB: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetAnchorB: Unknown exception");
  }
  return dub::error(L);
}

/** b2Vec2 b2DistanceJoint::GetReactionForce(float32 inv_dt) const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/Joints/b2DistanceJoint.h:76
 */
static int b2DistanceJoint_GetReactionForce(lua_State *L) {
  try {
    b2DistanceJoint *self = *((b2DistanceJoint **)dub::checksdata(L, 1, "b2.b2DistanceJoint"));
    float32 inv_dt = dub::checknumber(L, 2);
    dub::pushudata(L, new b2Vec2(self->GetReactionForce(inv_dt)), "b2.b2Vec2", true);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetReactionForce: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetReactionForce: Unknown exception");
  }
  return dub::error(L);
}

/** float32 b2DistanceJoint::GetReactionTorque(float32 inv_dt) const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/Joints/b2DistanceJoint.h:80
 */
static int b2DistanceJoint_GetReactionTorque(lua_State *L) {
  try {
    b2DistanceJoint *self = *((b2DistanceJoint **)dub::checksdata(L, 1, "b2.b2DistanceJoint"));
    float32 inv_dt = dub::checknumber(L, 2);
    lua_pushnumber(L, self->GetReactionTorque(inv_dt));
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetReactionTorque: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetReactionTorque: Unknown exception");
  }
  return dub::error(L);
}

/** const b2Vec2& b2DistanceJoint::GetLocalAnchorA() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/Joints/b2DistanceJoint.h:83
 */
static int b2DistanceJoint_GetLocalAnchorA(lua_State *L) {
  try {
    b2DistanceJoint *self = *((b2DistanceJoint **)dub::checksdata(L, 1, "b2.b2DistanceJoint"));
    dub::pushudata(L, const_cast<b2Vec2*>(&self->GetLocalAnchorA()), "b2.b2Vec2", false);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetLocalAnchorA: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetLocalAnchorA: Unknown exception");
  }
  return dub::error(L);
}

/** const b2Vec2& b2DistanceJoint::GetLocalAnchorB() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/Joints/b2DistanceJoint.h:86
 */
static int b2DistanceJoint_GetLocalAnchorB(lua_State *L) {
  try {
    b2DistanceJoint *self = *((b2DistanceJoint **)dub::checksdata(L, 1, "b2.b2DistanceJoint"));
    dub::pushudata(L, const_cast<b2Vec2*>(&self->GetLocalAnchorB()), "b2.b2Vec2", false);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetLocalAnchorB: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetLocalAnchorB: Unknown exception");
  }
  return dub::error(L);
}

/** void b2DistanceJoint::SetLength(float32 length)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/Joints/b2DistanceJoint.h:90
 */
static int b2DistanceJoint_SetLength(lua_State *L) {
  try {
    b2DistanceJoint *self = *((b2DistanceJoint **)dub::checksdata(L, 1, "b2.b2DistanceJoint"));
    float32 length = dub::checknumber(L, 2);
    self->SetLength(length);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "SetLength: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "SetLength: Unknown exception");
  }
  return dub::error(L);
}

/** float32 b2DistanceJoint::GetLength() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/Joints/b2DistanceJoint.h:91
 */
static int b2DistanceJoint_GetLength(lua_State *L) {
  try {
    b2DistanceJoint *self = *((b2DistanceJoint **)dub::checksdata(L, 1, "b2.b2DistanceJoint"));
    lua_pushnumber(L, self->GetLength());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetLength: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetLength: Unknown exception");
  }
  return dub::error(L);
}

/** void b2DistanceJoint::SetFrequency(float32 hz)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/Joints/b2DistanceJoint.h:94
 */
static int b2DistanceJoint_SetFrequency(lua_State *L) {
  try {
    b2DistanceJoint *self = *((b2DistanceJoint **)dub::checksdata(L, 1, "b2.b2DistanceJoint"));
    float32 hz = dub::checknumber(L, 2);
    self->SetFrequency(hz);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "SetFrequency: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "SetFrequency: Unknown exception");
  }
  return dub::error(L);
}

/** float32 b2DistanceJoint::GetFrequency() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/Joints/b2DistanceJoint.h:95
 */
static int b2DistanceJoint_GetFrequency(lua_State *L) {
  try {
    b2DistanceJoint *self = *((b2DistanceJoint **)dub::checksdata(L, 1, "b2.b2DistanceJoint"));
    lua_pushnumber(L, self->GetFrequency());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetFrequency: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetFrequency: Unknown exception");
  }
  return dub::error(L);
}

/** void b2DistanceJoint::SetDampingRatio(float32 ratio)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/Joints/b2DistanceJoint.h:98
 */
static int b2DistanceJoint_SetDampingRatio(lua_State *L) {
  try {
    b2DistanceJoint *self = *((b2DistanceJoint **)dub::checksdata(L, 1, "b2.b2DistanceJoint"));
    float32 ratio = dub::checknumber(L, 2);
    self->SetDampingRatio(ratio);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "SetDampingRatio: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "SetDampingRatio: Unknown exception");
  }
  return dub::error(L);
}

/** float32 b2DistanceJoint::GetDampingRatio() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/Joints/b2DistanceJoint.h:99
 */
static int b2DistanceJoint_GetDampingRatio(lua_State *L) {
  try {
    b2DistanceJoint *self = *((b2DistanceJoint **)dub::checksdata(L, 1, "b2.b2DistanceJoint"));
    lua_pushnumber(L, self->GetDampingRatio());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetDampingRatio: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetDampingRatio: Unknown exception");
  }
  return dub::error(L);
}

/** void b2DistanceJoint::Dump()
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/Joints/b2DistanceJoint.h:102
 */
static int b2DistanceJoint_Dump(lua_State *L) {
  try {
    b2DistanceJoint *self = *((b2DistanceJoint **)dub::checksdata(L, 1, "b2.b2DistanceJoint"));
    self->Dump();
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "Dump: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "Dump: Unknown exception");
  }
  return dub::error(L);
}

/** b2JointType b2Joint::GetType() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/Joints/b2Joint.h:108
 */
static int b2DistanceJoint_GetType(lua_State *L) {
  try {
    b2DistanceJoint *self = *((b2DistanceJoint **)dub::checksdata(L, 1, "b2.b2DistanceJoint"));
    lua_pushnumber(L, self->GetType());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetType: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetType: Unknown exception");
  }
  return dub::error(L);
}

/** b2Body * b2Joint::GetBodyA()
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/Joints/b2Joint.h:111
 */
static int b2DistanceJoint_GetBodyA(lua_State *L) {
  try {
    b2DistanceJoint *self = *((b2DistanceJoint **)dub::checksdata(L, 1, "b2.b2DistanceJoint"));
    b2Body *retval__ = self->GetBodyA();
    if (!retval__) return 0;
    dub::pushudata(L, retval__, "b2.b2Body", false);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetBodyA: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetBodyA: Unknown exception");
  }
  return dub::error(L);
}

/** b2Body * b2Joint::GetBodyB()
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/Joints/b2Joint.h:114
 */
static int b2DistanceJoint_GetBodyB(lua_State *L) {
  try {
    b2DistanceJoint *self = *((b2DistanceJoint **)dub::checksdata(L, 1, "b2.b2DistanceJoint"));
    b2Body *retval__ = self->GetBodyB();
    if (!retval__) return 0;
    dub::pushudata(L, retval__, "b2.b2Body", false);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetBodyB: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetBodyB: Unknown exception");
  }
  return dub::error(L);
}

/** b2Joint * b2Joint::GetNext()
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/Joints/b2Joint.h:129
 */
static int b2DistanceJoint_GetNext(lua_State *L) {
  try {
    b2DistanceJoint *self = *((b2DistanceJoint **)dub::checksdata(L, 1, "b2.b2DistanceJoint"));
    b2Joint *retval__ = self->GetNext();
    if (!retval__) return 0;
    dub::pushudata(L, retval__, "b2.b2Joint", false);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetNext: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetNext: Unknown exception");
  }
  return dub::error(L);
}

/** void * b2Joint::GetUserData() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/Joints/b2Joint.h:133
 */
static int b2DistanceJoint_GetUserData(lua_State *L) {
  try {
    b2DistanceJoint *self = *((b2DistanceJoint **)dub::checksdata(L, 1, "b2.b2DistanceJoint"));
    self->GetUserData();
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetUserData: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetUserData: Unknown exception");
  }
  return dub::error(L);
}

/** void b2Joint::SetUserData(void *data)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/Joints/b2Joint.h:136
 */
static int b2DistanceJoint_SetUserData(lua_State *L) {
  try {
    b2DistanceJoint *self = *((b2DistanceJoint **)dub::checksdata(L, 1, "b2.b2DistanceJoint"));
    void *data = *((void **)dub::checksdata(L, 2, "void"));
    self->SetUserData(data);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "SetUserData: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "SetUserData: Unknown exception");
  }
  return dub::error(L);
}

/** bool b2Joint::IsActive() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/Joints/b2Joint.h:139
 */
static int b2DistanceJoint_IsActive(lua_State *L) {
  try {
    b2DistanceJoint *self = *((b2DistanceJoint **)dub::checksdata(L, 1, "b2.b2DistanceJoint"));
    lua_pushboolean(L, self->IsActive());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "IsActive: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "IsActive: Unknown exception");
  }
  return dub::error(L);
}

/** bool b2Joint::GetCollideConnected() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/Joints/b2Joint.h:144
 */
static int b2DistanceJoint_GetCollideConnected(lua_State *L) {
  try {
    b2DistanceJoint *self = *((b2DistanceJoint **)dub::checksdata(L, 1, "b2.b2DistanceJoint"));
    lua_pushboolean(L, self->GetCollideConnected());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetCollideConnected: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetCollideConnected: Unknown exception");
  }
  return dub::error(L);
}

/** virtual void b2Joint::ShiftOrigin(const b2Vec2 &newOrigin)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/Joints/b2Joint.h:150
 */
static int b2DistanceJoint_ShiftOrigin(lua_State *L) {
  try {
    b2DistanceJoint *self = *((b2DistanceJoint **)dub::checksdata(L, 1, "b2.b2DistanceJoint"));
    b2Vec2 *newOrigin = *((b2Vec2 **)dub::checksdata(L, 2, "b2.b2Vec2"));
    self->ShiftOrigin(*newOrigin);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "ShiftOrigin: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "ShiftOrigin: Unknown exception");
  }
  return dub::error(L);
}



// --=============================================== __tostring
static int b2DistanceJoint___tostring(lua_State *L) {
  b2DistanceJoint *self = *((b2DistanceJoint **)dub::checksdata_n(L, 1, "b2.b2DistanceJoint"));
  lua_pushfstring(L, "b2.b2DistanceJoint: %p", self);
  
  return 1;
}

// --=============================================== METHODS

static const struct luaL_Reg b2DistanceJoint_member_methods[] = {
  { "__gc"         , b2DistanceJoint__b2DistanceJoint },
  { "_cast_"       , b2DistanceJoint__cast_ },
  { "GetAnchorA"   , b2DistanceJoint_GetAnchorA },
  { "GetAnchorB"   , b2DistanceJoint_GetAnchorB },
  { "GetReactionForce", b2DistanceJoint_GetReactionForce },
  { "GetReactionTorque", b2DistanceJoint_GetReactionTorque },
  { "GetLocalAnchorA", b2DistanceJoint_GetLocalAnchorA },
  { "GetLocalAnchorB", b2DistanceJoint_GetLocalAnchorB },
  { "SetLength"    , b2DistanceJoint_SetLength },
  { "GetLength"    , b2DistanceJoint_GetLength },
  { "SetFrequency" , b2DistanceJoint_SetFrequency },
  { "GetFrequency" , b2DistanceJoint_GetFrequency },
  { "SetDampingRatio", b2DistanceJoint_SetDampingRatio },
  { "GetDampingRatio", b2DistanceJoint_GetDampingRatio },
  { "Dump"         , b2DistanceJoint_Dump },
  { "GetType"      , b2DistanceJoint_GetType },
  { "GetBodyA"     , b2DistanceJoint_GetBodyA },
  { "GetBodyB"     , b2DistanceJoint_GetBodyB },
  { "GetNext"      , b2DistanceJoint_GetNext },
  { "GetUserData"  , b2DistanceJoint_GetUserData },
  { "SetUserData"  , b2DistanceJoint_SetUserData },
  { "IsActive"     , b2DistanceJoint_IsActive },
  { "GetCollideConnected", b2DistanceJoint_GetCollideConnected },
  { "ShiftOrigin"  , b2DistanceJoint_ShiftOrigin },
  { "__tostring"   , b2DistanceJoint___tostring },
  { "deleted"      , dub::isDeleted       },
  { NULL, NULL},
};


extern "C" int luaopen_b2_b2DistanceJoint(lua_State *L)
{
  // Create the metatable which will contain all the member methods
  luaL_newmetatable(L, "b2.b2DistanceJoint");
  // <mt>

  // register member methods
  dub::fregister(L, b2DistanceJoint_member_methods);
  // setup meta-table
  dub::setup(L, "b2.b2DistanceJoint");
  // <mt>
  return 1;
}
