#ifndef MOUSEEVENTPROCESSOR_H_
#define MOUSEEVENTPROCESSOR_H_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <Splitter.h>
#include <anax/anax.hpp>
#include <Box2D/Box2D.h>
#include <memory.h>


struct CompareEntities
{
    bool operator() (const anax::Entity& lhs, const anax::Entity& rhs) const{
        return lhs.getId() < rhs.getId();
    }
};

class B2dSplitter : public B2BodySplitCallback,  public anax::System<B2dSplitter>{
public:
	B2dSplitter(b2World& box2dWorld, anax::World& anaxWorld);
	~B2dSplitter();

    void onb2BodySplit(std::vector<B2BoxBuilder>& splitBodies, b2Body* body);
    void split(b2Vec2 startPoint, b2Vec2 endPoint);
    void clearIntersects();
    void deleteEntities();
    void refreshEntityBodyTypes();

private:

    class B2dSplitterImpl;
    std::unique_ptr<B2dSplitterImpl> m_impl;

};

#endif /* MOUSEEVENTPROCESSOR_H_ */
