#include "GameState.h"

namespace Tce {

    bool GameState::CheckState() {
        if (state != m_readyState) {
            state = m_readyState;
            return true;
        }
        return false;
    }

}

