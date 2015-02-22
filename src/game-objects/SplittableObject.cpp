#include <game-objects/SplittableObject.h>
#include <tmx/tmx2box2d.h>
#include <sstream>
#include <components/PhysicsComponent.h>
#include <components/NinjaDataComponent.h>
#include <components/Direction.h>
#include <boost/algorithm/string.hpp>
#include <components/PhysicsComponent.h>
#include <components/Texcoords.h>
#include <opengl/TextureLoader.h>
#include <components/SplitDirectionComponent.h>
#include <game-objects/GameObjectTag.h>

class SplittableObject::SplittableObjectImpl{

public:

	SplittableObjectImpl(){

	}

	~SplittableObjectImpl(){

	}


	std::vector<b2Vec2> parseTexCoordsFromTmxObject(std::string texCoordsToParse){
		 std::stringstream texCoordStream(texCoordsToParse);
		 std::vector<b2Vec2> textureCoords;
		 int count = 0;
		 std::string texCoord;
		 float x;
		 while(std::getline(texCoordStream,texCoord,',')){
			 count++;
			 //TODO Handle exception if texcoord cant be parsed
			 float value = std::stof(texCoord);
			 if(count % 2 == 0){
				 textureCoords.push_back(b2Vec2(x, value));
			 }else{
				x = value;
			 }
		 }
		 return textureCoords;
	}


	void createEntity(tmx::MapObject mapObject, b2World& box2dWorld, anax::World& anaxWorld) {
		auto objectEntity = anaxWorld.createEntity();
		auto& texCoordsComp = objectEntity.addComponent<Texcoords>();
		auto& splitDirectionComp = objectEntity.addComponent<SplitDirectionComponent>();
		auto& physComp = objectEntity.addComponent<PhysicsComponent>();
		auto& ninjaData = objectEntity.addComponent<NinjaDataComponent>();


		if (!texCoordsComp.image.loadFromFile("maps/" + mapObject.GetPropertyString("Texture")))
			std::cout << "unable to load texture from tmx: " <<  mapObject.GetPropertyString("Texture") << std::endl;
		texCoordsComp.image.flipVertically();
		texCoordsComp.textCoords = parseTexCoordsFromTmxObject(mapObject.GetPropertyString("TexCoords"));

		texCoordsComp.texture = TextureLoader::loadAsOpenglTexture(texCoordsComp.texture, texCoordsComp.image);
		std::cout << mapObject.PolyPoints().size() << "points size" << std::endl;

		if (mapObject.GetPropertyString("Body") == "dynamic") {
			physComp.physicsBody = tmx::BodyCreator::Add(mapObject, box2dWorld, b2_dynamicBody);
		} else {
			physComp.physicsBody = tmx::BodyCreator::Add(mapObject, box2dWorld, b2_staticBody);
		}

		b2Filter filter;
		filter.categoryBits = GameObjectTag::SPLITTABLE_OBJECT;;
		physComp.physicsBody->GetFixtureList()->SetFilterData(filter);

		splitDirectionComp.splitDirection = DirectionMap::parseDirection(mapObject.GetPropertyString("SplitDir"));

		objectEntity.activate();

	}


};


SplittableObject::SplittableObject() : m_impl(new SplittableObjectImpl()){

}

SplittableObject::~SplittableObject() {

}

void SplittableObject::createEntity(tmx::MapObject mapObject, b2World& box2dWorld, anax::World& anaxWorld) {
	m_impl->createEntity(mapObject, box2dWorld, anaxWorld);
}

GameObjectProperty SplittableObject::getProperties() {
	GameObjectProperty object;
	object.properties = { {"Texture", "plankssmall.png"}, {"TexCoords", "0,1,1,1,1,0,0,0"}, {"Body", "static"} };
	object.objectShapeType = tmx::MapObjectShape::Rectangle;
	return object;
}
