# Huawei-5 test task

## Formalisation of the problem 

There is a web-page. On the web-page we have hyper-links to other pages (maybe to itself). 
So the structure is a directed graph.

We will define rank of a page as a number of appropriate vertex indegree.

We have to implement next interface:

* `add_url` 
Add vertex to the graph
* `add_hyperlink`
Add edge to the graph
* `query_top_five`
Return top-5 vertices with most indegree
* `query_list_of_pages_with_given_prefix`

## Implementation

For function `query_list_of_pages_with_given_prefix` we will use [trie](https://en.wikipedia.org/wiki/Trie).
Asymptotic time for query is O(|Trie|) or O(|Answer size|)

To get vertex statistics we will use combination of hash map and list:
* ```
  struct Node {
    size_t rank;
    std::unordered_set<std::string_view> urls;
  }
* `list<Node>` -- stores `<rank, urls>` in sorted order
* `std::unordered<std::string_view, std::unique_ptr<Node>>` -- 
stores appropriate list node

So when we add an url, we're either creating new node or adding the url to a vector in an existing node.

When we add hyperlink (increasing indegree of some url) we're locating node, where url is located, extracting url from it and move it to the next node, which is appropriate to `rank + 1` (or create one).

Asymptotic time is O(1) in average for top5 and linear foarbitrary size.