#include "node.h"

const float EPSILON = 0.001;

void Node::destroy()
{
    onDestroy(*this);

    //TODO: engine->EarlyResourceReleaseCallback();
}