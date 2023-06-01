/**
 * SelectionSortRunnable class
 * Implements Runnable interface and overrides the run() method.
 */
class SelectionSortRunnable implements Runnable
{
  /**
   * The array to be sorted
   */
  private double[] arr;

  /**
   * Constructor
   * @param arr
   */
  public SelectionSortRunnable(double[] arr)
  {
    this.arr = arr;
  }

  /**
   * Overrides the run() method of the Runnable interface
   * Sorts the array using the selection sort algorithm
   */
  @Override // good practice
  public void run() {
    for (int i = 0; i < arr.length - 1; i++)
    {
      int min = i;
      for (int j = i + 1; j < arr.length; j++)
      {
        if (arr[j] < arr[min])
          min = j;
      }
      if (min != i)
      {
        double temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
      }
    }
    //System.out.println("Sorted subarray: " + Arrays.toString(arr));
  }
}
