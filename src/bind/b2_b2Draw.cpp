/**
 *
 * MACHINE GENERATED FILE. DO NOT EDIT.
 *
 * Bindings for class b2Draw
 *
 * This file has been generated by dub 2.2.0.
 */
#include "dub/dub.h"
#include <Box2D/Box2D.h>


/** virtual b2Draw::~b2Draw()
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Common/b2Draw.h:40
 */
static int b2Draw__b2Draw(lua_State *L) {
  try {
    DubUserdata *userdata = ((DubUserdata*)dub::checksdata_d(L, 1, "b2.b2Draw"));
    if (userdata->gc) {
      b2Draw *self = (b2Draw *)userdata->ptr;
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

/** void b2Draw::SetFlags(uint32 flags)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Common/b2Draw.h:52
 */
static int b2Draw_SetFlags(lua_State *L) {
  try {
    b2Draw *self = *((b2Draw **)dub::checksdata(L, 1, "b2.b2Draw"));
    uint32 flags = dub::checkint(L, 2);
    self->SetFlags(flags);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "SetFlags: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "SetFlags: Unknown exception");
  }
  return dub::error(L);
}

/** uint32 b2Draw::GetFlags() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Common/b2Draw.h:55
 */
static int b2Draw_GetFlags(lua_State *L) {
  try {
    b2Draw *self = *((b2Draw **)dub::checksdata(L, 1, "b2.b2Draw"));
    lua_pushnumber(L, self->GetFlags());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "GetFlags: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "GetFlags: Unknown exception");
  }
  return dub::error(L);
}

/** void b2Draw::AppendFlags(uint32 flags)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Common/b2Draw.h:58
 */
static int b2Draw_AppendFlags(lua_State *L) {
  try {
    b2Draw *self = *((b2Draw **)dub::checksdata(L, 1, "b2.b2Draw"));
    uint32 flags = dub::checkint(L, 2);
    self->AppendFlags(flags);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "AppendFlags: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "AppendFlags: Unknown exception");
  }
  return dub::error(L);
}

/** void b2Draw::ClearFlags(uint32 flags)
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Common/b2Draw.h:61
 */
static int b2Draw_ClearFlags(lua_State *L) {
  try {
    b2Draw *self = *((b2Draw **)dub::checksdata(L, 1, "b2.b2Draw"));
    uint32 flags = dub::checkint(L, 2);
    self->ClearFlags(flags);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "ClearFlags: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "ClearFlags: Unknown exception");
  }
  return dub::error(L);
}

/** virtual void b2Draw::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color)=0
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Common/b2Draw.h:64
 */
static int b2Draw_DrawPolygon(lua_State *L) {
  try {
    b2Draw *self = *((b2Draw **)dub::checksdata(L, 1, "b2.b2Draw"));
    b2Vec2 *vertices = *((b2Vec2 **)dub::checksdata(L, 2, "b2.b2Vec2"));
    int32 vertexCount = dub::checkint(L, 3);
    b2Color *color = *((b2Color **)dub::checksdata(L, 4, "b2.b2Color"));
    self->DrawPolygon(vertices, vertexCount, *color);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "DrawPolygon: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "DrawPolygon: Unknown exception");
  }
  return dub::error(L);
}

/** virtual void b2Draw::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color)=0
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Common/b2Draw.h:67
 */
static int b2Draw_DrawSolidPolygon(lua_State *L) {
  try {
    b2Draw *self = *((b2Draw **)dub::checksdata(L, 1, "b2.b2Draw"));
    b2Vec2 *vertices = *((b2Vec2 **)dub::checksdata(L, 2, "b2.b2Vec2"));
    int32 vertexCount = dub::checkint(L, 3);
    b2Color *color = *((b2Color **)dub::checksdata(L, 4, "b2.b2Color"));
    self->DrawSolidPolygon(vertices, vertexCount, *color);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "DrawSolidPolygon: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "DrawSolidPolygon: Unknown exception");
  }
  return dub::error(L);
}

/** virtual void b2Draw::DrawCircle(const b2Vec2 &center, float32 radius, const b2Color &color)=0
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Common/b2Draw.h:70
 */
static int b2Draw_DrawCircle(lua_State *L) {
  try {
    b2Draw *self = *((b2Draw **)dub::checksdata(L, 1, "b2.b2Draw"));
    b2Vec2 *center = *((b2Vec2 **)dub::checksdata(L, 2, "b2.b2Vec2"));
    float32 radius = dub::checknumber(L, 3);
    b2Color *color = *((b2Color **)dub::checksdata(L, 4, "b2.b2Color"));
    self->DrawCircle(*center, radius, *color);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "DrawCircle: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "DrawCircle: Unknown exception");
  }
  return dub::error(L);
}

/** virtual void b2Draw::DrawSolidCircle(const b2Vec2 &center, float32 radius, const b2Vec2 &axis, const b2Color &color)=0
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Common/b2Draw.h:73
 */
static int b2Draw_DrawSolidCircle(lua_State *L) {
  try {
    b2Draw *self = *((b2Draw **)dub::checksdata(L, 1, "b2.b2Draw"));
    b2Vec2 *center = *((b2Vec2 **)dub::checksdata(L, 2, "b2.b2Vec2"));
    float32 radius = dub::checknumber(L, 3);
    b2Vec2 *axis = *((b2Vec2 **)dub::checksdata(L, 4, "b2.b2Vec2"));
    b2Color *color = *((b2Color **)dub::checksdata(L, 5, "b2.b2Color"));
    self->DrawSolidCircle(*center, radius, *axis, *color);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "DrawSolidCircle: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "DrawSolidCircle: Unknown exception");
  }
  return dub::error(L);
}

/** virtual void b2Draw::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color)=0
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Common/b2Draw.h:76
 */
static int b2Draw_DrawSegment(lua_State *L) {
  try {
    b2Draw *self = *((b2Draw **)dub::checksdata(L, 1, "b2.b2Draw"));
    b2Vec2 *p1 = *((b2Vec2 **)dub::checksdata(L, 2, "b2.b2Vec2"));
    b2Vec2 *p2 = *((b2Vec2 **)dub::checksdata(L, 3, "b2.b2Vec2"));
    b2Color *color = *((b2Color **)dub::checksdata(L, 4, "b2.b2Color"));
    self->DrawSegment(*p1, *p2, *color);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "DrawSegment: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "DrawSegment: Unknown exception");
  }
  return dub::error(L);
}

/** virtual void b2Draw::DrawTransform(const b2Transform &xf)=0
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Common/b2Draw.h:80
 */
static int b2Draw_DrawTransform(lua_State *L) {
  try {
    b2Draw *self = *((b2Draw **)dub::checksdata(L, 1, "b2.b2Draw"));
    b2Transform *xf = *((b2Transform **)dub::checksdata(L, 2, "b2.b2Transform"));
    self->DrawTransform(*xf);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "DrawTransform: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "DrawTransform: Unknown exception");
  }
  return dub::error(L);
}



// --=============================================== __tostring
static int b2Draw___tostring(lua_State *L) {
  b2Draw *self = *((b2Draw **)dub::checksdata_n(L, 1, "b2.b2Draw"));
  lua_pushfstring(L, "b2.b2Draw: %p", self);
  
  return 1;
}

// --=============================================== METHODS

static const struct luaL_Reg b2Draw_member_methods[] = {
  { "__gc"         , b2Draw__b2Draw       },
  { "SetFlags"     , b2Draw_SetFlags      },
  { "GetFlags"     , b2Draw_GetFlags      },
  { "AppendFlags"  , b2Draw_AppendFlags   },
  { "ClearFlags"   , b2Draw_ClearFlags    },
  { "DrawPolygon"  , b2Draw_DrawPolygon   },
  { "DrawSolidPolygon", b2Draw_DrawSolidPolygon },
  { "DrawCircle"   , b2Draw_DrawCircle    },
  { "DrawSolidCircle", b2Draw_DrawSolidCircle },
  { "DrawSegment"  , b2Draw_DrawSegment   },
  { "DrawTransform", b2Draw_DrawTransform },
  { "__tostring"   , b2Draw___tostring    },
  { "deleted"      , dub::isDeleted       },
  { NULL, NULL},
};

// --=============================================== CONSTANTS
static const struct dub::const_Reg b2Draw_const[] = {
  { "e_shapeBit"   , b2Draw::e_shapeBit   },
  { "e_jointBit"   , b2Draw::e_jointBit   },
  { "e_aabbBit"    , b2Draw::e_aabbBit    },
  { "e_pairBit"    , b2Draw::e_pairBit    },
  { "e_centerOfMassBit", b2Draw::e_centerOfMassBit },
  { NULL, 0},
};

extern "C" int luaopen_b2_b2Draw(lua_State *L)
{
  // Create the metatable which will contain all the member methods
  luaL_newmetatable(L, "b2.b2Draw");
  // <mt>
  // register class constants
  dub::register_const(L, b2Draw_const);

  // register member methods
  dub::fregister(L, b2Draw_member_methods);
  // setup meta-table
  dub::setup(L, "b2.b2Draw");
  // <mt>
  return 1;
}
