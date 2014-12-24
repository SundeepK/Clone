local switch = require("lua-scripts.levels.game-objects.switch")
local moveablePlatorm = require("lua-scripts.levels.game-objects.moveablePlatform")
local prismaticButton = require("lua-scripts.levels.game-objects.prismaticButton")

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
        
  --prismaticButon = prismaticButton.createPrismaticButton(box2dWorldProxy)
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


function addUpAllMass(b2ContactEdge, gameObject, mass)
  if b2ContactEdge == nil then
    return mass
  else
    if (bitwise:band(b2ContactEdge.other:GetFixtureList():GetFilterData().categoryBits, gameObject)  == gameObject) then
      mass = mass + b2ContactEdge.other:GetMass()
    end
      return addUpAllMass(b2ContactEdge.next, gameObject, mass)
  end 
end


--function addUpAllMassOfAll(b2ContactEdge, gameObject, foundBodies)
--  if b2ContactEdge == nil then
--    return foundBodies
--  else
--    local edge = b2ContactEdge
--    while(edge ~= nil) do
--      if (bitwise:band(edge.other:GetFixtureList():GetFilterData().categoryBits, gameObject)  == gameObject) then
--        foundBodies[box2dWorldProxy:UuidOf(b2ContactEdge.other)] = edge.other:GetMass()
--      end      
--       edge = edge.next
--    end
--    local anotherEdge = b2ContactEdge.other:GetContactList()
--    while (anotherEdge ~= nil) do
--        if(foundBodies[box2dWorldProxy:UuidOf(anotherEdge.other)] == nil) then
--        return addUpAllMassOfAll(anotherEdge.other:GetContactList(), gameObject, foundBodies)
--        end
--        anotherEdge = anotherEdge.next
--    end
--  end
--end

function addUpAllMassOfAll(b2ContactEdge, gameObject, foundBodies)
  if b2ContactEdge == nil then
    return foundBodies
  end
  local edge = b2ContactEdge
  while(edge ~= nil) do
    if (bitwise:band(edge.other:GetFixtureList():GetFilterData().categoryBits, gameObject)  == gameObject and foundBodies[box2dWorldProxy:UuidOf(edge.other)] == nil) then
      foundBodies[box2dWorldProxy:UuidOf(edge.other)] = edge.other:GetMass()
      print("going in")
      return addUpAllMassOfAll(edge.other:GetContactList(),gameObject, foundBodies)
    end
    edge = edge.next
  end
end

function addUpMass(body)
  local edge = body:GetContactList()
  if (edge == nil) then
    return 0
  end

  local total = edge.other:GetMass()
  local foundBodies = {}
  while(edge ~= nil) do
   addUpAllMassOfAll(edge.other:GetContactList(),GameObjectTag.ROPE_BOX,foundBodies)
   edge = edge.next
  end
  for k, v in pairs(movingPlatform1Data) do 
    total = total + v
  end
  return total
end


function update() 
    -- totalMass = addUpMass(switch1.body)

--    local Mass = addUpAllMass(switch1.body:GetContactList(), bodyAFixture:GetFilterData().categoryBits,GameObjectTag.ROPE_BOX, 0)
--    print(Mass)
 --print(totalMass)
  --movePlatforms()
end

function beginCollision(b2Contact)
  
  local bodyAFixture =  b2Contact:GetFixtureAConst()  
  local bodyBFixture =  b2Contact:GetFixtureBConst()
  
  local bodyAId = box2dWorldProxy:UuidOf(bodyAFixture:GetBody())
  local bodyBId = box2dWorldProxy:UuidOf(bodyBFixture:GetBody())
  
  if (bodyAId == switchBodyId or bodyBId == switchBodyId) then
    if (bodyBId == switchBodyId and (bitwise:band(bodyAFixture:GetFilterData().categoryBits,GameObjectTag.ROPE_BOX) == GameObjectTag.ROPE_BOX)) then
      print("mass A", bodyAFixture:GetBody():GetMass())
         -- print("mass to add", addUpAllMass(switch1.body:GetContactList(),GameObjectTag.ROPE_BOX,bodyAFixture:GetBody():GetMass()))
--      totalMass = addUpAllMass(switch1.body:GetContactList(), GameObjectTag.ROPE_BOX, 0)
        totalMass = addUpMass(switch1.body)

    elseif ((bodyAId == switchBodyId) and (bitwise:band(bodyBFixture:GetFilterData().categoryBits,GameObjectTag.ROPE_BOX) == GameObjectTag.ROPE_BOX)) then
          print("mass A", bodyBFixture:GetBody():GetMass())
    
          --    print("mass to add", addUpAllMass(bodyAFixture:GetBody():GetContactList(),GameObjectTag.ROPE_BOX,bodyAFixture:GetBody():GetMass()))
--      totalMass = addUpAllMass(switch1.body:GetContactList(), GameObjectTag.ROPE_BOX, 0)
        totalMass = addUpMass(switch1.body)
    end
  end
  print("total mass", totalMass)
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
    
    elseif ((bodyAId == switchBodyId) and (bitwise:band(bodyBFixture:GetFilterData().categoryBits,GameObjectTag.ROPE_BOX) == GameObjectTag.ROPE_BOX)) then
    
    end
  end
end


--b2Body* ground = NULL;
--    {
--      b2BodyDef bd;
--      ground = m_world->CreateBody(&bd);
--
--      b2EdgeShape shape;
--      shape.Set(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
--      ground->CreateFixture(&shape, 0.0f);
--    }
--
--    {
--      b2PolygonShape shape;
--      shape.SetAsBox(2.0f, 0.5f);
--
--      b2BodyDef bd;
--      bd.type = b2_dynamicBody;
--      bd.allowSleep = false;
--      b2Body* body = m_world->CreateBody(&bd);
--      body->CreateFixture(&shape, 5.0f);
--
--      shape.SetAsBox(5.0f, 5.0f);
--      bd.position.Set(0.0f, 10.0f);
--      b2Body* body2 = m_world->CreateBody(&bd);
--      body2->CreateFixture(&shape, 5.0f);
--
--      b2PrismaticJointDef pjd;
--
--      // Bouncy limit
--      b2Vec2 axis(0.0f, 1.0f);
--      axis.Normalize();
--      pjd.Initialize(ground, body, b2Vec2(0.0f, 0.0f), axis);
--
--      // Non-bouncy limit
--      //pjd.Initialize(ground, body, b2Vec2(-10.0f, 10.0f), b2Vec2(1.0f, 0.0f));
--
--      pjd.motorSpeed = 10.0f;
--      pjd.maxMotorForce = 1000.0f;
--      pjd.enableMotor = true;
--      pjd.lowerTranslation = 0.0f;
--      pjd.upperTranslation = 20.0f;
--      pjd.enableLimit = true;
--
--      m_joint = (b2PrismaticJoint*)m_world->CreateJoint(&pjd);
--    }

