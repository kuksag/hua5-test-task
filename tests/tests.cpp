#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "crawler.h"

TEST_CASE("Check add_url and get_rank on zero-ranks") {
    Crawler::Crawler crawler{};

    crawler.add_url("foo");
    crawler.add_url("bar");

    CHECK(crawler.get_rank("foo") == 0);
    CHECK(crawler.get_rank("bar") == 0);
    CHECK_THROWS_AS(crawler.get_rank("not exist"), std::logic_error);
}

TEST_CASE("Check add_hyperlink") {
    Crawler::Crawler crawler{};

    crawler.add_url("foo");
    crawler.add_url("bar");
    CHECK(crawler.get_rank("foo") == 0);
    CHECK(crawler.get_rank("bar") == 0);


    crawler.add_hyperlink("foo");
    CHECK(crawler.get_rank("foo") == 1);
    crawler.add_hyperlink("foo");
    CHECK(crawler.get_rank("foo") == 2);

    crawler.add_hyperlink("bar");
    CHECK(crawler.get_rank("bar") == 1);
    crawler.add_hyperlink("bar");
    CHECK(crawler.get_rank("bar") == 2);
    crawler.add_hyperlink("bar");
    CHECK(crawler.get_rank("bar") == 3);
}

TEST_CASE("Check query_top") {
    typedef std::vector<std::string> vs;

    Crawler::Crawler crawler{};

    CHECK(crawler.query_top_five().empty());


    crawler.add_url("foo");
    crawler.add_hyperlink("foo");
    CHECK(crawler.query_top(1) == vs{"foo"});

    crawler.add_url("bar");
    crawler.add_hyperlink("bar");
    crawler.add_hyperlink("bar");

    CHECK(crawler.query_top(1) == vs{"bar"});
}

TEST_CASE("Check query_top_five") {
    typedef std::vector<std::string> vs;

    Crawler::Crawler crawler{};

    vs urls{
            "url0",
            "url1",
            "url2",
            "url3",
            "url4",
            "url5",
    };

    for (std::string &url: urls) {
        crawler.add_url(url);
    }
    for (int i = urls.size() - 1; i < urls.size(); i--) {
        for (int j = 0; j < i; j++) {
            crawler.add_hyperlink(urls[i]);
        }
    }
    CHECK(crawler.query_top_five() ==
          vs{
                  "url5",
                  "url4",
                  "url3",
                  "url2",
                  "url1",
          }
    );
}

TEST_CASE("Check trie") {
    typedef std::vector<std::string> vs;

    Crawler::Crawler crawler{};

    vs urls{
        "abacaba",
        "abacab",
        "abaca",
        "abac",
        "aba",
        "ab",
        "a",
        "foo",
    };

    for (std::string &url: urls) {
        crawler.add_url(url);
    }

    CHECK(crawler.query_list_of_pages_with_given_prefix("foo") == vs{"foo"});
    CHECK(crawler.query_list_of_pages_with_given_prefix("bar") == vs{});

    CHECK(crawler.query_list_of_pages_with_given_prefix("a").size() == urls.size() - 1);
    CHECK(crawler.query_list_of_pages_with_given_prefix("ab").size() == urls.size() - 2);
    CHECK(crawler.query_list_of_pages_with_given_prefix("aba").size() == urls.size() - 3);
    CHECK(crawler.query_list_of_pages_with_given_prefix("abac").size() == urls.size() - 4);
    CHECK(crawler.query_list_of_pages_with_given_prefix("abaca").size() == urls.size() - 5);
    CHECK(crawler.query_list_of_pages_with_given_prefix("abacab").size() == urls.size() - 6);
    CHECK(crawler.query_list_of_pages_with_given_prefix("abacaba").size() == urls.size() - 7);
}