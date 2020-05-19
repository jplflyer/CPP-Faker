#include "ESports.h"

/**
 * Produces the name of a professional eSports player.
 *
 * @return [String]
 *
 * @example
 *   Faker::Esport::player() => "Crimsix"
 */
std::string
Faker::ESports::player() {
    return parse("esport.players");
}

/**
 * Produces the name of an eSports team.
 *
 * @return [String]
 *
 * @example
 *   Faker::Esport::team() => "CLG"
 */
std::string
Faker::ESports::team() {
    return parse("esport.teams");
}

/**
 * Produces the name of an eSports league.
 *
 * @return [String]
 *
 * @example
 *   Faker::Esport::league() => "IEM"
 */
std::string
Faker::ESports::league() {
    return parse("esport.leagues");
}

/**
 * Produces the name of an eSports event.
 *
 * @return [String]
 *
 * @example
 *   Faker::Esport::event() => "ESL Cologne"
 */
std::string
Faker::ESports::event() {
    return parse("esport.events");
}

/**
 * Produces the name of a game played as an eSport.
 *
 * @return [String]
 *
 * @example
 *   Faker::Esport::game() => "Dota 2"
 */
std::string
Faker::ESports::game() {
    return parse("esport.games");
}
