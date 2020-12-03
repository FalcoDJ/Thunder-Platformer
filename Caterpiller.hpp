#include "Creature.hpp"

class Caterpiller : public Creature
{
private:

public:
    Caterpiller() {};
    ~Caterpiller(){};
    virtual void updateAi(RectF& Targ){};
    void animate() override;
};