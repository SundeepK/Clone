local switch = {}
switch.createSwitchBody = 1

local function createSwitchBody(box2dWorldProxy)
  local switchDef = b2BodyDef()
  switchDef.position = b2Vec2(20.0, 20.0)
  
  local switchShape = b2PolygonShape()
  switchShape:SetAsBox(2.0, 0.5)

  local switchFixture = b2FixtureDef()
  
  local switchBody = box2dWorldProxy:createNewBody(switchDef, switchShape, switchFixture)
  
  local switchShape = b2PolygonShape()
  switchShape:SetAsBox(1.5, 0.2, b2Vec2(0.0,-0.5), 0)
  
  local switchTopSensorFixture = b2FixtureDef()
  switchTopSensorFixture.density = 0
  switchTopSensorFixture.restitution = 0.0
  switchTopSensorFixture.isSensor = true
  
  local topCollisionFixture = box2dWorldProxy:addFixture(switchBody, switchShape, switchTopSensorFixture )
  return {switchid = box2dWorldProxy:UuidOf(switchBody), body = switchBody, collisionFixture = topCollisionFixture} 
end

switch.createSwitchBody = createSwitchBody

return switch

