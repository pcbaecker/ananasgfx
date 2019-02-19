#ifndef GFX_SCENE_H
#define GFX_SCENE_H

#include <memory>
#include <list>

#include <ananasgfx/gfx/Node.hpp>

namespace gfx {

    class Window;

    class Scene : public Node {
        friend class Window;
    public:

    };

}

#endif