local prismaticButton = {}

local function createPrismaticButton(box2dWorldProxy)
  -- make ground
--  local groundDef = b2BodyDef()
--  groundDef.position = b2Vec2(25.0, 20.0)
--  local groundShape = b2PolygonShape()
--  groundShape:SetAsBox(1.0, 0.5)
--  local groundFixture = b2FixtureDef()
--  groundFixture.density = 0.0
--  local ground = box2dWorldProxy:createNewBody(groundDef, groundShape, groundFixture)
  
    local groundDef = b2BodyDef()
    local groundShape = b2EdgeShape()
    groundShape:Set(b2Vec2(-40.0, 0.0), b2Vec2(40.0, 0.0))
    local groundFixture = b2FixtureDef()
    groundFixture.density = 0.0
      local ground = box2dWorldProxy:createEdgeNewBody(groundDef, groundShape, groundFixture)
    
--    b2BodyDef bd;
--      ground = m_world->CreateBody(&bd);
--
--      b2EdgeShape shape;
--      shape.Set(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
--      ground->CreateFixture(&shape, 0.0f);
  
  --make button 
  local buttonShape = b2PolygonShape()
  buttonShape:SetAsBox(1.0, 0.2)
  
  local buttonDef = b2BodyDef()
  buttonDef.type = b2BodyType.b2_dynamicBody
  buttonDef.allowSleep = false
  buttonDef.position = b2Vec2(25, 0.0)
  
  local buttonFixture = b2FixtureDef()
  buttonFixture.density = 5.0
  
  local button = box2dWorldProxy:createNewBody(buttonDef, buttonShape, buttonFixture)
  
  --make prismatic joint joining button and ground
  local prismaticJoint = b2PrismaticJointDef()
  local axis = b2Vec2(0.0, 1.0)
  axis:Normalize()
  local center = b2Vec2(0.0, -5.0)
  prismaticJoint:Initialize(ground, button, center, axis)

  prismaticJoint.motorSpeed = 10.0
  prismaticJoint.maxMotorForce = 10000.0
  prismaticJoint.enableMotor = true
  prismaticJoint.lowerTranslation = 0.0
  prismaticJoint.upperTranslation = 20.0
  prismaticJoint.enableLimit = true

  box2dWorldProxy:createPrismaticJoint(prismaticJoint)

end

prismaticButton.createPrismaticButton = createPrismaticButton

return prismaticButton

