#include <iostream>
#include <memory>
#include <thread>

#include "graphics/interface/interface.hpp"
#include "graphics/interface/scene_control.hpp"
#include "graphics/interface/scene_switcher.hpp"
#include "graphics/renderer.hpp"
#include "graphics/scene_camera.hpp"
#include "input.hpp"
#include "modules/reconstruction.hpp"
#include "scene.hpp"
#include "scene_list.hpp"
#include "server/server.hpp"

int main() {
    tomovis::Renderer renderer;

    auto& input = tomovis::Input::instance(renderer.window());
    renderer.register_ticker(input);

    // construct interface
    tomovis::Interface interface(renderer.window());
    renderer.register_target(interface);
    input.register_handler(interface);

    // construct the scenes
    tomovis::SceneList scenes;
    renderer.register_target(scenes);
    input.register_handler(scenes);

    tomovis::SceneSwitcher scene_switcher(scenes);
    interface.register_window(scene_switcher);
    input.register_handler(scene_switcher);

    tomovis::SceneControl scene_control(scenes);
    interface.register_window(scene_control);

    // start the server
    tomovis::Server server(scenes);

    // FIXME: add modules to the server
    server.register_module(std::make_shared<tomovis::ReconstructionProtocol>());

    server.start();
    renderer.register_ticker(server);

    // enter main loop
    renderer.main_loop();

    return 0;
}
