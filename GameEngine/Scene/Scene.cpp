#include "Scene.hpp"

void Scene::on_event(const EventSPtr& event) { man_->on_event(event); }

void Scene::events() { man_->events(); }

void Scene::update() { man_->update(); }

void Scene::render(const Renderer& ren) { man_->render(ren); }
