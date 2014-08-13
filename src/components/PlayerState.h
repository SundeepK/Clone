#ifndef PLAYERSTATE_H_
#define PLAYERSTATE_H_
#include <unordered_map>

enum class PlayerState {
		NO_STATE = -1,
		DEFAULT_STATE = 0,
		MOVE_LEFT,
		MOVE_RIGHT,
		JUMP,
		MOVE_DOWN
};

namespace std
{
template<>
struct hash<PlayerState>
   {
       typedef PlayerState argument_type;
       typedef std::underlying_type< argument_type >::type underlying_type;
       typedef std::hash< underlying_type >::result_type result_type;
       result_type operator()( const argument_type& arg ) const
       {
           std::hash< underlying_type > hasher;
           return hasher( static_cast< underlying_type >( arg ) );
       }
};
}
#endif /* PLAYERSTATE_H_ */
