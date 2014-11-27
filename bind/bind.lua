local lub = require 'lub'
local dub = require 'dub'

local ins = dub.Inspector {
  INPUT   = {
      '../vendor/Box2D/Box2D/Common',
      '../vendor/Box2D/Box2D/Collision',
      '../vendor/Box2D/Box2D/Collision/Shapes',
     '../vendor/Box2D/Box2D/Dynamics',
      '../vendor/Box2D/Box2D/Dynamics/Joints',
     '../vendor/Box2D/Box2D/Rope',
  },
}

local binder = dub.LuaBinder()

binder:bind(ins, {
  output_directory =  '../src/bind',

  header_base =  '../vendor/Box2D/Box2D/',
  -- Execute all lua_open in a single go
  -- with luaopen_b2_vendor (creates b2_vendor.cpp).
  single_lib = 'b2',
  -- Other name so that we can first load b2.lua
  luaopen = 'b2_vendor',
})
