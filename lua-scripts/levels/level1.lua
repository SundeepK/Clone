local moveablePlatorm = require("lua-scripts.levels.game-objects.moveablePlatform")
local prismaticButton = require("lua-scripts.levels.game-objects.prismaticButton")

local platformData = {}
local collisionFixtures = {}

function init(b2worldProxy)
  clock = sf_Clock()
  box2dWorldProxy = b2worldProxy
  local movingPlatform1 = moveablePlatorm.new(b2Vec2(30.0, 10.0), b2Vec2(1.0, 3.0))
  movingPlatform1Body = movingPlatform1:createBody(b2worldProxy)
  platform1Id = box2dWorldProxy:UuidOf(movingPlatform1Body)
  platformData[platform1Id] =
    {body = movingPlatform1Body, startTime = clock:getElapsedTime():asMilliseconds(),
      maxTime = 500, linearVelocity = b2Vec2(0.0, 10.0)}

  local prismaticOptions =   {
    groundPosition = b2Vec2(20.0, 20.0),
    buttonPosition = b2Vec2(20.0, 17.0),
    shape = b2Vec2(1.0, 0.5),
    motorSpeed = 2.0
  }
  prismaticButton1 = prismaticButton.createPrismaticButton(box2dWorldProxy, prismaticOptions)
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
  print(prismaticButton1.joint:GetJointTranslation())
end

function beginCollision(b2Contact)

end

function endCollision(b2Contact)

end


