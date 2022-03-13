#include <crawler.h>
#include <exception>

size_t Crawler::Crawler::get_rank(std::string_view root_url) {
    if (!exists(root_url)) {
        throw std::logic_error("No url such as: " + std::string(root_url));
    }
    auto it = str_to_iterator[root_url];
    return it->rank;
}

void Crawler::Crawler::add_url(std::string_view root_url) {
    if (exists(root_url)) {
        return;
    }
    if (data.empty() || data.front().rank != DEFAULT_RANK) {
        data.emplace_front(Node{DEFAULT_RANK, {root_url}});
    } else {
        data.front().urls.insert(root_url);
    }
    str_to_iterator[root_url] = data.begin();
}

void Crawler::Crawler::add_hyperlink(std::string_view hyper_link) {
    if (!exists(hyper_link)) {
        throw std::logic_error("No url such as: " + std::string(hyper_link));
    }
    auto it = str_to_iterator[hyper_link];
    if (next(it) != data.end() && next(it)->rank == it->rank + 1) {
        next(it)->urls.insert(hyper_link);
    } else {
        data.insert(next(it), Node{it->rank + 1, {hyper_link}});
    }
    it->urls.erase(hyper_link);
    str_to_iterator[hyper_link] = next(it);
    if (it->urls.empty()) {
        // Collect garbage if any
        // Because of that we're getting linear time
        data.erase(it);
    }
}

bool Crawler::Crawler::exists(std::string_view url) {
    return str_to_iterator.find(url) != str_to_iterator.end();
}

std::vector<std::string> Crawler::Crawler::query_top(size_t count) {
    std::vector<std::string> result;
    for (auto rit = data.rbegin(); result.size() < count && rit != data.rend(); rit++) {
        for (std::string_view str : rit->urls) {
            result.emplace_back(str);
            if (result.size() >= count) {
                break;
            }
        }
    }
    return result;
}

std::vector<std::string> Crawler::Crawler::query_top_five() {
    return query_top(TOP_FIVE);
}

