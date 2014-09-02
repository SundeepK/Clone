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
	walk = thor_FrameAnimation();
	addFrames(walk, 0, 0, 4, 1);		
	time = sf_seconds(0.5)
	animationComp:registerAnimation("walk", walk, time)
end


function addFrames(animation,  y, xFirst,  xLast, duration)
	local step = 0;
	if xFirst < xLast then
		step = 1
	else
		step = -1
	end

	xLast = (xLast + step ) 
	for  x = xFirst, xLast, step do
		if x < xLast then
		rect = sf_IntRect(88*x, 88*y, 88, 88)
		animation:addFrame(duration, rect)
		end
	end
end

--[[function addFrames(animation,  x,  yFirst,  yLast, duration)
	local step = 0;
	if yFirst < yLast then
		step = 1
	else
		step = -1
	end

	yLast = (yLast + step ) 
	for  y = yFirst, yLast, step do
		if y < yLast then
		rect = sf_IntRect(36*x, 39*y, 36, 39)
		animation:addFrame(duration, rect)
		end
	end
end--]]