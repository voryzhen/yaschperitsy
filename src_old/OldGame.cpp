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
