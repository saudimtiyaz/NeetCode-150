# Is Anagram — Learning Notes

The goal of this problem is to determine whether two strings contain the same characters with the same number of occurrences. My implementation progressed from searching for individual matches to sorting and comparing characters, with an intermediate attempt using C-style strings.

## Initial Approach: Search and Remove Matches

My first attempt checks whether the strings have the same length. If their lengths differ, the function returns `false` immediately.

For each character in `s`, a nested loop searches through `t`. When it finds a matching character, it erases that occurrence from `t` and stops the inner search. Removing one occurrence at a time accounts for repeated characters: each occurrence in `s` needs its own match in `t`.

After processing `s`, the function returns `true` if `t` is empty and `false` otherwise. Diagnostic messages describe the length check and the final result.

- **Worst-case time complexity:** O(n²), where n is the length of either equal-length input. Searching and erasing characters can each take linear time.
- **Space used by parameter copies:** O(n), because both strings are passed by value. The loops use a fixed number of index variables.

## Intermediate Approach: C-Style Strings

My next version kept the length check but changed the matching process. I added `<cstring>` and `<algorithm>`, copied the input characters into two character arrays, called `strlen` to obtain their lengths, sorted the arrays, and compared them with `strcmp`.

The approach expressed the idea that anagrams produce the same character sequence when sorted. Instead of removing individual matches, it compared the sorted sequences.

### Array and String Behavior

The arrays were declared with exactly as many elements as the input strings:

```cpp
char cstring_s[s.size()], cstring_t[t.size()];
```

The copy loop populated these elements without writing a null terminator. Since `strlen` and `strcmp` expect null-terminated strings, these calls could read beyond the arrays, resulting in undefined behavior. This observation comes from reading the code; no execution failure was recorded.

The array sizes were also determined at runtime. These variable-length array declarations are a compiler extension rather than standard C++.

This version was later enclosed in a block comment and labeled `(STASHED)` in the source file.

## Subsequent Approach: Sort and Compare C++ Strings

The next implementation used `std::sort` directly on the C++ strings:

```cpp
sort(s.begin(), s.end());
sort(t.begin(), t.end());
```

After the initial length check, both local string copies are sorted. A loop compares characters at corresponding positions. Matching characters continue the loop; the first mismatch returns `false`. Reaching the end returns `true`.

This version uses the strings' iterator ranges instead of separate character arrays, `strlen`, and `strcmp`. Only the unequal-length branch retains a diagnostic message. For two empty strings, the comparison loop has no iterations and the function returns `true`.

- **Worst-case time complexity:** O(n log n) for sorting, followed by an O(n) comparison, giving O(n log n) overall.
- **Space used by parameter copies:** O(n). Both strings are passed by value, so sorting operates on local copies.
- **Additional sorting storage:** Depends on the standard library implementation; commonly O(log n) stack space.

## Reason for Not Using Hash Maps

I chose not to use a hash map because I did not want the additional storage associated with that data structure in exchange for average O(1) lookup time. The O(1) figure describes individual average lookups, not the runtime of the entire anagram check. This was my reason for exploring the sorting approach.

## Example Inputs

The example in `main()` has remained:

```cpp
string s = "racecar";
string t = "carrace";
```

Both strings sort to `"aaccerr"`. Reading the sorting implementation indicates that it returns `true`, which `main()` would print as `1`. The initial search-and-remove implementation also consumes all matching characters for this example. These are code-reading observations, not recorded test results.

## Complexity and Measured Performance

The two submission screenshots show accepted solutions passing **37 out of 37 test cases**.

| Metric | Naïve implementation | Sorted implementation |
| --- | --- | --- |
| Worst-case time complexity | O(n²) | O(n log n) |
| Space used by parameter copies | O(n) | O(n) |
| Reported runtime | 290 ms | 15 ms |
| Runtime percentile | Beats 0.73% | Beats 100.00% |
| Reported memory usage | 107.0 MB | 108.4 MB |
| Memory percentile | Beats 93.02% | Beats 93.02% |

In these submissions, the sorted implementation took **275 ms less**, making it approximately **19.3 times faster**, with a **94.83% reduction** in reported runtime. Reported memory usage increased by **1.4 MB**, approximately **1.31%**.

The naïve submission's runtime beat 0.73% of the comparison population. Its graph shows a large concentration of submissions in the fastest runtime bucket, to the left of its 290 ms result. The sorted submission moved into that fastest region, with a reported runtime percentile of 100.00%.

Both screenshots report the same memory percentile, 93.02%, despite the difference in measured memory. These figures describe the platform's comparison population at submission time. A displayed 100.00% does not establish a unique fastest solution, and reported memory includes more than the algorithm's auxiliary storage.

### Naïve Submission

![Accepted naïve submission: 37 of 37 tests passed, 290 ms runtime, and 107.0 MB memory.](naive_method.png)

### Sorted Submission

![Accepted sorted submission: 37 of 37 tests passed, 15 ms runtime, and 108.4 MB memory.](sorted_method.png)

## Latest Source Observation

At the time of this rewrite, the initial search-and-remove function has been uncommented while the sorting function also remains active. Both definitions have the same signature, so the file currently contains a function redefinition. The C-style version remains commented out. A new comment above the sorting version describes using an O(n log n) sorting algorithm instead of the C-style implementation.

## Key Observations

- The initial approach consumes matching characters one occurrence at a time.
- Both sorting attempts arrange characters before comparing their sequences.
- The C-style attempt uses character arrays and null-terminated string functions; the subsequent version operates directly on C++ strings.
- Passing the strings by value gives each function local copies of the inputs.
- The source preserves the earlier approaches alongside the sorting implementation.
