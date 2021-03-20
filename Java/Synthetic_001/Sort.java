import java.util.Collections;
import java.util.ArrayList;

public class Sort<A extends ArrayList<Integer>>{

  private A array;

  Sort(A array){

    this.array = array;

  }

  // Basic Sorting //

  public void shakerSorting(){

    for(int left = 0, right = array.size() - 1; left <= right; ++left, --right){

      for(int i = right; i > left; --i)

        if(array.get(i - 1) > array.get(i))

          swap(i - 1, i);

      for(int i = left; i < right; ++i)

        if(array.get(i + 1) < array.get(i))

          swap(i + 1, i);

    }

  }

  public void insertionSorting(){

    for(int right = 1; right < array.size(); ++right)

      for(int left = right; left > 0 && array.get(left - 1) > array.get(left); --left)

        swap(left - 1, left);

  }

  public void bubbleSorting(){

    for(int current = 0; current + 1 < array.size(); ++current)

      if(array.get(current + 1) < array.get(current)){

        swap(current + 1, current);
        current = -1;

      }

  }

  // Quick Sorting //

  public void quickSorting(){

    quickSortingLoop(0, array.size() - 1);

  }

  private void quickSortingLoop(int left, int right){

    if(left < right){

      int pivot = quickSortingPart(left, right);

      quickSortingLoop(left, pivot - 1);
      quickSortingLoop(pivot + 1, right);

    }

  }

  private int quickSortingPart(int left, int right){

    int pivot    = array.get(right),
        previous = left - 1,
        current  = left;

    while(current <= right - 1){

      if(array.get(current) < pivot){

        ++previous;
        swap(previous, current);

      }

      ++current;

    }

    ++previous;

    swap(previous, right);
    return previous;

  }

  // Tools //

  private void swap(int left, int right){

    Collections.swap(array, left, right);

  }

}