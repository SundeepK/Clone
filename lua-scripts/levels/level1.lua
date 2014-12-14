
function init(b2worldProxy)

  box2dWorldProxy = b2worldProxy
  
  local switchDef = b2BodyDef()
  switchDef.position = b2Vec2(20.0, 20.0)
  
  local switchShape = b2PolygonShape()
  switchShape:SetAsBox(2.0, 0.5)

  local switchFixture = b2FixtureDef()
  
  local switchBody = box2dWorldProxy:createNewBody(switchDef, switchShape, switchFixture)  
  switchBodyId = box2dWorldProxy:UuidOf(switchBody)
    
end

function update()
end

function beginCollision(b2Contact)
  
  local bodyAFixture =  b2Contact:GetFixtureAConst()  
  local bodyBFixture =  b2Contact:GetFixtureBConst()
  
  if (box2dWorldProxy:UuidOf(bodyAFixture:GetBody()) == switchBodyId or box2dWorldProxy:UuidOf(bodyBFixture:GetBody()) == switchBodyId ) then
    print("colision with switch")
  end
  
end


function endCollision(b2Contact)

end