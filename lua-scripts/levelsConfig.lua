function getLevelsToLoad()
	local level1 = LevelObject()
	level1.levelMapName = "level-1.tmx" 
	level1.scriptName = "level-1.lua"
	
	local level2 = LevelObject()
  level2.levelMapName = "level-2.tmx" 
  level2.scriptName = "level-2.lua"
	
	return {level1, level2}
end
