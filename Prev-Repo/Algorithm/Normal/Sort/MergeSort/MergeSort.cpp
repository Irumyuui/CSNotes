template <std::random_access_iterator RandomIter,
          std::random_access_iterator RandomTempIter, typename Comp>
  requires requires(Comp comp, RandomIter it, RandomTempIter tmp_it) {
    { comp(*it, *it) } -> std::same_as<bool>;
    { comp(*tmp_it, *tmp_it) } -> std::same_as<bool>;
  }
constexpr auto MergeSort(RandomIter begin, RandomIter end,
                         RandomTempIter temp_begin, RandomTempIter temp_end,
                         Comp &&comp) -> void {
  if (begin + 1 == end) {
    return;
  }
 
  auto mid = begin + (end - begin) / 2;
  auto temp_mid = temp_begin + (temp_end - temp_begin) / 2;
  MergeSort(begin, mid, temp_begin, temp_mid, std::forward<Comp>(comp));
  MergeSort(mid, end, temp_mid, temp_end, std::forward<Comp>(comp));
 
  auto left_it = begin, right_it = mid;
  auto tit = temp_begin;
  while (left_it < mid && right_it < end) {
    if (comp(*left_it, *right_it)) {
      *tit = std::move(*left_it);
      ++left_it;
    } else {
      *tit = std::move(*right_it);
      ++right_it;
    }
    ++tit;
  }
  while (left_it < mid) {
    *tit = std::move(*left_it);
    ++tit;
    ++left_it;
  }
  while (right_it < end) {
    *tit = std::move(*right_it);
    ++tit;
    ++right_it;
  }
 
  while (begin < end) {
    *begin = std::move(*temp_begin);
    ++begin;
    ++temp_begin;
  }
}
 
template <std::random_access_iterator Iter, typename Comp>
  requires requires(Comp comp, Iter it) {
    { comp(*it, *it) } -> std::same_as<bool>;
  }
constexpr auto MergeSort(Iter begin, Iter end, Comp &&comp) -> void {
  std::vector<typename std::iterator_traits<Iter>::value_type> buffer(end -
                                                                      begin);
  MergeSort(begin, end, std::begin(buffer), std::end(buffer),
            std::forward<Comp>(comp));
}