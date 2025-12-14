#pragma once

#include "Mode.hpp"
#include <SFML/System/Clock.hpp>

class GUI : public Mode {
    private:
        int speedDelay;

        std::string lastRuleChanged;

        sf::Clock ruleChangeTimer;

        bool quietPauseMode;

    public:
        GUI() : speedDelay(50), lastRuleChanged(""), quietPauseMode(false) {}

        void adjustSpeed(int delta);

        void notifyRuleChange(const std::string &ruleName);

        bool shouldShowRuleNotification() const;

        std::string getLastRuleChanged() const { return lastRuleChanged; }

        bool isQuietPauseMode() const { return quietPauseMode; }
        void setQuietPauseMode(bool mode) { quietPauseMode = mode; }

        void run() override;
};
