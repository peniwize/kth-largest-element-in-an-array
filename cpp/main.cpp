/*!
    \file "main.cpp"

    Author: Matt Ervin <matt@impsoftware.org>
    Formatting: 4 spaces/tab (spaces only; no tabs), 120 columns.
    Doc-tool: Doxygen (http://www.doxygen.com/)

    https://leetcode.com/problems/kth-largest-element-in-an-array/
*/

//!\sa https://github.com/doctest/doctest/blob/master/doc/markdown/main.md
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <algorithm>
#include <cassert>
#include <chrono>
#include <doctest/doctest.h> //!\sa https://github.com/doctest/doctest/blob/master/doc/markdown/tutorial.md
#include <iterator>
#include <vector>
#include <set>
#include <span>

using namespace std;

// [----------------(120 columns)---------------> Module Code Delimiter <---------------(120 columns)----------------]

class Solution {
public:
    /*!
        Time = O(n*log2(n))
        Space = O(1)
    */
    int findKthLargest_sort(vector<int>& nums, int k) {
        std::sort(nums.begin(), nums.end());
        return nums.size() >= k ? nums[nums.size() - k] : 0;
    }

    /*!
        Time = O(k*log2(k) + (n-k)*log2(k)) => O(n*log2(k))
        Space = O(k)
    */
    int findKthLargest_multiset(vector<int>& nums, int k) {
        std::multiset<int> largest{};
        auto first_k_end = nums.begin();
        std::advance(first_k_end, k);
        std::copy(nums.begin(), first_k_end, std::inserter(largest, largest.end()));

        for (auto const num : std::span{first_k_end, nums.end()}) {
            largest.insert(num);
            while (largest.size() > k) { largest.erase(largest.begin()); }
        }

        return largest.size() == k ? *largest.begin() : 0;
    }

    /*!
        Time = O(2n) => O(n)
        Space = O(20002) => O(1)
    */
    int findKthLargest_freqCount(vector<int>& nums, int k) {
        constexpr auto const half_range = 10000 + 1;
        constexpr auto const range = half_range * 2;
        int_least32_t freq[range] = { 0 };
        int min = (std::numeric_limits<int>::max)();
        int max = (std::numeric_limits<int>::min)();
        for (auto const num : nums) {
            assert(half_range > num && 0 - half_range < num);
            ++freq[half_range + num]; // Track frequency of num.
            min = (std::min)(min, num); // Track minimum value in all nums.
            max = (std::max)(max, num); // Track maximum value in all nums.
        }

        // Scan the range of all nums processed, from max to min.
        int kcnt = k;
        for (int idx = max; min <= idx; --idx) {
            kcnt -= freq[half_range + idx]; // Count how many nums were recorded.
            auto const found_kth_num = 0 >= kcnt;
            if (found_kth_num) {
                return idx;
            }
        }

        return 0;
    }

    int findKthLargest_heap(vector<int>& nums, int k) {
        // Create a heap containing the first k nums.
        int heap[k];
        std::copy(nums.begin(), nums.begin() + k, heap);
        make_heap(heap, heap + k);

        // For each remaining num in nums:
        for (auto const num : std::span{nums.begin() + k, nums.end()}) {
//
//!\todo TODO: The following is bs.  The smallest [leaf] node in the heap 
//             must be replaced with the new value, but only when the new
//             value is <= heap max value AND the new value >= all heap 
//             leaf node values.
//             When the new value is greater than the max value in the heap,
//             replace the smallest heap value with the new value and then 
//             heapify it up.
//             This is all necessary to use the heap like a shift register.
//
//             auto const num_is_larger_than_heap_content = num > heap[0];
//             if (num_is_larger_than_heap_content) {
// // Remove largest number 
// //
// //!\todo TODO: >>> Under Construction <<<
// //
//                 pop_heap(heap, heap + k);
//                 heap[k - 1] = num;
//                 push_heap(heap, heap + k);
//             }
        }

//
//!\todo TODO: >>> Under Construction <<<
//
return 0;
    }

    int findKthLargest(vector<int>& nums, int k) {
        //return findKthLargest_sort(nums, k);
        //return findKthLargest_multiset(nums, k);
        return findKthLargest_freqCount(nums, k);
    }
};

// [----------------(120 columns)---------------> Module Code Delimiter <---------------(120 columns)----------------]

struct elapsed_time_t
{
    std::chrono::steady_clock::time_point start{};
    std::chrono::steady_clock::time_point end{};
    
    elapsed_time_t(
        std::chrono::steady_clock::time_point start
        , std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now()
    ) : start{std::move(start)}, end{std::move(end)} {}
};

std::ostream&
operator<<(std::ostream& os, elapsed_time_t const& et)
{
    auto const elapsed_time = et.end - et.start;
    os << std::chrono::duration_cast<std::chrono::microseconds>(elapsed_time).count()
       << '.' << (std::chrono::duration_cast<std::chrono::microseconds>(elapsed_time).count() % 1000)
       << " ms";
    return os;
}

TEST_CASE("Case 1")
{
    cerr << "Case 1" << '\n';
    vector<int> value{3,2,1,5,6,4}; // 1,2,3,4,[5],6
    auto const expected = 5;
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        CHECK(expected == Solution{}.findKthLargest(value, 2));
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << '\n';
}

TEST_CASE("Case 2")
{
    cerr << "Case 1" << '\n';
    vector<int> value{3,2,3,1,2,4,5,5,6}; // 1,2,2,3,3,[4],5,5,6
    auto const expected = 4;
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        CHECK(expected == Solution{}.findKthLargest(value, 4));
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << '\n';
}

/*
    End of "main.cpp"
*/
