#pragma once
#include "Game.h"
#include "UnityEngine.h"

namespace Idxhook::Hooks {

    namespace GhostAI {

        namespace Original { static inline std::add_pointer_t<void(void*, void*)> Start = nullptr; }

    }

    namespace DNAEvidence {

        namespace Original { static inline std::add_pointer_t<void(void*, void*)> Start = nullptr; }

    }

    namespace LevelController {

        namespace Original { static inline std::add_pointer_t<void(void*, void*)> Start = nullptr; }

    }

    namespace GameController {

        namespace Original { static inline std::add_pointer_t<void(void*, void*)> Exit = nullptr; }

    }

    namespace PauseMenuController {

        namespace Original { static inline std::add_pointer_t<void(void*, void*)> Leave = nullptr; }

    }

    namespace RewardManager {

        namespace Original { static inline std::add_pointer_t<void(void*, void*)> Awake = nullptr; }

    }

    namespace SceneManager {

        namespace Original {

            static inline std::add_pointer_t<void(System::String *, void *)> LoadScene = nullptr;
            static inline std::add_pointer_t<void(UnityEngine::Scene, int, void *)> SceneLoaded = nullptr;

        }

    }

    namespace FuseBox {

        namespace Original {

            static inline std::add_pointer_t<void(void*, void*)> Use = nullptr;
            static inline std::add_pointer_t<void(void*, bool, void*)> TurnOff = nullptr;

        }

    }

    namespace GUIUtility {

        namespace Original { static inline std::add_pointer_t<void(void*)> CheckOnGUI = nullptr; }

    }

    namespace Player {

        namespace Original { static inline std::add_pointer_t<void(Game::Player*, void*)> Update = nullptr; }

    }
}
