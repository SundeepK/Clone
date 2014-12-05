/**
 *
 * MACHINE GENERATED FILE. DO NOT EDIT.
 *
 * Bindings for class b2TreeNode
 *
 * This file has been generated by dub 2.2.0.
 */
#include "dub/dub.h"
#include <Box2D/Box2D.h>


/** Set attributes (key, value)
 * 
 */
static int b2TreeNode__set_(lua_State *L) {

  b2TreeNode *self = *((b2TreeNode **)dub::checksdata_n(L, 1, "b2.b2TreeNode"));
  const char *key = luaL_checkstring(L, 2);
  int key_h = dub::hash(key, 14);
  switch(key_h) {
    case 2: {
      if (DUB_ASSERT_KEY(key, "aabb")) break;
      self->aabb = **((b2AABB **)dub::checksdata_n(L, 3, "b2.b2AABB"));
      return 0;
    }
    case 9: {
      if (DUB_ASSERT_KEY(key, "userData")) break;
      dub::protect(L, 1, 3, "userData");
      self->userData = *((void **)dub::checksdata_n(L, 3, "void"));
      return 0;
    }
    case 4: {
      if (DUB_ASSERT_KEY(key, "parent")) break;
      self->parent = luaL_checkint(L, 3);
      return 0;
    }
    case 3: {
      if (DUB_ASSERT_KEY(key, "next")) break;
      self->next = luaL_checkint(L, 3);
      return 0;
    }
    case 13: {
      if (DUB_ASSERT_KEY(key, "child1")) break;
      self->child1 = luaL_checkint(L, 3);
      return 0;
    }
    case 0: {
      if (DUB_ASSERT_KEY(key, "child2")) break;
      self->child2 = luaL_checkint(L, 3);
      return 0;
    }
    case 7: {
      if (DUB_ASSERT_KEY(key, "height")) break;
      self->height = luaL_checkint(L, 3);
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
static int b2TreeNode__get_(lua_State *L) {

  b2TreeNode *self = *((b2TreeNode **)dub::checksdata_n(L, 1, "b2.b2TreeNode", true));
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
  int key_h = dub::hash(key, 14);
  switch(key_h) {
    case 2: {
      if (DUB_ASSERT_KEY(key, "aabb")) break;
      dub::pushudata(L, &self->aabb, "b2.b2AABB", false);
      return 1;
    }
    case 9: {
      if (DUB_ASSERT_KEY(key, "userData")) break;
      void *retval__ = self->userData;
      if (!retval__) return 0;
      dub::pushudata(L, retval__, "void", false);
      return 1;
    }
    case 4: {
      if (DUB_ASSERT_KEY(key, "parent")) break;
      lua_pushnumber(L, self->parent);
      return 1;
    }
    case 3: {
      if (DUB_ASSERT_KEY(key, "next")) break;
      lua_pushnumber(L, self->next);
      return 1;
    }
    case 13: {
      if (DUB_ASSERT_KEY(key, "child1")) break;
      lua_pushnumber(L, self->child1);
      return 1;
    }
    case 0: {
      if (DUB_ASSERT_KEY(key, "child2")) break;
      lua_pushnumber(L, self->child2);
      return 1;
    }
    case 7: {
      if (DUB_ASSERT_KEY(key, "height")) break;
      lua_pushnumber(L, self->height);
      return 1;
    }
  }
  return 0;
}

/** b2TreeNode()
 * 
 */
static int b2TreeNode_b2TreeNode(lua_State *L) {
  try {
    b2TreeNode *retval__ = new b2TreeNode();
    dub::pushudata(L, retval__, "b2.b2TreeNode", true);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "new: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "new: Unknown exception");
  }
  return dub::error(L);
}

/** bool b2TreeNode::IsLeaf() const
 * /media/sundeep/3 tb Vol/code/Clone-game-repo/Clone-game/vendor/Box2D/Box2D/Collision/b2DynamicTree.h:30
 */
static int b2TreeNode_IsLeaf(lua_State *L) {
  try {
    b2TreeNode *self = *((b2TreeNode **)dub::checksdata(L, 1, "b2.b2TreeNode"));
    lua_pushboolean(L, self->IsLeaf());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "IsLeaf: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "IsLeaf: Unknown exception");
  }
  return dub::error(L);
}



// --=============================================== __tostring
static int b2TreeNode___tostring(lua_State *L) {
  b2TreeNode *self = *((b2TreeNode **)dub::checksdata_n(L, 1, "b2.b2TreeNode"));
  lua_pushfstring(L, "b2.b2TreeNode: %p", self);
  
  return 1;
}

// --=============================================== METHODS

static const struct luaL_Reg b2TreeNode_member_methods[] = {
  { "__newindex"   , b2TreeNode__set_     },
  { "__index"      , b2TreeNode__get_     },
  { "new"          , b2TreeNode_b2TreeNode },
  { "IsLeaf"       , b2TreeNode_IsLeaf    },
  { "__tostring"   , b2TreeNode___tostring },
  { "deleted"      , dub::isDeleted       },
  { NULL, NULL},
};


extern "C" int luaopen_b2_b2TreeNode(lua_State *L)
{
  // Create the metatable which will contain all the member methods
  luaL_newmetatable(L, "b2.b2TreeNode");
  // <mt>

  // register member methods
  dub::fregister(L, b2TreeNode_member_methods);
  // setup meta-table
  dub::setup(L, "b2.b2TreeNode");
  // <mt>
  return 1;
}