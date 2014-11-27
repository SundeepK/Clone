/**
 *
 * MACHINE GENERATED FILE. DO NOT EDIT.
 *
 * Bindings for class b2ContactListener
 *
 * This file has been generated by dub 2.2.0.
 */
#include "dub/dub.h"
#include <Box2D/Box2D.h>


/** b2ContactListener()
 * 
 */
static int b2ContactListener_b2ContactListener(lua_State *L) {
  try {
    b2ContactListener *retval__ = new b2ContactListener();
    dub::pushudata(L, retval__, "b2.b2ContactListener", true);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "new: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "new: Unknown exception");
  }
  return dub::error(L);
}

/** virtual b2ContactListener::~b2ContactListener()
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2WorldCallbacks.h:84
 */
static int b2ContactListener__b2ContactListener(lua_State *L) {
  try {
    DubUserdata *userdata = ((DubUserdata*)dub::checksdata_d(L, 1, "b2.b2ContactListener"));
    if (userdata->gc) {
      b2ContactListener *self = (b2ContactListener *)userdata->ptr;
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

/** virtual void b2ContactListener::BeginContact(b2Contact *contact)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2WorldCallbacks.h:87
 */
static int b2ContactListener_BeginContact(lua_State *L) {
  try {
    b2ContactListener *self = *((b2ContactListener **)dub::checksdata(L, 1, "b2.b2ContactListener"));
    b2Contact *contact = *((b2Contact **)dub::checksdata(L, 2, "b2Contact"));
    self->BeginContact(contact);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "BeginContact: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "BeginContact: Unknown exception");
  }
  return dub::error(L);
}

/** virtual void b2ContactListener::EndContact(b2Contact *contact)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2WorldCallbacks.h:90
 */
static int b2ContactListener_EndContact(lua_State *L) {
  try {
    b2ContactListener *self = *((b2ContactListener **)dub::checksdata(L, 1, "b2.b2ContactListener"));
    b2Contact *contact = *((b2Contact **)dub::checksdata(L, 2, "b2Contact"));
    self->EndContact(contact);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "EndContact: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "EndContact: Unknown exception");
  }
  return dub::error(L);
}

/** virtual void b2ContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2WorldCallbacks.h:102
 */
static int b2ContactListener_PreSolve(lua_State *L) {
  try {
    b2ContactListener *self = *((b2ContactListener **)dub::checksdata(L, 1, "b2.b2ContactListener"));
    b2Contact *contact = *((b2Contact **)dub::checksdata(L, 2, "b2Contact"));
    b2Manifold *oldManifold = *((b2Manifold **)dub::checksdata(L, 3, "b2.b2Manifold"));
    self->PreSolve(contact, oldManifold);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "PreSolve: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "PreSolve: Unknown exception");
  }
  return dub::error(L);
}

/** virtual void b2ContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Dynamics/b2WorldCallbacks.h:114
 */
static int b2ContactListener_PostSolve(lua_State *L) {
  try {
    b2ContactListener *self = *((b2ContactListener **)dub::checksdata(L, 1, "b2.b2ContactListener"));
    b2Contact *contact = *((b2Contact **)dub::checksdata(L, 2, "b2Contact"));
    b2ContactImpulse *impulse = *((b2ContactImpulse **)dub::checksdata(L, 3, "b2.b2ContactImpulse"));
    self->PostSolve(contact, impulse);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "PostSolve: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "PostSolve: Unknown exception");
  }
  return dub::error(L);
}



// --=============================================== __tostring
static int b2ContactListener___tostring(lua_State *L) {
  b2ContactListener *self = *((b2ContactListener **)dub::checksdata_n(L, 1, "b2.b2ContactListener"));
  lua_pushfstring(L, "b2.b2ContactListener: %p", self);
  
  return 1;
}

// --=============================================== METHODS

static const struct luaL_Reg b2ContactListener_member_methods[] = {
  { "new"          , b2ContactListener_b2ContactListener },
  { "__gc"         , b2ContactListener__b2ContactListener },
  { "BeginContact" , b2ContactListener_BeginContact },
  { "EndContact"   , b2ContactListener_EndContact },
  { "PreSolve"     , b2ContactListener_PreSolve },
  { "PostSolve"    , b2ContactListener_PostSolve },
  { "__tostring"   , b2ContactListener___tostring },
  { "deleted"      , dub::isDeleted       },
  { NULL, NULL},
};


extern "C" int luaopen_b2_b2ContactListener(lua_State *L)
{
  // Create the metatable which will contain all the member methods
  luaL_newmetatable(L, "b2.b2ContactListener");
  // <mt>

  // register member methods
  dub::fregister(L, b2ContactListener_member_methods);
  // setup meta-table
  dub::setup(L, "b2.b2ContactListener");
  // <mt>
  return 1;
}
