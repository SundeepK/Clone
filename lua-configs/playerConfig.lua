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