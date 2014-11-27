/**
 *
 * MACHINE GENERATED FILE. DO NOT EDIT.
 *
 * Bindings for class b2BroadPhase
 *
 * This file has been generated by dub 2.2.0.
 */
#include "dub/dub.h"
#include <Box2D/Box2D.h>


/** b2BroadPhase::b2BroadPhase()
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/b2BroadPhase.h:45
 */
static int b2BroadPhase_b2BroadPhase(lua_State *L) {
  try {
    b2BroadPhase *retval__ = new b2BroadPhase();
    dub::pushudata(L, retval__, "b2.b2BroadPhase", true);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "new: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "new: Unknown exception");
  }
  return dub::error(L);
}

/** b2BroadPhase::~b2BroadPhase()
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/b2BroadPhase.h:46
 */
static int b2BroadPhase__b2BroadPhase(lua_State *L) {
  try {
    DubUserdata *userdata = ((DubUserdata*)dub::checksdata_d(L, 1, "b2.b2BroadPhase"));
    if (userdata->gc) {
      b2BroadPhase *self = (b2BroadPhase *)userdata->ptr;
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

/** int32 b2BroadPhase::CreateProxy(const b2AABB &aabb, void *userData)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/b2BroadPhase.h:50
 */
static int b2BroadPhase_CreateProxy(lua_State *L) {
  try {
    b2BroadPhase *self = *((b2BroadPhase **)dub::checksdata(L, 1, "b2.b2BroadPhase"));
    b2AABB *aabb = *((b2AABB **)dub::checksdata(L, 2, "b2.b2AABB"));
    void *userData = *((void **)dub::checksdata(L, 3, "void"));
    lua_pushnumber(L, self->CreateProxy(*aabb, userData));
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "CreateProxy: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "CreateProxy: Unknown exception");
  }
  return dub::error(L);
}

/** void b2BroadPhase::DestroyProxy(int32 proxyId)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/b2BroadPhase.h:53
 */
static int b2BroadPhase_DestroyProxy(lua_State *L) {
  try {
    b2BroadPhase *self = *((b2BroadPhase **)dub::checksdata(L, 1, "b2.b2BroadPhase"));
    int32 proxyId = dub::checkint(L, 2);
    self->DestroyProxy(proxyId);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "DestroyProxy: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "DestroyProxy: Unknown exception");
  }
  return dub::error(L);
}

/** void b2BroadPhase::MoveProxy(int32 proxyId, const b2AABB &aabb, const b2Vec2 &displacement)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/b2BroadPhase.h:57
 */
static int b2BroadPhase_MoveProxy(lua_State *L) {
  try {
    b2BroadPhase *self = *((b2BroadPhase **)dub::checksdata(L, 1, "b2.b2BroadPhase"));
    int32 proxyId = dub::checkint(L, 2);
    b2AABB *aabb = *((b2AABB **)dub::checksdata(L, 3, "b2.b2AABB"));
    b2Vec2 *displacement = *((b2Vec2 **)dub::checksdata(L, 4, "b2.b2Vec2"));
    self->MoveProxy(proxyId, *aabb, *displacement);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "MoveProxy: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "MoveProxy: Unknown exception");
  }
  return dub::error(L);
}

/** void b2BroadPhase::TouchProxy(int32 proxyId)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/b2BroadPhase.h:60
 */
static int b2BroadPhase_TouchProxy(lua_State *L) {
  try {
    b2BroadPhase *self = *((b2BroadPhase **)dub::checksdata(L, 1, "b2.b2BroadPhase"));
    int32 proxyId = dub::checkint(L, 2);
    self->TouchProxy(proxyId);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "TouchProxy: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "TouchProxy: Unknown exception");
  }
  return dub::error(L);
}

/** const b2AABB & b2BroadPhase::GetFatAABB(int32 proxyId) const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/b2BroadPhase.h:63
 */
static int b2BroadPhase_GetFatAABB(lua_State *L) {
  try {
    b2BroadPhase *self = *((b2BroadPhase **)dub::checksdata(L, 1, "b2.b2BroadPhase"));
    int32 proxyId = dub::checkint(L, 2);
    dub::pushudata(L, const_cast<b2AABB*>(&self->GetFatAABB(proxyId)), "b2.b2AABB", false);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetFatAABB: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetFatAABB: Unknown exception");
  }
  return dub::error(L);
}

/** void * b2BroadPhase::GetUserData(int32 proxyId) const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/b2BroadPhase.h:66
 */
static int b2BroadPhase_GetUserData(lua_State *L) {
  try {
    b2BroadPhase *self = *((b2BroadPhase **)dub::checksdata(L, 1, "b2.b2BroadPhase"));
    int32 proxyId = dub::checkint(L, 2);
    self->GetUserData(proxyId);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetUserData: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetUserData: Unknown exception");
  }
  return dub::error(L);
}

/** bool b2BroadPhase::TestOverlap(int32 proxyIdA, int32 proxyIdB) const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/b2BroadPhase.h:69
 */
static int b2BroadPhase_TestOverlap(lua_State *L) {
  try {
    b2BroadPhase *self = *((b2BroadPhase **)dub::checksdata(L, 1, "b2.b2BroadPhase"));
    int32 proxyIdA = dub::checkint(L, 2);
    int32 proxyIdB = dub::checkint(L, 3);
    lua_pushboolean(L, self->TestOverlap(proxyIdA, proxyIdB));
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "TestOverlap: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "TestOverlap: Unknown exception");
  }
  return dub::error(L);
}

/** int32 b2BroadPhase::GetProxyCount() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/b2BroadPhase.h:72
 */
static int b2BroadPhase_GetProxyCount(lua_State *L) {
  try {
    b2BroadPhase *self = *((b2BroadPhase **)dub::checksdata(L, 1, "b2.b2BroadPhase"));
    lua_pushnumber(L, self->GetProxyCount());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetProxyCount: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetProxyCount: Unknown exception");
  }
  return dub::error(L);
}

/** int32 b2BroadPhase::GetTreeHeight() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/b2BroadPhase.h:94
 */
static int b2BroadPhase_GetTreeHeight(lua_State *L) {
  try {
    b2BroadPhase *self = *((b2BroadPhase **)dub::checksdata(L, 1, "b2.b2BroadPhase"));
    lua_pushnumber(L, self->GetTreeHeight());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetTreeHeight: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetTreeHeight: Unknown exception");
  }
  return dub::error(L);
}

/** int32 b2BroadPhase::GetTreeBalance() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/b2BroadPhase.h:97
 */
static int b2BroadPhase_GetTreeBalance(lua_State *L) {
  try {
    b2BroadPhase *self = *((b2BroadPhase **)dub::checksdata(L, 1, "b2.b2BroadPhase"));
    lua_pushnumber(L, self->GetTreeBalance());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetTreeBalance: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetTreeBalance: Unknown exception");
  }
  return dub::error(L);
}

/** float32 b2BroadPhase::GetTreeQuality() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/b2BroadPhase.h:100
 */
static int b2BroadPhase_GetTreeQuality(lua_State *L) {
  try {
    b2BroadPhase *self = *((b2BroadPhase **)dub::checksdata(L, 1, "b2.b2BroadPhase"));
    lua_pushnumber(L, self->GetTreeQuality());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetTreeQuality: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetTreeQuality: Unknown exception");
  }
  return dub::error(L);
}

/** void b2BroadPhase::ShiftOrigin(const b2Vec2 &newOrigin)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/b2BroadPhase.h:105
 */
static int b2BroadPhase_ShiftOrigin(lua_State *L) {
  try {
    b2BroadPhase *self = *((b2BroadPhase **)dub::checksdata(L, 1, "b2.b2BroadPhase"));
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
static int b2BroadPhase___tostring(lua_State *L) {
  b2BroadPhase *self = *((b2BroadPhase **)dub::checksdata_n(L, 1, "b2.b2BroadPhase"));
  lua_pushfstring(L, "b2.b2BroadPhase: %p", self);
  
  return 1;
}

// --=============================================== METHODS

static const struct luaL_Reg b2BroadPhase_member_methods[] = {
  { "new"          , b2BroadPhase_b2BroadPhase },
  { "__gc"         , b2BroadPhase__b2BroadPhase },
  { "CreateProxy"  , b2BroadPhase_CreateProxy },
  { "DestroyProxy" , b2BroadPhase_DestroyProxy },
  { "MoveProxy"    , b2BroadPhase_MoveProxy },
  { "TouchProxy"   , b2BroadPhase_TouchProxy },
  { "GetFatAABB"   , b2BroadPhase_GetFatAABB },
  { "GetUserData"  , b2BroadPhase_GetUserData },
  { "TestOverlap"  , b2BroadPhase_TestOverlap },
  { "GetProxyCount", b2BroadPhase_GetProxyCount },
  { "GetTreeHeight", b2BroadPhase_GetTreeHeight },
  { "GetTreeBalance", b2BroadPhase_GetTreeBalance },
  { "GetTreeQuality", b2BroadPhase_GetTreeQuality },
  { "ShiftOrigin"  , b2BroadPhase_ShiftOrigin },
  { "__tostring"   , b2BroadPhase___tostring },
  { "deleted"      , dub::isDeleted       },
  { NULL, NULL},
};

// --=============================================== CONSTANTS
static const struct dub::const_Reg b2BroadPhase_const[] = {
  { "e_nullProxy"  , b2BroadPhase::e_nullProxy },
  { NULL, 0},
};

extern "C" int luaopen_b2_b2BroadPhase(lua_State *L)
{
  // Create the metatable which will contain all the member methods
  luaL_newmetatable(L, "b2.b2BroadPhase");
  // <mt>
  // register class constants
  dub::register_const(L, b2BroadPhase_const);

  // register member methods
  dub::fregister(L, b2BroadPhase_member_methods);
  // setup meta-table
  dub::setup(L, "b2.b2BroadPhase");
  // <mt>
  return 1;
}
