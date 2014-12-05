function init(b2worldProxy)
  box2dWorldProxy = b2worldProxy
end

function testBox()

  local anchorBodyDef = b2BodyDef()
  anchorBodyDef.position = b2Vec2(3.0, 10.0)
  
	local anchorShape = b2PolygonShape()
	anchorShape:SetAsBox(2.0, 0.5)

	local anchorFixDef = b2FixtureDef()
  
  local body = box2dWorldProxy:createNewBody(anchorBodyDef, anchorShape, anchorFixDef)	

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

