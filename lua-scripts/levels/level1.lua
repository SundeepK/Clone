local switch = require("lua-scripts.levels.game-objects.switch")
--print(package.path)

function init(b2worldProxy)

  box2dWorldProxy = b2worldProxy
  switchBodyId = switch.createSwitchBody(box2dWorldProxy)
  bitwise = Bitwise()
  
--  switch.createSwitchBody() 
end



function update()
end

function beginCollision(b2Contact)
  
  local bodyAFixture =  b2Contact:GetFixtureAConst()  
  local bodyBFixture =  b2Contact:GetFixtureBConst()
  
  local bodyAId = box2dWorldProxy:UuidOf(bodyAFixture:GetBody())
  local bodyBId = box2dWorldProxy:UuidOf(bodyBFixture:GetBody())
  local ropeBoxId = box2dWorldProxy:UuidOf(RopeBox) 
  
  print((bitwise:band(bodyAFixture:GetFilterData().categoryBits,GameObjectTag.ROPE_BOX) == GameObjectTag.ROPE_BOX))
  
  if (bodyAId == switchBodyId or bodyBId == switchBodyId) then
          print("in if condition")
    local isswitchAAndBRope = (bodyAId == switchBodyId) and (bitwise:band(bodyAFixture:GetFilterData().categoryBits,GameObjectTag.ROPE_BOX) == GameObjectTag.ROPE_BOX)
    local isswitchBAndARope = (bodyBId == switchBodyId) and (bitwise:band(bodyBFixture:GetFilterData().categoryBits,GameObjectTag.ROPE_BOX) == GameObjectTag.ROPE_BOX) 
    
    if(isswitchBAndARope  ) then
        print("RopeBox colliding with switch")
    end
  end
  
end


function endCollision(b2Contact)

end