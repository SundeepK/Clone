
#ifndef ENTITYTAG_H_
#define ENTITYTAG_H_

template <typename Tag_type>
class EntityTag {
public:
	EntityTag(const Tag_type& tag);
	virtual ~EntityTag();

	const Tag_type getTag() const;

private:
    const Tag_type m_tag;

};

template <typename Tag_type>
EntityTag<Tag_type>::EntityTag(const Tag_type& tag) : m_tag(tag){
}

template <typename Tag_type>
const Tag_type  EntityTag<Tag_type>::getTag() const{
	return m_tag;
}



#endif /* ENTITYTAG_H_ */
