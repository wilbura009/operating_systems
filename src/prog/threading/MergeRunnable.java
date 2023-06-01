/**
 * MergeRunnable class
 * Implements Runnable interface and overrides the run() method.
 * Merges two sorted subarrays into a single sorted array.
 */
class MergeRunnable implements Runnable
{
  /**
   * The two sorted subarrays
   */
  private double[] left_arr;
  private double[] right_arr;

  /**
   * The array to store the merged result
   */
  private double[] res_arr;

  /**
   * Constructor
   * @param left_arr
   * @param right_arr
   * @param res_arr
   */
  public MergeRunnable(double[] left_arr,
                       double[] right_arr,
                       double[] res_arr)
  {
    this.left_arr = left_arr;
    this.right_arr = right_arr;
    this.res_arr = res_arr;
  }

  /**
   * Overrides the run() method of the Runnable interface
   * Merges the two sorted subarrays into a single sorted array.
   */
  @Override
  public void run()
  {
    int left_index = 0;  // the index of the left array
    int right_index = 0; // the index of the right array
    int result_index = 0; // the index of the result array
     

    while (left_index < left_arr.length && right_index < right_arr.length)
    {
      // Copy the smaller element into the result array
      if (left_arr[left_index] < right_arr[right_index])
        res_arr[result_index++] = left_arr[left_index++];
      else 
        res_arr[result_index++] = right_arr[right_index++];
    }

    // Copy the remaining elements from the left array into the result array
    while (left_index < left_arr.length)
      res_arr[result_index++] = left_arr[left_index++];

    // Copy the remaining elements from the right array into the result array
    while (right_index < right_arr.length)
      res_arr[result_index++] = right_arr[right_index++];
  }
}
