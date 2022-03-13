#ifndef HUA5_TEST_TASK_CRAWLER_H
#define HUA5_TEST_TASK_CRAWLER_H

#include <string_view>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <list>


namespace Crawler {
    enum {
        DEFAULT_RANK = 0,
        TOP_FIVE = 5,
    };


    class Crawler {
        struct Node {
            size_t rank;
            std::unordered_set<std::string_view> urls;
        };

        std::list<Node> data;
        std::unordered_map<std::string_view, std::list<Node>::iterator> str_to_iterator;

        bool exists(std::string_view url);
    public:
        size_t get_rank(std::string_view root_url);

        // add newly found page url
        void add_url(std::string_view root_url);

        // add the content of newly found page url
        void add_hyperlink(std::string_view hyper_link);

        std::vector<std::string> query_top(size_t count);
        // return top 5 most important pages
        std::vector<std::string> query_top_five();

        // return a list of pages which urls have same prefix
        std::vector<std::string> query_list_of_pages_with_given_prefix(std::string_view prefix);
    };
}


#endif //HUA5_TEST_TASK_CRAWLER_H
