
function init(b2worldProxy)

  box2dWorldProxy = b2worldProxy
  
  local switchDef = b2BodyDef()
  switchDef.position = b2Vec2(20.0, 20.0)
  
  local switchShape = b2PolygonShape()
  switchShape:SetAsBox(2.0, 0.5)

  local switchFixture = b2FixtureDef()
  
  switchBody = box2dWorldProxy:createNewBody(switchDef, switchShape, switchFixture)  
    
end

function update()
end

function beginCollision(b2Contact)
  
   bodyA =  b2Contact:GetFixtureAConst()
   b = bodyA:GetBody()
  print(b:GetAngle())
  
end


function endCollision(b2Contact)

end