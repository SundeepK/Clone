local switch = require("lua-scripts.levels.game-objects.switch")
--print(package.path)

function init(b2worldProxy)

  box2dWorldProxy = b2worldProxy
  switchBodyId = switch.createSwitchBody(box2dWorldProxy)
  
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
 
  if (bodyAId == switchBodyId or bodyBId == switchBodyId) then
    if((bodyAId == switchBodyId) and (bodyBId == ropeBoxId) or (bodyAId == ropeBoxId) and (bodyBId == switchBodyId) ) then
        print("RopeBox colliding with switch")
    end
  end
  
end


function endCollision(b2Contact)

end