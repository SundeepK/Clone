local moveablePlatorm = require("lua-scripts.levels.game-objects.moveablePlatform")
local prismaticButton = require("lua-scripts.levels.game-objects.prismaticButton")

local collisionFixtures = {}

local loadMapObjectFunctions = {}

function init(b2worldProxy) 
  clock = sf_Clock()
  box2dWorldProxy = b2worldProxy

  local prismaticOptions =   {
    groundPosition = b2Vec2(20.0, 20.0),
    buttonPosition = b2Vec2(20.0, 17.0),
    shape = b2Vec2(1.0, 0.5),
    motorSpeed = 2.0
  }
  prismaticButton1 = prismaticButton.createPrismaticButton(box2dWorldProxy, prismaticOptions)
  lastTranslation =  prismaticButton1.joint:GetJointTranslation()
  
  loadMapObjectFunctions["MovingPlatform1"] = { func = loadMovingPlatform}
end

function loadMapObject(objectName, mapObject) 
  if loadMapObjectFunctions[objectName] then
    loadMapObjectFunctions[objectName].func(mapObject)
  end
end

function loadMovingPlatform(mapObject)
  local position = mapObject:GetPosition()
  position.x = position.x / 30
   position.y = position.y / 30
  local pbody = box2dWorldProxy:createBodyFromMapObject(mapObject, b2BodyType.b2_kinematicBody)
  verticalMovingPlatform1 = {body = pbody, originalPosition = position}
end

function getFixturesInterestedInCollisions()
  return collisionFixtures
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


function update()
  movePlatform()
end

function movePlatform()
  translation = math.abs(prismaticButton1.joint:GetJointTranslation())
  local direction = -1
  if(translation > lastTranslation) then
    direction = 1
  end
  lastTranslation = translation
  local movingPlatform1Body = verticalMovingPlatform1.body
  local originalMovingPlatform1Position = verticalMovingPlatform1.originalPosition
  print("current position", movingPlatform1Body:GetPosition().y, originalMovingPlatform1Position.y)
   if(translation >= 0.1 and movingPlatform1Body:GetPosition().y < originalMovingPlatform1Position.y) then
        movingPlatform1Body:SetLinearVelocity(b2Vec2(0, 4))
   elseif(translation <= 2 and movingPlatform1Body:GetPosition().y > (originalMovingPlatform1Position.y + 5)) then
        movingPlatform1Body:SetLinearVelocity(b2Vec2(0, -4))
   else
      movingPlatform1Body:SetLinearVelocity(b2Vec2(0, 0))
   end
end

function beginCollision(b2Contact)

end

function endCollision(b2Contact)

end


