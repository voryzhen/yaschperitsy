// Refactor as Component ?
OldGame::OldGame() _topbar() {}

int OldGame::update()
{
    update_yaschperitsy();
    update_player();
    destroy_objects();

    // kostyl
    _stat->_curr_hp = _player->health();

    _manager.refresh();
    _manager.update(_event);

    if (_stat->_curr_hp < 1 || _stat->_score == 10)
    {
        _end = true;
        return -4; // TODO: Magic nums for now
    }
    else
    {
        return 0;
    }
}

void OldGame::reset_state()
{
    if (_end)
    {
        _end = false;
        for (auto& e : _manager.get_entities())
        {
            if (e->type() != ecs::EntityType::player)
            {
                e->destroy();
            }
        }
        _player->reset_state();

        _stat->_max_score = std::max(_stat->_max_score, _stat->_score);
        _stat->_score = 0;
        _stat->_yaschperitsy_num = _stat->_yaschperitsy_total_num;
    }
}
