function getLevelsToLoad()

	return {
	      createLevel("level-3.tmx", ""),
	      createLevel("level-1.tmx", "level1.lua"), 
	      createLevel("level-2.tmx", "emptyLevelScript.lua")
	      }
end

function createLevel(mapName, scriptName) 
  local level = LevelObject()
  level.levelMapName = mapName 
  level.scriptName = scriptName
  return level
end
