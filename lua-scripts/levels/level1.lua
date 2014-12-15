
function init(b2worldProxy)

  box2dWorldProxy = b2worldProxy
  createSwitchBody1() 
end

function createSwitchBody1()
  local switchDef = b2BodyDef()
  switchDef.position = b2Vec2(20.0, 20.0)
  
  local switchShape = b2PolygonShape()
  switchShape:SetAsBox(2.0, 0.5)

  local switchFixture = b2FixtureDef()
  
  local switchBody = box2dWorldProxy:createNewBody(switchDef, switchShape, switchFixture)
  
  local switchShape = b2PolygonShape()
  switchShape:SetAsBox(1.5, 0.2, b2Vec2(0.0,-0.5), 0)
  
  local switchTopSensorFixture = b2FixtureDef()
  switchTopSensorFixture.density = 0.3
  switchTopSensorFixture.restitution = 0.0
  switchTopSensorFixture.isSensor = true
  
  box2dWorldProxy:addFixture(switchBody, switchShape, switchTopSensorFixture )
  switchBodyId = box2dWorldProxy:UuidOf(switchBody)
 
end

function update()
end

function beginCollision(b2Contact)
  
  local bodyAFixture =  b2Contact:GetFixtureAConst()  
  local bodyBFixture =  b2Contact:GetFixtureBConst()
  
  local bodyAId = box2dWorldProxy:UuidOf(bodyAFixture:GetBody())
  local bodyBId = box2dWorldProxy:UuidOf(bodyBFixture:GetBody())
  local ropeBoxId = box2dWorldProxy:UuidOf(RopeBox) 
 
  if (bodyAId == switchBodyId or bodyBId == switchBodyId) then
    if((bodyAId == switchBodyId) and (bodyBId == ropeBoxId) or (bodyAId == ropeBoxId) and (bodyBId == switchBodyId) ) then
        print("RopeBox colliding with switch")
    end
  end
  
end


function endCollision(b2Contact)

end