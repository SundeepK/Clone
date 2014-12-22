local switch = require("lua-scripts.levels.game-objects.switch")
local moveablePlatorm = require("lua-scripts.levels.game-objects.moveablePlatform")

--print(package.path)
local platformData = {}
local movingPlatform1Data = {}
local moveDirection = { up = 0 , down = 1 }
local collisionFixtures = {}
local totalMass = 0;

function init(b2worldProxy)
  clock = sf_Clock()
  box2dWorldProxy = b2worldProxy
  switch1 = switch.createSwitchBody(box2dWorldProxy)
  switchBodyId = switch1.switchid
  bitwise = Bitwise()
  local movingPlatform1 = moveablePlatorm.new(b2Vec2(30.0, 10.0), b2Vec2(1.0, 3.0))
  movingPlatform1Body = movingPlatform1:createBody(b2worldProxy)
  platform1Id = box2dWorldProxy:UuidOf(movingPlatform1Body)
  collisionFixtures = {switch1.collisionFixture } 
  platformData[platform1Id] =
         {body = movingPlatform1Body, startTime = clock:getElapsedTime():asMilliseconds(), 
        maxTime = 500, linearVelocity = b2Vec2(0.0, 10.0)}
        canMoveDown = true
--  switch.createSwitchBody() 
end

function getFixturesInterestedInCollisions()
 return collisionFixtures
end

function isBodyCollidingWith(b2ContactEdge, gameObject, count)
  if b2ContactEdge == nil then
    return count
  else
    if (bitwise:band(b2ContactEdge.other:GetFixtureList():GetFilterData().categoryBits, gameObject)  == gameObject) then
      print("bits", bitwise:band(b2ContactEdge.other:GetFixtureList():GetFilterData().categoryBits, gameObject))
      count = count + 1 
    end
      return isBodyCollidingWith(b2ContactEdge.next, gameObject, count)
  end 
end

function update() 
 print(totalMass)
  --movePlatforms()
end

function updateCollisions()
 local v = switch1.body:GetContactList()
  local total = isBodyCollidingWith(switch1.body:GetContactList(), GameObjectTag.SWITCH, 0)
  print("inside isBodyCollidingWith", total, canMoveDown)
  if(total >=1 and canMoveDown) then
       platformData[platform1Id].linearVelocity = b2Vec2(0.0, 10.0)
       platformData[platform1Id].maxTime = 500
       platformData[platform1Id].startTime = clock:getElapsedTime():asMilliseconds()
       movingPlatform1Data[platform1Id] = platformData[platform1Id]
       canMoveDown = false
  elseif (total == 0 and canMoveDown == false) then
        platformData[platform1Id].linearVelocity = b2Vec2(0.0, -10.0)
        platformData[platform1Id].startTime = clock:getElapsedTime():asMilliseconds()      
        platformData[platform1Id].maxTime = 500
        movingPlatform1Data[platform1Id] = platformData[platform1Id]
       canMoveDown = true
  end
end


function movePlatforms()
    for k, v in pairs(movingPlatform1Data) do 
    if(clock:getElapsedTime():asMilliseconds() - v.startTime  >= v.maxTime) then
         v.body:SetLinearVelocity(b2Vec2(0.0, 0.0))
         movingPlatform1Data[k] = nil     
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
  print(bodyAFixture:GetBody():GetMass())
  if (bodyAId == switchBodyId or bodyBId == switchBodyId) then
    if (bodyBId == switchBodyId and (bitwise:band(bodyAFixture:GetFilterData().categoryBits,GameObjectTag.ROPE_BOX) == GameObjectTag.ROPE_BOX)) then
      totalMass = totalMass + bodyAFixture:GetBody():GetMass()
    elseif ((bodyAId == switchBodyId) and (bitwise:band(bodyBFixture:GetFilterData().categoryBits,GameObjectTag.ROPE_BOX) == GameObjectTag.ROPE_BOX)) then
      totalMass = totalMass + bodyBFixture:GetBody():GetMass()
    end
  end
end


--isBodyCollidingWith(bodyAId:GetContactList(), GameObjectTag.ROPE_BOX)
--TODO if already contacting with rope box via contact list then dont do any thing
function endCollision(b2Contact)
   local bodyAFixture =  b2Contact:GetFixtureAConst()  
  local bodyBFixture =  b2Contact:GetFixtureBConst()
  
  local bodyAId = box2dWorldProxy:UuidOf(bodyAFixture:GetBody())
  local bodyBId = box2dWorldProxy:UuidOf(bodyBFixture:GetBody())


  if (bodyAId == switchBodyId or bodyBId == switchBodyId) then
    if (bodyBId == switchBodyId and (bitwise:band(bodyAFixture:GetFilterData().categoryBits,GameObjectTag.ROPE_BOX) == GameObjectTag.ROPE_BOX)) then
      totalMass = totalMass - bodyAFixture:GetBody():GetMass()
    elseif ((bodyAId == switchBodyId) and (bitwise:band(bodyBFixture:GetFilterData().categoryBits,GameObjectTag.ROPE_BOX) == GameObjectTag.ROPE_BOX)) then
      totalMass = totalMass - bodyBFixture:GetBody():GetMass()
    end
  end
end

