/**
 *
 * MACHINE GENERATED FILE. DO NOT EDIT.
 *
 * Bindings for class b2Body
 *
 * This file has been generated by dub 2.2.0.
 */
#include "dub/dub.h"
#include <Box2D/Box2D.h>


/** b2Fixture * b2Body::CreateFixture(const b2FixtureDef *def)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:136
 */
static int b2Body_CreateFixture(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    int top__ = lua_gettop(L);
    if (top__ >= 3) {
      b2Shape *shape = *((b2Shape **)dub::checksdata(L, 2, "b2.b2Shape"));
      float32 density = dub::checknumber(L, 3);
      b2Fixture *retval__ = self->CreateFixture(shape, density);
      if (!retval__) return 0;
      dub::pushudata(L, retval__, "b2.b2Fixture", false);
      return 1;
    } else {
      b2FixtureDef *def = *((b2FixtureDef **)dub::checksdata(L, 2, "b2.b2FixtureDef"));
      b2Fixture *retval__ = self->CreateFixture(def);
      if (!retval__) return 0;
      dub::pushudata(L, retval__, "b2.b2Fixture", false);
      return 1;
    }
  } catch (std::exception &e) {
    lua_pushfstring(L, "CreateFixture: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "CreateFixture: Unknown exception");
  }
  return dub::error(L);
}

/** void b2Body::DestroyFixture(b2Fixture *fixture)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:154
 */
static int b2Body_DestroyFixture(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    b2Fixture *fixture = *((b2Fixture **)dub::checksdata(L, 2, "b2.b2Fixture"));
    self->DestroyFixture(fixture);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "DestroyFixture: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "DestroyFixture: Unknown exception");
  }
  return dub::error(L);
}

/** void b2Body::SetTransform(const b2Vec2 &position, float32 angle)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:161
 */
static int b2Body_SetTransform(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    b2Vec2 *position = *((b2Vec2 **)dub::checksdata(L, 2, "b2.b2Vec2"));
    float32 angle = dub::checknumber(L, 3);
    self->SetTransform(*position, angle);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "SetTransform: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "SetTransform: Unknown exception");
  }
  return dub::error(L);
}

/** const b2Transform & b2Body::GetTransform() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:165
 */
static int b2Body_GetTransform(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    dub::pushudata(L, const_cast<b2Transform*>(&self->GetTransform()), "b2.b2Transform", false);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetTransform: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetTransform: Unknown exception");
  }
  return dub::error(L);
}

/** const b2Vec2 & b2Body::GetPosition() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:169
 */
static int b2Body_GetPosition(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    dub::pushudata(L, const_cast<b2Vec2*>(&self->GetPosition()), "b2.b2Vec2", false);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetPosition: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetPosition: Unknown exception");
  }
  return dub::error(L);
}

/** float32 b2Body::GetAngle() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:173
 */
static int b2Body_GetAngle(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    lua_pushnumber(L, self->GetAngle());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetAngle: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetAngle: Unknown exception");
  }
  return dub::error(L);
}

/** const b2Vec2 & b2Body::GetWorldCenter() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:176
 */
static int b2Body_GetWorldCenter(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    dub::pushudata(L, const_cast<b2Vec2*>(&self->GetWorldCenter()), "b2.b2Vec2", false);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetWorldCenter: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetWorldCenter: Unknown exception");
  }
  return dub::error(L);
}

/** const b2Vec2 & b2Body::GetLocalCenter() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:179
 */
static int b2Body_GetLocalCenter(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    dub::pushudata(L, const_cast<b2Vec2*>(&self->GetLocalCenter()), "b2.b2Vec2", false);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetLocalCenter: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetLocalCenter: Unknown exception");
  }
  return dub::error(L);
}

/** void b2Body::SetLinearVelocity(const b2Vec2 &v)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:183
 */
static int b2Body_SetLinearVelocity(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    b2Vec2 *v = *((b2Vec2 **)dub::checksdata(L, 2, "b2.b2Vec2"));
    self->SetLinearVelocity(*v);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "SetLinearVelocity: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "SetLinearVelocity: Unknown exception");
  }
  return dub::error(L);
}

/** const b2Vec2 & b2Body::GetLinearVelocity() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:187
 */
static int b2Body_GetLinearVelocity(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    dub::pushudata(L, const_cast<b2Vec2*>(&self->GetLinearVelocity()), "b2.b2Vec2", false);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetLinearVelocity: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetLinearVelocity: Unknown exception");
  }
  return dub::error(L);
}

/** void b2Body::SetAngularVelocity(float32 omega)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:191
 */
static int b2Body_SetAngularVelocity(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    float32 omega = dub::checknumber(L, 2);
    self->SetAngularVelocity(omega);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "SetAngularVelocity: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "SetAngularVelocity: Unknown exception");
  }
  return dub::error(L);
}

/** float32 b2Body::GetAngularVelocity() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:195
 */
static int b2Body_GetAngularVelocity(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    lua_pushnumber(L, self->GetAngularVelocity());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetAngularVelocity: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetAngularVelocity: Unknown exception");
  }
  return dub::error(L);
}

/** void b2Body::ApplyForce(const b2Vec2 &force, const b2Vec2 &point, bool wake)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:203
 */
static int b2Body_ApplyForce(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    b2Vec2 *force = *((b2Vec2 **)dub::checksdata(L, 2, "b2.b2Vec2"));
    b2Vec2 *point = *((b2Vec2 **)dub::checksdata(L, 3, "b2.b2Vec2"));
    bool wake = dub::checkboolean(L, 4);
    self->ApplyForce(*force, *point, wake);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "ApplyForce: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "ApplyForce: Unknown exception");
  }
  return dub::error(L);
}

/** void b2Body::ApplyForceToCenter(const b2Vec2 &force, bool wake)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:208
 */
static int b2Body_ApplyForceToCenter(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    b2Vec2 *force = *((b2Vec2 **)dub::checksdata(L, 2, "b2.b2Vec2"));
    bool wake = dub::checkboolean(L, 3);
    self->ApplyForceToCenter(*force, wake);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "ApplyForceToCenter: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "ApplyForceToCenter: Unknown exception");
  }
  return dub::error(L);
}

/** void b2Body::ApplyTorque(float32 torque, bool wake)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:215
 */
static int b2Body_ApplyTorque(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    float32 torque = dub::checknumber(L, 2);
    bool wake = dub::checkboolean(L, 3);
    self->ApplyTorque(torque, wake);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "ApplyTorque: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "ApplyTorque: Unknown exception");
  }
  return dub::error(L);
}

/** void b2Body::ApplyLinearImpulse(const b2Vec2 &impulse, const b2Vec2 &point, bool wake)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:223
 */
static int b2Body_ApplyLinearImpulse(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    b2Vec2 *impulse = *((b2Vec2 **)dub::checksdata(L, 2, "b2.b2Vec2"));
    b2Vec2 *point = *((b2Vec2 **)dub::checksdata(L, 3, "b2.b2Vec2"));
    bool wake = dub::checkboolean(L, 4);
    self->ApplyLinearImpulse(*impulse, *point, wake);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "ApplyLinearImpulse: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "ApplyLinearImpulse: Unknown exception");
  }
  return dub::error(L);
}

/** void b2Body::ApplyAngularImpulse(float32 impulse, bool wake)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:228
 */
static int b2Body_ApplyAngularImpulse(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    float32 impulse = dub::checknumber(L, 2);
    bool wake = dub::checkboolean(L, 3);
    self->ApplyAngularImpulse(impulse, wake);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "ApplyAngularImpulse: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "ApplyAngularImpulse: Unknown exception");
  }
  return dub::error(L);
}

/** float32 b2Body::GetMass() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:232
 */
static int b2Body_GetMass(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    lua_pushnumber(L, self->GetMass());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetMass: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetMass: Unknown exception");
  }
  return dub::error(L);
}

/** float32 b2Body::GetInertia() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:236
 */
static int b2Body_GetInertia(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    lua_pushnumber(L, self->GetInertia());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetInertia: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetInertia: Unknown exception");
  }
  return dub::error(L);
}

/** void b2Body::GetMassData(b2MassData *data) const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:240
 */
static int b2Body_GetMassData(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    b2MassData *data = *((b2MassData **)dub::checksdata(L, 2, "b2.b2MassData"));
    self->GetMassData(data);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetMassData: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetMassData: Unknown exception");
  }
  return dub::error(L);
}

/** void b2Body::SetMassData(const b2MassData *data)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:247
 */
static int b2Body_SetMassData(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    b2MassData *data = *((b2MassData **)dub::checksdata(L, 2, "b2.b2MassData"));
    self->SetMassData(data);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "SetMassData: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "SetMassData: Unknown exception");
  }
  return dub::error(L);
}

/** void b2Body::ResetMassData()
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:252
 */
static int b2Body_ResetMassData(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    self->ResetMassData();
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "ResetMassData: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "ResetMassData: Unknown exception");
  }
  return dub::error(L);
}

/** b2Vec2 b2Body::GetWorldPoint(const b2Vec2 &localPoint) const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:257
 */
static int b2Body_GetWorldPoint(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    b2Vec2 *localPoint = *((b2Vec2 **)dub::checksdata(L, 2, "b2.b2Vec2"));
    dub::pushudata(L, new b2Vec2(self->GetWorldPoint(*localPoint)), "b2.b2Vec2", true);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetWorldPoint: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetWorldPoint: Unknown exception");
  }
  return dub::error(L);
}

/** b2Vec2 b2Body::GetWorldVector(const b2Vec2 &localVector) const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:262
 */
static int b2Body_GetWorldVector(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    b2Vec2 *localVector = *((b2Vec2 **)dub::checksdata(L, 2, "b2.b2Vec2"));
    dub::pushudata(L, new b2Vec2(self->GetWorldVector(*localVector)), "b2.b2Vec2", true);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetWorldVector: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetWorldVector: Unknown exception");
  }
  return dub::error(L);
}

/** b2Vec2 b2Body::GetLocalPoint(const b2Vec2 &worldPoint) const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:267
 */
static int b2Body_GetLocalPoint(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    b2Vec2 *worldPoint = *((b2Vec2 **)dub::checksdata(L, 2, "b2.b2Vec2"));
    dub::pushudata(L, new b2Vec2(self->GetLocalPoint(*worldPoint)), "b2.b2Vec2", true);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetLocalPoint: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetLocalPoint: Unknown exception");
  }
  return dub::error(L);
}

/** b2Vec2 b2Body::GetLocalVector(const b2Vec2 &worldVector) const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:272
 */
static int b2Body_GetLocalVector(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    b2Vec2 *worldVector = *((b2Vec2 **)dub::checksdata(L, 2, "b2.b2Vec2"));
    dub::pushudata(L, new b2Vec2(self->GetLocalVector(*worldVector)), "b2.b2Vec2", true);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetLocalVector: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetLocalVector: Unknown exception");
  }
  return dub::error(L);
}

/** b2Vec2 b2Body::GetLinearVelocityFromWorldPoint(const b2Vec2 &worldPoint) const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:277
 */
static int b2Body_GetLinearVelocityFromWorldPoint(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    b2Vec2 *worldPoint = *((b2Vec2 **)dub::checksdata(L, 2, "b2.b2Vec2"));
    dub::pushudata(L, new b2Vec2(self->GetLinearVelocityFromWorldPoint(*worldPoint)), "b2.b2Vec2", true);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetLinearVelocityFromWorldPoint: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetLinearVelocityFromWorldPoint: Unknown exception");
  }
  return dub::error(L);
}

/** b2Vec2 b2Body::GetLinearVelocityFromLocalPoint(const b2Vec2 &localPoint) const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:282
 */
static int b2Body_GetLinearVelocityFromLocalPoint(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    b2Vec2 *localPoint = *((b2Vec2 **)dub::checksdata(L, 2, "b2.b2Vec2"));
    dub::pushudata(L, new b2Vec2(self->GetLinearVelocityFromLocalPoint(*localPoint)), "b2.b2Vec2", true);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetLinearVelocityFromLocalPoint: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetLinearVelocityFromLocalPoint: Unknown exception");
  }
  return dub::error(L);
}

/** float32 b2Body::GetLinearDamping() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:285
 */
static int b2Body_GetLinearDamping(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    lua_pushnumber(L, self->GetLinearDamping());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetLinearDamping: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetLinearDamping: Unknown exception");
  }
  return dub::error(L);
}

/** void b2Body::SetLinearDamping(float32 linearDamping)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:288
 */
static int b2Body_SetLinearDamping(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    float32 linearDamping = dub::checknumber(L, 2);
    self->SetLinearDamping(linearDamping);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "SetLinearDamping: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "SetLinearDamping: Unknown exception");
  }
  return dub::error(L);
}

/** float32 b2Body::GetAngularDamping() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:291
 */
static int b2Body_GetAngularDamping(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    lua_pushnumber(L, self->GetAngularDamping());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetAngularDamping: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetAngularDamping: Unknown exception");
  }
  return dub::error(L);
}

/** void b2Body::SetAngularDamping(float32 angularDamping)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:294
 */
static int b2Body_SetAngularDamping(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    float32 angularDamping = dub::checknumber(L, 2);
    self->SetAngularDamping(angularDamping);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "SetAngularDamping: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "SetAngularDamping: Unknown exception");
  }
  return dub::error(L);
}

/** float32 b2Body::GetGravityScale() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:297
 */
static int b2Body_GetGravityScale(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    lua_pushnumber(L, self->GetGravityScale());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetGravityScale: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetGravityScale: Unknown exception");
  }
  return dub::error(L);
}

/** void b2Body::SetGravityScale(float32 scale)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:300
 */
static int b2Body_SetGravityScale(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    float32 scale = dub::checknumber(L, 2);
    self->SetGravityScale(scale);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "SetGravityScale: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "SetGravityScale: Unknown exception");
  }
  return dub::error(L);
}

/** void b2Body::SetType(b2BodyType type)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:303
 */
static int b2Body_SetType(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    b2BodyType type = (b2BodyType)dub::checkint(L, 2);
    self->SetType(type);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "SetType: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "SetType: Unknown exception");
  }
  return dub::error(L);
}

/** b2BodyType b2Body::GetType() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:306
 */
static int b2Body_GetType(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    lua_pushnumber(L, self->GetType());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetType: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetType: Unknown exception");
  }
  return dub::error(L);
}

/** void b2Body::SetBullet(bool flag)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:309
 */
static int b2Body_SetBullet(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    bool flag = dub::checkboolean(L, 2);
    self->SetBullet(flag);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "SetBullet: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "SetBullet: Unknown exception");
  }
  return dub::error(L);
}

/** bool b2Body::IsBullet() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:312
 */
static int b2Body_IsBullet(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    lua_pushboolean(L, self->IsBullet());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "IsBullet: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "IsBullet: Unknown exception");
  }
  return dub::error(L);
}

/** void b2Body::SetSleepingAllowed(bool flag)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:316
 */
static int b2Body_SetSleepingAllowed(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    bool flag = dub::checkboolean(L, 2);
    self->SetSleepingAllowed(flag);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "SetSleepingAllowed: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "SetSleepingAllowed: Unknown exception");
  }
  return dub::error(L);
}

/** bool b2Body::IsSleepingAllowed() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:319
 */
static int b2Body_IsSleepingAllowed(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    lua_pushboolean(L, self->IsSleepingAllowed());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "IsSleepingAllowed: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "IsSleepingAllowed: Unknown exception");
  }
  return dub::error(L);
}

/** void b2Body::SetAwake(bool flag)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:324
 */
static int b2Body_SetAwake(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    bool flag = dub::checkboolean(L, 2);
    self->SetAwake(flag);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "SetAwake: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "SetAwake: Unknown exception");
  }
  return dub::error(L);
}

/** bool b2Body::IsAwake() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:328
 */
static int b2Body_IsAwake(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    lua_pushboolean(L, self->IsAwake());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "IsAwake: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "IsAwake: Unknown exception");
  }
  return dub::error(L);
}

/** void b2Body::SetActive(bool flag)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:343
 */
static int b2Body_SetActive(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    bool flag = dub::checkboolean(L, 2);
    self->SetActive(flag);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "SetActive: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "SetActive: Unknown exception");
  }
  return dub::error(L);
}

/** bool b2Body::IsActive() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:346
 */
static int b2Body_IsActive(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    lua_pushboolean(L, self->IsActive());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "IsActive: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "IsActive: Unknown exception");
  }
  return dub::error(L);
}

/** void b2Body::SetFixedRotation(bool flag)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:350
 */
static int b2Body_SetFixedRotation(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    bool flag = dub::checkboolean(L, 2);
    self->SetFixedRotation(flag);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "SetFixedRotation: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "SetFixedRotation: Unknown exception");
  }
  return dub::error(L);
}

/** bool b2Body::IsFixedRotation() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:353
 */
static int b2Body_IsFixedRotation(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    lua_pushboolean(L, self->IsFixedRotation());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "IsFixedRotation: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "IsFixedRotation: Unknown exception");
  }
  return dub::error(L);
}

/** b2Fixture * b2Body::GetFixtureList()
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:356
 */
static int b2Body_GetFixtureList(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    b2Fixture *retval__ = self->GetFixtureList();
    if (!retval__) return 0;
    dub::pushudata(L, retval__, "b2.b2Fixture", false);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetFixtureList: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetFixtureList: Unknown exception");
  }
  return dub::error(L);
}

/** b2JointEdge * b2Body::GetJointList()
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:360
 */
static int b2Body_GetJointList(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    b2JointEdge *retval__ = self->GetJointList();
    if (!retval__) return 0;
    dub::pushudata(L, retval__, "b2.b2JointEdge", false);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetJointList: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetJointList: Unknown exception");
  }
  return dub::error(L);
}

/** b2ContactEdge * b2Body::GetContactList()
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:366
 */
static int b2Body_GetContactList(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    b2ContactEdge *retval__ = self->GetContactList();
    if (!retval__) return 0;
    dub::pushudata(L, retval__, "b2ContactEdge", false);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetContactList: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetContactList: Unknown exception");
  }
  return dub::error(L);
}

/** b2Body * b2Body::GetNext()
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:370
 */
static int b2Body_GetNext(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    b2Body *retval__ = self->GetNext();
    if (!retval__) return 0;
    dub::pushudata(L, retval__, "b2.b2Body", false);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetNext: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetNext: Unknown exception");
  }
  return dub::error(L);
}

/** void * b2Body::GetUserData() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:374
 */
static int b2Body_GetUserData(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    self->GetUserData();
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetUserData: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetUserData: Unknown exception");
  }
  return dub::error(L);
}

/** void b2Body::SetUserData(void *data)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:377
 */
static int b2Body_SetUserData(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
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

/** b2World * b2Body::GetWorld()
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:380
 */
static int b2Body_GetWorld(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    b2World *retval__ = self->GetWorld();
    if (!retval__) return 0;
    dub::pushudata(L, retval__, "b2.b2World", false);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetWorld: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetWorld: Unknown exception");
  }
  return dub::error(L);
}

/** void b2Body::Dump()
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2Body.h:384
 */
static int b2Body_Dump(lua_State *L) {
  try {
    b2Body *self = *((b2Body **)dub::checksdata(L, 1, "b2.b2Body"));
    self->Dump();
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "Dump: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "Dump: Unknown exception");
  }
  return dub::error(L);
}



// --=============================================== __tostring
static int b2Body___tostring(lua_State *L) {
  b2Body *self = *((b2Body **)dub::checksdata_n(L, 1, "b2.b2Body"));
  lua_pushfstring(L, "b2.b2Body: %p", self);
  
  return 1;
}

// --=============================================== METHODS

static const struct luaL_Reg b2Body_member_methods[] = {
  { "CreateFixture", b2Body_CreateFixture },
  { "DestroyFixture", b2Body_DestroyFixture },
  { "SetTransform" , b2Body_SetTransform  },
  { "GetTransform" , b2Body_GetTransform  },
  { "GetPosition"  , b2Body_GetPosition   },
  { "GetAngle"     , b2Body_GetAngle      },
  { "GetWorldCenter", b2Body_GetWorldCenter },
  { "GetLocalCenter", b2Body_GetLocalCenter },
  { "SetLinearVelocity", b2Body_SetLinearVelocity },
  { "GetLinearVelocity", b2Body_GetLinearVelocity },
  { "SetAngularVelocity", b2Body_SetAngularVelocity },
  { "GetAngularVelocity", b2Body_GetAngularVelocity },
  { "ApplyForce"   , b2Body_ApplyForce    },
  { "ApplyForceToCenter", b2Body_ApplyForceToCenter },
  { "ApplyTorque"  , b2Body_ApplyTorque   },
  { "ApplyLinearImpulse", b2Body_ApplyLinearImpulse },
  { "ApplyAngularImpulse", b2Body_ApplyAngularImpulse },
  { "GetMass"      , b2Body_GetMass       },
  { "GetInertia"   , b2Body_GetInertia    },
  { "GetMassData"  , b2Body_GetMassData   },
  { "SetMassData"  , b2Body_SetMassData   },
  { "ResetMassData", b2Body_ResetMassData },
  { "GetWorldPoint", b2Body_GetWorldPoint },
  { "GetWorldVector", b2Body_GetWorldVector },
  { "GetLocalPoint", b2Body_GetLocalPoint },
  { "GetLocalVector", b2Body_GetLocalVector },
  { "GetLinearVelocityFromWorldPoint", b2Body_GetLinearVelocityFromWorldPoint },
  { "GetLinearVelocityFromLocalPoint", b2Body_GetLinearVelocityFromLocalPoint },
  { "GetLinearDamping", b2Body_GetLinearDamping },
  { "SetLinearDamping", b2Body_SetLinearDamping },
  { "GetAngularDamping", b2Body_GetAngularDamping },
  { "SetAngularDamping", b2Body_SetAngularDamping },
  { "GetGravityScale", b2Body_GetGravityScale },
  { "SetGravityScale", b2Body_SetGravityScale },
  { "SetType"      , b2Body_SetType       },
  { "GetType"      , b2Body_GetType       },
  { "SetBullet"    , b2Body_SetBullet     },
  { "IsBullet"     , b2Body_IsBullet      },
  { "SetSleepingAllowed", b2Body_SetSleepingAllowed },
  { "IsSleepingAllowed", b2Body_IsSleepingAllowed },
  { "SetAwake"     , b2Body_SetAwake      },
  { "IsAwake"      , b2Body_IsAwake       },
  { "SetActive"    , b2Body_SetActive     },
  { "IsActive"     , b2Body_IsActive      },
  { "SetFixedRotation", b2Body_SetFixedRotation },
  { "IsFixedRotation", b2Body_IsFixedRotation },
  { "GetFixtureList", b2Body_GetFixtureList },
  { "GetJointList" , b2Body_GetJointList  },
  { "GetContactList", b2Body_GetContactList },
  { "GetNext"      , b2Body_GetNext       },
  { "GetUserData"  , b2Body_GetUserData   },
  { "SetUserData"  , b2Body_SetUserData   },
  { "GetWorld"     , b2Body_GetWorld      },
  { "Dump"         , b2Body_Dump          },
  { "__tostring"   , b2Body___tostring    },
  { "deleted"      , dub::isDeleted       },
  { NULL, NULL},
};


extern "C" int luaopen_b2_b2Body(lua_State *L)
{
  // Create the metatable which will contain all the member methods
  luaL_newmetatable(L, "b2.b2Body");
  // <mt>

  // register member methods
  dub::fregister(L, b2Body_member_methods);
  // setup meta-table
  dub::setup(L, "b2.b2Body");
  // <mt>
  return 1;
}
