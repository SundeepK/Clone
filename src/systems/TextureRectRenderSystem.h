#ifndef TEXTURERECTRENDERSYSTEM_H_
#define TEXTURERECTRENDERSYSTEM_H_

#include <anax/System.hpp>
#include <components/TextureRectComponent.h>
#include <components/PhysicsComponent.h>
#include <components/AnimationComponent.h>

class TextureRectRenderSystem  : public sf::Drawable, public anax::System<TextureRectRenderSystem> {
	public:
		TextureRectRenderSystem() ;
		virtual ~TextureRectRenderSystem();

		void render(sf::RenderTarget* renderTarget);

	private:
		void draw(sf::RenderTarget& rt, sf::RenderStates states) const;

};

#endif /* TEXTURERECTRENDERSYSTEM_H_ */
