local switch = require("lua-scripts.levels.game-objects.switch")
local moveablePlatorm = require("lua-scripts.levels.game-objects.moveablePlatform")

--print(package.path)
local platformData = {}

function init(b2worldProxy)
  clock = sf_Clock()
  box2dWorldProxy = b2worldProxy
  switchBodyId = switch.createSwitchBody(box2dWorldProxy)
  bitwise = Bitwise()
  local movingPlatform1 = moveablePlatorm.new(b2Vec2(30.0, 10.0), b2Vec2(1.0, 3.0))
  movingPlatform1Body = movingPlatform1:createBody(b2worldProxy)
--  switch.createSwitchBody() 
end



function update()
  movePlatforms()
end

function movePlatforms()
  for k, v in pairs(platformData) do
   if(clock:getElapsedTime():asMilliseconds() - v.startTime  >= v.maxTime) then
    v.body:SetLinearVelocity(b2Vec2(0.0, 0.0))
    platformData[k] = nil
   else
    v.body:SetLinearVelocity(v.linearVelocity)
   end
  end
end

function beginCollision(b2Contact)
  
  local bodyAFixture =  b2Contact:GetFixtureAConst()  
  local bodyBFixture =  b2Contact:GetFixtureBConst()
  
  local bodyAId = box2dWorldProxy:UuidOf(bodyAFixture:GetBody())
  local bodyBId = box2dWorldProxy:UuidOf(bodyBFixture:GetBody())
  local ropeBoxId = box2dWorldProxy:UuidOf(RopeBox) 

  if (bodyAId == switchBodyId or bodyBId == switchBodyId) then
    if (bodyBId == switchBodyId and (bitwise:band(bodyAFixture:GetFilterData().categoryBits,GameObjectTag.ROPE_BOX) == GameObjectTag.ROPE_BOX)) or
     ((bodyAId == switchBodyId) and (bitwise:band(bodyBFixture:GetFilterData().categoryBits,GameObjectTag.ROPE_BOX) == GameObjectTag.ROPE_BOX)) then
       local platformId = box2dWorldProxy:UuidOf(movingPlatform1Body)
       if platformData[platformId] == nil then
        platformData[platformId] = {body = movingPlatform1Body, startTime = clock:getElapsedTime():asMilliseconds(), maxTime = 500, linearVelocity = b2Vec2(0.0, 10.0) }
       end
    end  
  end
end


function endCollision(b2Contact)
  
  local bodyAFixture =  b2Contact:GetFixtureAConst()  
  local bodyBFixture =  b2Contact:GetFixtureBConst()
  
  local bodyAId = box2dWorldProxy:UuidOf(bodyAFixture:GetBody())
  local bodyBId = box2dWorldProxy:UuidOf(bodyBFixture:GetBody())
  local ropeBoxId = box2dWorldProxy:UuidOf(RopeBox) 

  if (bodyAId == switchBodyId or bodyBId == switchBodyId) then
    if (bodyBId == switchBodyId and (bitwise:band(bodyAFixture:GetFilterData().categoryBits,GameObjectTag.ROPE_BOX) == GameObjectTag.ROPE_BOX)) or
     ((bodyAId == switchBodyId) and (bitwise:band(bodyBFixture:GetFilterData().categoryBits,GameObjectTag.ROPE_BOX) == GameObjectTag.ROPE_BOX)) then
      print("End collision with RopeBox")
    end  
  end
end