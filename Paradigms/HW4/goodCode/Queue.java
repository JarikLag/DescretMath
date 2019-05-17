package queue;
//arr[i] - sequence of elements in queue order
//Inv: elements of queue are removed in order they came && arr[i] != null for all i in range 0... size - 1 && size >= 0 
public interface Queue {
	//Pre: obj != null
	//Post: size' = size + 1 && arr[size] = obj
    void enqueue(Object obj);
	//Pre: size > 0
	//Post: R = arr[0]
    Object element();
	//Pre: size > 0
	//Post: size' = size - 1 && R = arr[0]
    Object dequeue();
	//Pre: true
	//Post: R = arr
    Object[] toArray();
	//Pre: true
	//Post: R = size
    int size();
	//Pre: true
	//Post: R = (size == 0)
    boolean isEmpty();
	//Pre: true
	//Post: size' = 0 && arr becomes empty
    void clear();
}
