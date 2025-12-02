#pragma once

#include "Mode.hpp"
#include <SFML/System/Clock.hpp>

class GUI : public Mode {
    private:
        // Délai en millisecondes entre chaque itération (contrôle la vitesse)
        // Plus la valeur est élevée, plus le jeu est lent
        int speedDelay;
        
        // Nom du dernier mode changé pour afficher une notification temporaire
        std::string lastRuleChanged;
        
        // Horloge pour afficher temporairement le nom du mode (disparaît après 2 secondes)
        sf::Clock ruleChangeTimer;
        
    public:
        // Constructeur: initialise la vitesse par défaut à 50ms
        GUI() : speedDelay(50), lastRuleChanged("") {}
        
        ~GUI() = default;
        
        // Ajuste la vitesse de simulation en augmentant ou diminuant le délai
        // delta > 0 : ralentit le jeu, delta < 0 : accélère le jeu
        // Le délai reste entre 10ms (très rapide) et 1000ms (très lent)
        void adjustSpeed(int delta);
        
        // Enregistre le changement de mode et démarre le timer de notification
        void notifyRuleChange(const std::string &ruleName);
        
        // Retourne true si la notification du mode doit encore être affichée
        // (elle disparaît après 2 secondes)
        bool shouldShowRuleNotification() const;
        
        // Retourne le nom du dernier mode changé pour l'affichage
        std::string getLastRuleChanged() const { return lastRuleChanged; }
        
        // Lance la boucle de jeu en mode graphique
        void run() override;
};
