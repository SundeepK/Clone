local moveableBody = {}
moveableBody.__index = moveableBody 

local function new(position,shape)
  return setmetatable({ position = position or b2Vec2(0.0, 0.0), shape = shape or b2Vec2(1.0, 1.0)}, moveableBody)
end

function moveableBody:createBody(box2dWorldProxy)
  print(self.position.x)
  local moveableBodyDef = b2BodyDef()
  moveableBodyDef.position = self.position
  moveableBodyDef.type = b2BodyType.b2_kinematicBody
   moveableBodyDef.density=1.0;
  moveableBodyDef.restitution=1.0
  local moveableBodyShape = b2PolygonShape()
  moveableBodyShape:SetAsBox(self.shape.x, self.shape.y)
  local moveableBodyFixture = b2FixtureDef()
  local switchBody = box2dWorldProxy:createNewBody(moveableBodyDef, moveableBodyShape, moveableBodyFixture)
  return switchBody
end

return setmetatable({new = new}, {__call = function(_, ...) return new(...) end})