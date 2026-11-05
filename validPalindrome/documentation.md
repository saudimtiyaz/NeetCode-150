# Valid Palindrome — Learning Notes

The goal of this problem is to check whether a string reads the same forward and backward after ignoring non-alphanumeric characters and treating uppercase and lowercase letters as equivalent. My attempts progressed from opposite-end comparisons to a reversal-based attempt and then to a two-pointer implementation that skips non-alphanumeric characters.

## Initial Approach: Compare the Input from Both Ends

My first implementation passes the string by value and initializes `i` to zero and `j` to `s.length()`. While `i <= j`, it checks for a space at either end, adjusts one pointer, and then compares the characters. A mismatch at different positions returns `false`; otherwise, both pointers move inward. Completing the loop returns `true`.

### Why This Implementation Was Wrong

The right pointer starts at `s.length()`, which is one position beyond the last character. Reading `s[s.length()]` in modern C++ yields the string's null character, not its last letter. For a simple palindrome such as `"aba"`, the first comparison is therefore `'a'` against the null character, and the function returns `false`. This counterexample follows from reading the code; it is not a recorded execution.

The space handling also does not consistently reach the next meaningful character before comparing. Each iteration skips at most one space on one side, because the checks use `if` and `else if`. Consecutive spaces or spaces at both ends can remain at the comparison positions. The pointers can also meet or cross during a skip, but the code still performs the comparison and subsequent pointer updates in that iteration.

Finally, the implementation ignores only the literal space character. Punctuation remains part of the comparison, and uppercase letters are compared directly with lowercase letters. This does not implement the problem's alphanumeric filtering and case-insensitive comparison. The first example in `main()` contains both mixed case and a question mark.

- **Intended traversal time complexity:** O(n), since the pointers move inward on each iteration.
- **Space complexity including the parameter copy:** O(n). The pointer variables themselves use O(1) additional storage.

## Second Approach: Build a String Without Spaces

My second attempt creates an empty `new_string` and an `index` counter. A loop visits the input and attempts to write each non-space character into `new_string[index]`, incrementing the index afterward. It then prints `new_string` and compares characters from opposite ends.

### Why This Implementation Was Wrong

The destination string starts empty, and indexed assignment does not grow a C++ string:

```cpp
string new_string;
new_string[index] = s[i];
```

At the first non-space input character, `index` is zero while the string's size is still zero. Writing a non-null character at that position produces undefined behavior. Subsequent indexed writes also do not create string elements or update the length. The code therefore does not construct the intended filtered string, and its printed contents and final result cannot be relied on.

The comparison stage repeats the first attempt's right-boundary issue: `j` is initialized to `new_string.length()` rather than the position of its last character. Even if a nonempty filtered string had been constructed, comparing its first character with its null character would reject an ordinary palindrome.

This attempt also excludes only spaces and does not normalize letter case. Punctuation and differences between uppercase and lowercase letters would still affect the result independently of the string-construction problem.

- **Intended time complexity:** O(n) for filtering followed by O(n) comparison, giving O(n) overall, including printing the intended filtered string.
- **Intended space complexity:** O(n) for a filtered string and the by-value input copy. As written, the destination never grows through indexed assignment, and undefined behavior prevents a meaningful valid-execution resource analysis of the full function.

## Third Approach: Normalize and Reverse the String

Under `// using hint1:`, I added an implementation that converts uppercase characters to lowercase, replaces anything that is not a lowercase letter with a space, builds a reversed string using `push_back`, and compares the two strings character by character. This version is now commented out alongside the first two attempts.

Unlike the second attempt, `push_back` actually adds characters to the initially empty destination string. However, the normalization still does not match the problem's rules.

### Why This Attempt Was Wrong

Replacing ignored characters with spaces preserves their positions rather than removing their effect on the comparison. For example, `"a,b a"` becomes `"a b a"` and happens to compare successfully, but `"a,ba"` becomes `"a ba"` and differs from its reverse even though its alphanumeric sequence `"aba"` is a palindrome. The positions of punctuation can therefore change the result.

The `!islower` condition also replaces digits with spaces, although digits must participate in the palindrome check. For example, `"12"` becomes two spaces and would return `true`, while the original alphanumeric sequence is not a palindrome. These examples are deductions from the code, not recorded executions.

- **Time complexity:** O(n) for normalization, O(n) amortized for constructing the reverse, and O(n) for comparison, giving **O(n)** overall.
- **Space complexity:** **O(n)** for the reversed string and the by-value input copy.

## Current Approach: Skip and Compare with Two Pointers

The active implementation initializes `i` to zero and `j` to `s.length() - 1`. While `i < j`, it checks the current left character with `isalnum`. A non-alphanumeric character advances `i` and triggers `continue`, so the next iteration checks the pointer bounds again before comparing anything. The right side uses the same process with `j--`.

Once both positions hold alphanumeric characters, the function compares `tolower(s[i])` with `tolower(s[j])`. A mismatch returns `false`; a match moves both pointers inward. When the pointers meet or cross, the function returns `true`.

This version starts the right pointer at the last character, skips punctuation and spaces without preserving them in a second string, retains digits as meaningful characters, and compares letters without case differences. The input's characters are not modified, and no filtered or reversed string is constructed.

### Time and Space Complexity

- **Worst-case time complexity:** **O(n)**. Each pointer moves inward, and each character is visited only a constant number of times. The `continue` statements do not restart traversal from the beginning.
- **Working storage beyond the parameter:** **O(1)** for the two indices and character operations.
- **Space including the by-value parameter:** **O(n)**, because `isPalindrome(string s)` copies the input string. This is distinct from the constant working storage of the pointer traversal.

## Example Inputs and Current Source State

`main()` still contains `"Was it a car or a cat I saw?"` and `"tab a cat"`. Under the problem's rules, the first has the alphanumeric lowercase sequence `"wasitacaroracatisaw"` and is a palindrome; the second has `"tabacat"` and is not. Reading the active implementation indicates outputs of `1` and `0`, each on its own line. These are inferred results, not recorded local executions.

The source now includes a problem-description comment specifying case-insensitive comparison and ignoring non-alphanumeric characters, including an explicit definition covering letters and digits. The first three implementations are commented out, and one two-pointer implementation is active.

## Complexity and Measured Performance

The supplied submission screenshot shows the final two-pointer solution **accepted, passing 43 out of 43 test cases**.

| Metric | Two-pointer implementation |
| --- | --- |
| Worst-case time complexity | O(n) |
| Working storage beyond the parameter | O(1) |
| Space including the by-value input copy | O(n) |
| Reported runtime | 3 ms |
| Runtime percentile | Beats 85.72% |
| Reported memory usage | 107.0 MB |
| Memory percentile | Beats 88.30% |

The submission's runtime beat 85.72% of the platform's comparison population, while its memory usage beat 88.30%. The runtime graph places the 3 ms result in the largest displayed runtime bucket.

These are the screenshot's measured results for this submission. Reported memory includes more than the traversal's working storage, and the percentiles describe the platform's comparison population at submission time. No performance screenshots were supplied for the earlier attempts, so there is no measured before-and-after comparison.

### Accepted Two-Pointer Submission

![Accepted Valid Palindrome submission: 43 of 43 tests passed, 3 ms runtime, and 107.0 MB memory.](finally.png)

## Key Observations

- The first two attempts initialize the right pointer to the string length rather than the last character.
- The first attempt's space checks can leave spaces at the comparison positions.
- Indexed assignment into an empty string does not construct the second attempt's intended filtered string.
- The reversal attempt grows its destination with `push_back`, but its replacement rules preserve ignored positions and discard digits.
- The active version skips non-alphanumeric characters and compares lowercase forms using two inward-moving pointers.
- The active traversal takes O(n) time and O(1) working storage; its by-value string parameter adds O(n) space.

- The final submission screenshot records acceptance on all 43 test cases, with 3 ms runtime and 107.0 MB reported memory.
