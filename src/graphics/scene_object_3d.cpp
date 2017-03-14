#include <algorithm>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "graphics/components/reconstruction_component.hpp"
#include "graphics/scene_camera_3d.hpp"
#include "graphics/scene_object_3d.hpp"
#include "graphics/shader_program.hpp"

namespace tomovis {

SceneObject3d::SceneObject3d() : SceneObject() {
    this->add_component(std::make_unique<ReconstructionComponent>());
    camera_3d_ = std::make_unique<SceneCamera3d>(
        ((ReconstructionComponent&)(*components_["reconstruction"])).slices());
}

SceneObject3d::~SceneObject3d() {}

void SceneObject3d::draw(glm::mat4 window_matrix) {
    auto world_to_screen = window_matrix * camera_3d_->matrix();
    for (auto& component : components_) {
        component.second->draw(world_to_screen);
    }
}

}  // namespace tomovis