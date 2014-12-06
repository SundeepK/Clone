function init(b2worldProxy)
  box2dWorldProxy = b2worldProxy
end

function testBox()
 
  local  ropeDef = b2RopeJointDef();
 
  local anchorBodyDef = b2BodyDef()
  anchorBodyDef.position = b2Vec2(8.0, 0.0)
  
	local anchorShape = b2PolygonShape()
	anchorShape:SetAsBox(2.0, 0.5)

	local anchorFixDef = b2FixtureDef()
  
  local ropeAnchor = box2dWorldProxy:createNewBody(anchorBodyDef, anchorShape, anchorFixDef)	
 
 --generate chain 
  local chainShape = b2PolygonShape()
  chainShape:SetAsBox(0.1, 0.5);
  
  local chainFixture = b2FixtureDef()
  chainFixture.density = 20.0
  chainFixture.friction = 0.2
  --chainFixture.filter.categoryBits = 0x0001
--  chainFixture.filter.maskBits =  (0xff - 0x0003);
  
  local chainJoint =  b2RevoluteJointDef();
  chainJoint.collideConnected = false;  
  
  local maxChains = 10
  local x = 8.0
  
  ropeDef.localAnchorA = b2Vec2(0.0, x)
  
  local prevBody = ropeAnchor
  prevBody:SetAngularDamping(1.0)
  for y = 0, maxChains, 1 do
      local chainBodyDef = b2BodyDef()
      chainBodyDef.angularDamping = 1.0
      chainBodyDef.type = b2BodyType.b2_dynamicBody
      chainBodyDef.position = b2Vec2(x, y)
      if y == (maxChains) then
        chainBodyDef.position = b2Vec2(x, y)
        chainShape:SetAsBox(1.5, 1.5)
       -- chainFixture.filter.maskbits = 0x0003
        chainFixture.density = 1.0
      end     
     local chainBody = box2dWorldProxy:createNewBody(chainBodyDef, chainShape, chainFixture)     
     local anchor = b2Vec2(x, y - 0.5)     
     chainJoint:Initialize(prevBody, chainBody, anchor)
    
     local b = box2dWorldProxy:createJoint(chainJoint)  
     print("im here lua")
     
     prevBody = chainBody
     
  end
  
   ropeDef.localAnchorB = b2Vec2(0.0, 0.0)
   local extraLength = 0.01;
   ropeDef.maxLength = maxChains - 1.0 + extraLength;
   ropeDef.bodyB = prevBody;
   ropeDef.bodyA = ropeAnchor;
   --box2dWorldProxy:createJoint(ropeDef)
    
end

function loadPhysicsComp(playerComp)
	playerComp.previousAngle = 10
	playerComp.previousPosition = b2Vec2(40,10)
end

function loadTexCoords(texComp)
	texCoords = vectorOfb2Vec2()
	texCoords:push_back(b2Vec2(0.0, 1.0))
	texCoords:push_back(b2Vec2(1.0, 1.0))
	texCoords:push_back(b2Vec2(1.0, 0.0))
	texCoords:push_back(b2Vec2(0.0, 0.0))
	texComp.textCoords = texCoords
end

function loadAnimations(animationComp)
	
	--standing
	standing = thor_FrameAnimation();
	addSingleFrame(standing, 0, 1, 0.5, false);		
	time = sf_seconds(0.5)
	animationComp:registerAnimation("standing", standing, time)
	
	--walk right
	walkRight = thor_FrameAnimation();
	addFrames(walkRight, 0, 0, 4, 0.5, false);		
	time = sf_seconds(0.5)
	animationComp:registerAnimation("walkRight", walkRight, time)
	
	--walk left
	walkLeft = thor_FrameAnimation();
	addFrames(walkLeft, 0, 1, 5, 0.5, true);		
	time = sf_seconds(0.5)
	animationComp:registerAnimation("walkLeft", walkLeft, time)	
	
	
end

function addSingleFrame(animation, xOffset, yOffset, duration, shouldFlip)
	local flip = 1
	if shouldFlip then
		flip = -1
	end
	rect = sf_IntRect(88*xOffset, 88*yOffset, 88 * flip, 88)
	animation:addFrame(duration, rect)
end

function addFrames(animation,  y, xFirst,  xLast, duration, shouldFlip)
	local step = 0;
	if xFirst < xLast then
		step = 1
	else
		step = -1
	end
	
	local flip = 1
	if shouldFlip then
		flip = -1
	end
	
	xLast = (xLast + step ) 
	for  x = xFirst, xLast, step do
		if x < xLast then
		rect = sf_IntRect(88*x, 88*y, 88 * flip, 88)
		animation:addFrame(duration, rect)
		end
	end
end

