#pragma once
#include "BaseObject.h"

class Bullet : public BaseObject {
public:
    Bullet(float radius, const sf::Vector2f& position);
    void Update(float dt) override;
    bool Obsolete() const;
    void SetManuallyObsolete();

private:
    float _lifeTime = 0.0f; // Tiempo de vida
    bool manuallyObsolete;
};
