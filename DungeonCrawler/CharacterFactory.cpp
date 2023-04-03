#include "CharacterFactory.h"

Character CharacterFactory::Create()
{
    return Character{baseHealth, baseDamage};
}
