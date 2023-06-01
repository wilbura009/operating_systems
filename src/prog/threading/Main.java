import java.util.Arrays;
import java.util.Random;

/**
 * Main class
 * Creates two sorting threads and a merging thread.
 * The sorting threads sort the two subarrays using the selection sort algorithm.
 * The merging thread merges the two sorted subarrays into a single sorted array.
 */
public class Main
{
  /**
   * The default array size if the user does not specify the array size
   */
  private static final int ARRAY_SIZE = 1000;

  /**
   * Returns a random double value
   * @return 
   */
  private static double getRandomDouble() {
    Random random = new Random();
    double r = 1.0 + (1000.0 - 1.0) * random.nextDouble();
    return r;
  }

  /**
   * Sets the array with random double values
   * @param size
   * @return 
   */
  private static double[] setArray(int size)
  {
    double[] arr = new double[size];
    for (int i = 0; i < size; i++)
      arr[i] = getRandomDouble();

    return arr;
  }

  private static double getElaspedTime(long start_time, long end_time)
  {
    // Calculate the elapsed time in milliseconds
    double elapsed_time = (end_time - start_time) / 1000000.0;
    return elapsed_time;
  }

  /**
   * Main method
   * @param args
   * @throws InterruptedException for the join() method
   */
  public static void main(String[] args) throws InterruptedException
  {
    // Check if the array size is specified by the user, otherwise use the default size
    int size = args.length > 0 ? Integer.parseInt(args[0]) : ARRAY_SIZE;
    double[] arr = setArray(size);

    //System.out.println("Unsorted array: " + Arrays.toString(arr));

    // Split the array into two subarrays
    int mid = arr.length / 2;
    double[] left_arr = Arrays.copyOfRange(arr, 0, mid);
    double[] right_arr = Arrays.copyOfRange(arr, mid, arr.length);

    // Create two sorting threads
    Thread t0 = new Thread(new SelectionSortRunnable(left_arr));
    Thread t1 = new Thread(new SelectionSortRunnable(right_arr));

    // ----------- Start the Thread timer -----------
    long start_time = System.nanoTime();

    // Start the sorting threads
    t0.start();
    t1.start();

    // Wait for the sorting threads to finish
    t0.join();
    t1.join();

    // Create a merging thread
    Thread t3 = new Thread(new MergeRunnable(left_arr, right_arr, arr));

    // Start the merging thread
    t3.start();

    // Wait for the merging thread to finish
    t3.join();

    // Stop the timer
    long end_time = System.nanoTime();

    // Print the elapsed time for sorting with two threads and merging
    System.out.println(
        "Sorting is done in "
        + getElaspedTime(start_time, end_time)
        + "ms when two thread are used."
    );

    // ---- Prepare an array for the non-threaded sorting algorithm ----
    double[] arr2 = setArray(size);
    //System.out.println("Unsorted array: " + Arrays.toString(arr2));

    // Split the array into two subarrays
    double[] left_arr2 = Arrays.copyOfRange(arr2, 0, mid);
    double[] right_arr2 = Arrays.copyOfRange(arr2, mid, arr2.length);

    SelectionSortRunnable s0 = new SelectionSortRunnable(left_arr2);
    SelectionSortRunnable s1 = new SelectionSortRunnable(right_arr2);
    MergeRunnable m = new MergeRunnable(left_arr2, right_arr2, arr2);

    // ----------- Start the single thread timer ----------- 
    start_time = System.nanoTime();
    s0.run();
    s1.run();
    m.run();
    end_time = System.nanoTime();
    System.out.println(
        "Sorting is done in "
        + getElaspedTime(start_time, end_time)
        + "ms when one thread is used."
    );

    //System.out.println("Sorted array: " + Arrays.toString(arr));
  }
}
