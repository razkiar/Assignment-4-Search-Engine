#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Query.h"
#include "UserInterface.h"

const std::string basePath = "sample_data/coll_1/"; // Directory containing your sample data

TEST_CASE("Basic Query Functionality", "[Query]") {
    UserInterface ui;
    ui.createIndex(basePath); // Provide directory path

    SECTION("Single Word Query") {
        ui.enterQuery("test", true); // Assuming enterQuery requires a second argument
        auto results = ui.readQueryResults();
        REQUIRE_FALSE(results.empty());
    }

    SECTION("Multiple Word Query") {
        ui.enterQuery("multiple words", true);
        auto results = ui.readQueryResults();
        REQUIRE_FALSE(results.empty());
    }
}

TEST_CASE("Empty Query Handling", "[Query]") {
    UserInterface ui;
    ui.createIndex(basePath);

    ui.enterQuery("", true);
    auto results = ui.readQueryResults();
    REQUIRE(results.empty());
}

TEST_CASE("Non-Existent Key Query", "[Query]") {
    UserInterface ui;
    ui.createIndex(basePath);

    ui.enterQuery("nonexistentword", true);
    auto results = ui.readQueryResults();
    REQUIRE(results.empty());
}

TEST_CASE("Special Query Types", "[Query]") {
    UserInterface ui;
    ui.createIndex(basePath);

    SECTION("Organization Query") {
        ui.enterQuery("org:exampleOrg", true);
        auto results = ui.readQueryResults();
        REQUIRE_FALSE(results.empty());
    }

    SECTION("Person Query") {
        ui.enterQuery("person:examplePerson", true);
        auto results = ui.readQueryResults();
        REQUIRE_FALSE(results.empty());
    }
}

TEST_CASE("Exclusion Terms in Query", "[Query]") {
    UserInterface ui;
    ui.createIndex(basePath);

    ui.enterQuery("test -exclude", true);
    auto results = ui.readQueryResults();
    // Add checks to ensure 'exclude' term is handled correctly
}
