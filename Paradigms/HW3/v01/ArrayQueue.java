package queue;

public class ArrayQueue {
	// Inv: (n >= 0) && (a[i] != null for i = 1..n - 1)
    private Object[] elements = new Object[4];
    private int size = 0;
    private int head = 0;
    private int tail = 0;
	private int realSize = 0;

	// Pre: (elements.length != 0) && (0 <= i < elements.length)
    private int nextIndex(int i) {
        return (i + 1) % elements.length;
    }
	// Result: i' = (i + 1) % elements.length

	// Pre: (elements.length != 0) && (0 <= i < elements.length)
    private int prevIndex(int i) {
        if (i == 0) {
            return elements.length - 1;
        } else {
            return i - 1;
        }
    }
	// Post: (Result == i - 1 && i > 0) || (Result == elements.length && i == 0)

	// Pre: size >= 0
    public Object[] toArray() {
        Object[] arr = new Object[size];
        int ind = 0;
        for (int i = head; i != tail; i = nextIndex(i)) {
            arr[ind] = elements[i];
            ind++;
        }
        realSize = ind;
        return arr;
    }
	// Result: a'[i] = a[i] for i = 0...size - 1

	// Pre: size >= 0
    private void ensureCapacity() {
        if ((elements.length <= size) || (size * 4 <= elements.length)) {
            Object[] temp = new Object[size * 2];
            elements = toArray();
            System.arraycopy(elements, 0, temp, 0, elements.length);
            head = 0;
            tail = realSize;
            elements = temp;
        }
    }
	// Post: (size < elem'.length < size * 4) && (size' == size) && (a'[i] == a[i] for i = 0...size - 1)

	// Pre: true
    public int size() {
        return size;
    }
	// Post: (size' == size) && (a'[i] == a[i] for i = 0...size - 1) && (Result == size)

	// Pre: true
    public boolean isEmpty() {
        return size == 0;
    }
	// Post: (size' == size) && (a'[i] == a[i] for i = 0...size - 1) && (Result == (size == 0))

	// Pre: true
    public void clear() {
        elements = new Object[4];
        head = tail = size = 0;
    }
	// Post: size == 0

	// Pre: size > 0
    public Object element() {
        assert size > 0;

        return elements[head];
    }
	// Post: (size' == size) && (a'[i] == a[i] for i = 0...size - 1) && (Result == a[0])
	
	// Pre: size > 0
    public Object dequeue() {
        assert size > 0;

        Object ans = elements[head];
        head = nextIndex(head);
        size--;
        ensureCapacity();
        return ans;
    }
	// Post: (size' == size - 1) && (a'[i - 1] == a[i] for i = 1...size - 1) && (Result == a[0])

	// Pre: (elem != null)
    public void push(Object x) {
        assert x != null;

        size++;
        ensureCapacity();
        head = prevIndex(head);
        elements[head] = x;
    }
	// (size' == size + 1) && (a'[i + 1] == a[i] for i = 0..size - 1) && (a'[0] == elem)

	// Pre: size > 0
    public Object peek() {
        assert size > 0;

        return elements[prevIndex(tail)];
    }
	// Post: (size' == size) && (a'[i] == a[i] for i = 0...size - 1) && (Result == a[size - 1])

	// Pre: size > 0
    public Object remove() {
        assert size > 0;

        tail = prevIndex(tail);
        Object ans = elements[tail];
        size--;
        ensureCapacity();
        return ans;
    }
	// Post: (size' == size - 1) && (a'[i] == a[i] for i = 0...size - 2) && (Result == a[size - 1])

	// Pre: (elem != null)
    public void enqueue(Object x) {
        assert x != null;

        size++;
        ensureCapacity();
        elements[tail] = x;
        tail = nextIndex(tail);
    }
	// (size' == size + 1) && (a'[i] == a[i] for i = 0..size - 1) && (a'[size] == elem)
}



//Pre: obj != null && invariant
	public void push(Object obj) {
		assert obj != null;
		ensureCapacity();
		array[(head - 1 + array.length) % array.length] = obj;
		size++;
		head = (head - 1 + array.length) % array.length;
	}
	//Post: invariant && size == size' + 1 && (
	//(size' < array'.length && array == array', without array[l] == obj && l = (l' - 1 + array'.length) % array'.length) || 
	//(size' == array'.length && for i=0...size' - 1: array[i] = array'[(l' + i) % array'.length] && array[l] = obj && l == array.length - 1 && array.length = 2 * array'.length)) 

	//Pre: size > 0 && invariant
	public Object peek() {
		assert size > 0;
		return array[(l + size - 1) % array.length];
	}
	//Post: array = array' && size == size' && l == l' && R == array[(l + size) % array.length] && invariant 

	//Pre: invariant && size > 0
	public Object remove() {
		assert size > 0;
		Object obj = peek();
		size--;
		return obj;
	}
	//Post: size = size' - 1 && R == array[(l + size' - 1) % array.length] && invariant
