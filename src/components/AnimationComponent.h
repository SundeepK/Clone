#ifndef ANIMATIONCOMPONENT_H_
#define ANIMATIONCOMPONENT_H_


#include <anax/Component.hpp>
#include <SFML/Graphics.hpp>
#include <Thor/Animation.hpp>

class AnimationComponent  : public anax::Component<AnimationComponent> {

	public:
		thor::Animator<sf::Sprite, std::string> animator;
		bool loadSpriteSheet(std::string spriteSheetLocation);
		void registerAnimation(std::string animationId, thor::FrameAnimation animation, sf::Time duration);
		sf::Sprite m_sprite;

	private:
		sf::Texture m_texture;

};

inline bool AnimationComponent::loadSpriteSheet(std::string spriteSheetLocation) {
	sf::Image image;
	if (!image.loadFromFile(spriteSheetLocation)){
		return false;
	}

	image.createMaskFromColor(sf::Color::White);
	sf::Texture texture;

	if (!texture.loadFromImage(image))
		return false;

	m_sprite = sf::Sprite(texture);
	return true;
}

inline void AnimationComponent::registerAnimation(std::string animationId, thor::FrameAnimation animation, sf::Time duration) {
	animator.addAnimation(animationId, animation, duration);
}

#endif /* ANIMATIONCOMPONENT_H_ */
