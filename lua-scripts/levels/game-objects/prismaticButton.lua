local prismaticButton = {}

local function createPrismaticButton(box2dWorldProxy, options)
  -- make ground
  local groundDef = b2BodyDef()
  groundDef.position = options.groundPosition
  local groundShape = b2PolygonShape()
  groundShape:SetAsBox(1.0, 0.5)
  local groundFixture = b2FixtureDef()
  groundFixture.density = 1.0
  local ground = box2dWorldProxy:createNewBody(groundDef, groundShape, groundFixture)

  --make button 
  local buttonShape = b2PolygonShape()
  
  buttonShape:SetAsBox(options.shape.x, options.shape.y)
  
  local buttonDef = b2BodyDef()
  buttonDef.type = b2BodyType.b2_dynamicBody
  buttonDef.allowSleep = false
  buttonDef.position = options.buttonPosition
  local buttonFixture = b2FixtureDef()
  buttonFixture.density = 1.0
  
  local button = box2dWorldProxy:createNewBody(buttonDef, buttonShape, buttonFixture)
  
  --make prismatic joint joining button and ground
  local prismaticJoint = b2PrismaticJointDef()
  local axis = options.axis or b2Vec2(0.0, 1.0)
  axis:Normalize()
  prismaticJoint:Initialize(button, ground, button:GetWorldCenter(), axis)

  prismaticJoint.motorSpeed = options.motorSpeed or 1.0
  prismaticJoint.maxMotorForce = options.maxMotorForce or 160.0
  prismaticJoint.enableMotor = options.enableMotor or true
  prismaticJoint.lowerTranslation = options.lowerTranslation or  -2.0 
  prismaticJoint.upperTranslation = options.upperTranslation or  0.0
  prismaticJoint.enableLimit = options.enableLimit or  true
  
  return { joint = box2dWorldProxy:createPrismaticJoint(prismaticJoint)}
end

prismaticButton.createPrismaticButton = createPrismaticButton

return prismaticButton

