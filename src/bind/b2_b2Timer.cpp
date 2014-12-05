/**
 *
 * MACHINE GENERATED FILE. DO NOT EDIT.
 *
 * Bindings for class b2Timer
 *
 * This file has been generated by dub 2.2.0.
 */
#include "dub/dub.h"
#include <Box2D/Box2D.h>


/** ~b2Timer()
 * 
 */
static int b2Timer__b2Timer(lua_State *L) {
  try {
    DubUserdata *userdata = ((DubUserdata*)dub::checksdata_d(L, 1, "b2.b2Timer"));
    if (userdata->gc) {
      b2Timer *self = (b2Timer *)userdata->ptr;
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

/** b2Timer::b2Timer()
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Common/b2Timer.h:31
 */
static int b2Timer_b2Timer(lua_State *L) {
  try {
    b2Timer *retval__ = new b2Timer();
    dub::pushudata(L, retval__, "b2.b2Timer", true);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "new: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "new: Unknown exception");
  }
  return dub::error(L);
}

/** void b2Timer::Reset()
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Common/b2Timer.h:34
 */
static int b2Timer_Reset(lua_State *L) {
  try {
    b2Timer *self = *((b2Timer **)dub::checksdata(L, 1, "b2.b2Timer"));
    self->Reset();
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "Reset: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "Reset: Unknown exception");
  }
  return dub::error(L);
}

/** float32 b2Timer::GetMilliseconds() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Common/b2Timer.h:37
 */
static int b2Timer_GetMilliseconds(lua_State *L) {
  try {
    b2Timer *self = *((b2Timer **)dub::checksdata(L, 1, "b2.b2Timer"));
    lua_pushnumber(L, self->GetMilliseconds());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetMilliseconds: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetMilliseconds: Unknown exception");
  }
  return dub::error(L);
}



// --=============================================== __tostring
static int b2Timer___tostring(lua_State *L) {
  b2Timer *self = *((b2Timer **)dub::checksdata_n(L, 1, "b2.b2Timer"));
  lua_pushfstring(L, "b2.b2Timer: %p", self);
  
  return 1;
}

// --=============================================== METHODS

static const struct luaL_Reg b2Timer_member_methods[] = {
  { "__gc"         , b2Timer__b2Timer     },
  { "new"          , b2Timer_b2Timer      },
  { "Reset"        , b2Timer_Reset        },
  { "GetMilliseconds", b2Timer_GetMilliseconds },
  { "__tostring"   , b2Timer___tostring   },
  { "deleted"      , dub::isDeleted       },
  { NULL, NULL},
};


extern "C" int luaopen_b2_b2Timer(lua_State *L)
{
  // Create the metatable which will contain all the member methods
  luaL_newmetatable(L, "b2.b2Timer");
  // <mt>

  // register member methods
  dub::fregister(L, b2Timer_member_methods);
  // setup meta-table
  dub::setup(L, "b2.b2Timer");
  // <mt>
  return 1;
}