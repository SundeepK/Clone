local switch = require("lua-scripts.levels.game-objects.switch")
local moveablePlatorm = require("lua-scripts.levels.game-objects.moveablePlatform")

--print(package.path)
local platformData = {}
local movingPlatform1Data = {}
local moveDirection = { up = 0 , down = 1 }
local collisionFixtures = {}

function init(b2worldProxy)
  clock = sf_Clock()
  box2dWorldProxy = b2worldProxy
  local switch = switch.createSwitchBody(box2dWorldProxy)
  switchBodyId = switch.switchid
  bitwise = Bitwise()
  local movingPlatform1 = moveablePlatorm.new(b2Vec2(30.0, 10.0), b2Vec2(1.0, 3.0))
  movingPlatform1Body = movingPlatform1:createBody(b2worldProxy)
  platform1Id = box2dWorldProxy:UuidOf(movingPlatform1Body)
  collisionFixtures = {switch.collisionFixture } 
--  switch.createSwitchBody() 
end

function getFixturesInterestedInCollisions()
 return collisionFixtures
end

function update()
  movePlatforms()
end


function movePlatforms()
    for k, v in pairs(movingPlatform1Data) do 
      if(v.isGoingUp)  then
          local timeTaken = clock:getElapsedTime():asMilliseconds() - v.startTime
        --timeTaken >= 500 and
          print("isGoingUp", v.nextMoveDirection)
          if (timeTaken >= 500) then  
                  print("timeTaken >= 500", v.nextMoveDirection)      
            if( timeTaken <= v.maxTime) then
                print("timeTaken <= v.maxTime", v.nextMoveDirection)
            v.body:SetLinearVelocity(v.linearVelocity)   
            else
              v.nextMoveDirection = moveDirection.down
              v.body:SetLinearVelocity(b2Vec2(0.0, 0.0))
              v.isGoingUp = false
              movingPlatform1Data[k] = nil   
            end  
         end 
    elseif(clock:getElapsedTime():asMilliseconds() - v.startTime  >= v.maxTime) then
           print("normal flow end", v.nextMoveDirection)
          v.body:SetLinearVelocity(b2Vec2(0.0, 0.0))
         movingPlatform1Data[k] = nil     
    else    
          v.body:SetLinearVelocity(v.linearVelocity)
    end
  end
end

function isBodyCollidingWith(b2ContactEdge, gameObject, count)
  if b2ContactEdge == nil then
    return count
  else
    if (bitwise:band(b2ContactEdge.other:GetFixtureList():GetFilterData().categoryBits, gameObject)  == gameObject) then
      count = count + 1 
    end
      return isBodyCollidingWith(b2ContactEdge.next, gameObject, count)
  end 
end

function handleBeginPlatform1Collision(bodyFixture)
local total = isBodyCollidingWith(bodyFixture:GetBody():GetContactList(), GameObjectTag.ROPE_BOX, 0)
      --     print("handleBeginPlatform1Collision", platformData[platform1Id].nextMoveDirection ==  moveDirection.down, movingPlatform1Data[platform1Id] == nil)

    if platformData[platform1Id] == nil then       
        platformData[platform1Id] =
         {body = movingPlatform1Body, startTime = clock:getElapsedTime():asMilliseconds(), 
        maxTime = 500, linearVelocity = b2Vec2(0.0, 10.0), nextMoveDirection = moveDirection.up, isGoingUp = false }
        movingPlatform1Data[platform1Id] = platformData[platform1Id]
    elseif platformData[platform1Id].nextMoveDirection ==  moveDirection.down and movingPlatform1Data[platform1Id] == nil then
                   print("handleBeginPlatform1Collision elseif branch", platformData[platform1Id].nextMoveDirection, movingPlatform1Data[platform1Id] == nil)
    
       platformData[platform1Id].nextMoveDirection = moveDirection.up
       platformData[platform1Id].linearVelocity = b2Vec2(0.0, 10.0)
       platformData[platform1Id].maxTime = 500
       platformData[platform1Id].startTime = clock:getElapsedTime():asMilliseconds()
       movingPlatform1Data[platform1Id] = platformData[platform1Id]
    end

end

function beginCollision(b2Contact)
  
  local bodyAFixture =  b2Contact:GetFixtureAConst()  
  local bodyBFixture =  b2Contact:GetFixtureBConst()
  
  local bodyAId = box2dWorldProxy:UuidOf(bodyAFixture:GetBody())
  local bodyBId = box2dWorldProxy:UuidOf(bodyBFixture:GetBody())
  local ropeBoxId = box2dWorldProxy:UuidOf(RopeBox) 
  
 if (bodyAId == switchBodyId) then
  if(bitwise:band(bodyBFixture:GetFilterData().categoryBits,GameObjectTag.ROPE_BOX) == GameObjectTag.ROPE_BOX) then
    handleBeginPlatform1Collision(bodyBFixture)
  end
 end 
 
  if (bodyBId == switchBodyId) then
  if(bitwise:band(bodyAFixture:GetFilterData().categoryBits,GameObjectTag.ROPE_BOX) == GameObjectTag.ROPE_BOX) then
     handleBeginPlatform1Collision(bodyAFixture)
  end
 end 
  
end

function handlePlatform1EndCollision(bodyFixture)
    local total = isBodyCollidingWith(bodyFixture:GetBody():GetContactList(), GameObjectTag.ROPE_BOX, 0)
    print(total)
    if platformData[platform1Id].nextMoveDirection == moveDirection.up and movingPlatform1Data[platform1Id] == nil then 
               print("handlePlatform1EndCollision if branch", platformData[platform1Id].nextMoveDirection, movingPlatform1Data[platform1Id] == nil)
    
        platformData[platform1Id].isGoingUp = true
        platformData[platform1Id].linearVelocity = b2Vec2(0.0, -10.0)
        platformData[platform1Id].startTime = clock:getElapsedTime():asMilliseconds()      
        platformData[platform1Id].maxTime = 1500
        movingPlatform1Data[platform1Id] = platformData[platform1Id]
    end
end

--isBodyCollidingWith(bodyAId:GetContactList(), GameObjectTag.ROPE_BOX)
--TODO if already contacting with rope box via contact list then dont do any thing
function endCollision(b2Contact)
  
  local bodyAFixture =  b2Contact:GetFixtureAConst()  
  local bodyBFixture =  b2Contact:GetFixtureBConst()
  
  local bodyAId = box2dWorldProxy:UuidOf(bodyAFixture:GetBody())
  local bodyBId = box2dWorldProxy:UuidOf(bodyBFixture:GetBody())
  local ropeBoxId = box2dWorldProxy:UuidOf(RopeBox) 

 if (bodyAId == switchBodyId) then
  if(bitwise:band(bodyBFixture:GetFilterData().categoryBits,GameObjectTag.ROPE_BOX) == GameObjectTag.ROPE_BOX) then
    handlePlatform1EndCollision(bodyBFixture)
  end
 end 
 
  if (bodyBId == switchBodyId) then
  if(bitwise:band(bodyAFixture:GetFilterData().categoryBits,GameObjectTag.ROPE_BOX) == GameObjectTag.ROPE_BOX) then
        handlePlatform1EndCollision(bodyAFixture)
  end
 end 


--  if (bodyAId == switchBodyId or bodyBId == switchBodyId) then
--    if (bodyBId == switchBodyId and (bitwise:band(bodyAFixture:GetFilterData().categoryBits,GameObjectTag.ROPE_BOX) == GameObjectTag.ROPE_BOX)) or
--     ((bodyAId == switchBodyId) and (bitwise:band(bodyBFixture:GetFilterData().categoryBits,GameObjectTag.ROPE_BOX) == GameObjectTag.ROPE_BOX)) then
--       if platformData[platform1Id] == nil then 
--                print("in end")
--         movingPlatform1Data[platform1Id] = {lastMoveTriggered = clock:getElapsedTime():asMilliseconds()}
--        platformData[platform1Id] = {body = movingPlatform1Body, startTime = clock:getElapsedTime():asMilliseconds(), maxTime = 500, linearVelocity = b2Vec2(0.0, -10.0) }
--       end
--    end  
--  end
end