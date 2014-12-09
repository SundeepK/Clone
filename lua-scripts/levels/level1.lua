function init(levelObjects)
  levelObjectsTable = levelObjects
end

function update()
  local pos = RopeBox:GetAngle()
  print(pos)
end

function beginCollision(b2Contact)
  print("in begin contact")
end


function endCollision(b2Contact)
  print("in end contact")

end