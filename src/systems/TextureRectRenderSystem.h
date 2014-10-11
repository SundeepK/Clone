#ifndef TEXTURERECTRENDERSYSTEM_H_
#define TEXTURERECTRENDERSYSTEM_H_

#include <anax/System.hpp>
#include <components/TextureRectComponent.h>
#include <components/PhysicsComponent.h>
#include <components/AnimationComponent.h>
#include <memory>

class TextureRectRenderSystem  : public sf::Drawable, public anax::System<TextureRectRenderSystem> {
	public:
		TextureRectRenderSystem() ;
		virtual ~TextureRectRenderSystem();

	private:
		void draw(sf::RenderTarget& rt, sf::RenderStates states) const;

		class TextureRectRenderSystemImpl;
		std::unique_ptr<TextureRectRenderSystemImpl> m_impl;

};

#endif /* TEXTURERECTRENDERSYSTEM_H_ */
