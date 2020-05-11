#include <type_traits>
#include "UseKey.h"


UseKey begin(UseKey)
{
	return UseKey::K_NON;
}

UseKey end(UseKey)
{
	return UseKey::K_MAX;
}

UseKey operator*(UseKey key)
{
	return key;
}

UseKey operator++(UseKey& key)
{
	return key = UseKey(std::underlying_type<UseKey>::type(key) + 1);
}