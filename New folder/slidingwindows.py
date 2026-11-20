"""Find the maximum sum of a contiguous subarray of a fixed size."""


def max_sum_subarray(numbers, k):
	"""Return the largest sum among all contiguous windows of length k."""
	if k <= 0 or k > len(numbers):
		raise ValueError("k must be between 1 and len(numbers)")

	window_sum = sum(numbers[:k])
	best_sum = window_sum

	for right in range(k, len(numbers)):
		window_sum += numbers[right] - numbers[right - k]
		best_sum = max(best_sum, window_sum)

	return best_sum


if __name__ == "__main__":
	values = [2, 1, 5, 1, 3, 2]
	print(max_sum_subarray(values, 3))  # 9
