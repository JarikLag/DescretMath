package queue;

public class ArrayQueueADT {
	// Inv: (n >= 0) && (a[i] != null for i = 1..n - 1)
    private Object[] elements = new Object[4];
    private int size = 0;
    private int head = 0;
    private int tail = 0;
	private int realSize = 0;

	// Pre: (elements.length != 0) && (0 <= x < elements.length)
    private static int nextIndex(ArrayQueueADT q, int i) {
        return (i + 1) % q.elements.length;
    }
	// Result: i' = (i + 1) % elements.length

	// Pre: (elements.length != 0) && (0 <= i < elements.length)
    private static int prevIndex(ArrayQueueADT q, int i) {
        if (i == 0) {
            return q.elements.length - 1;
        } else {
            return i - 1;
        }
    }
	// Post: (Result == i - 1 && i > 0) || (Result == elements.length && i == 0)
	
	// Pre: size >= 0
	public static Object[] toArray(ArrayQueueADT q) {
        Object[] arr = new Object[q.size];
        int ind = 0;
        for (int i = q.head; i != q.tail; i = nextIndex(q, i)) {
            arr[ind] = q.elements[i];
            ind++;
        }
        q.realSize = ind;
        return arr;
    }
	// Result: a'[i] = a[i] for i = 0...size - 1

	// Pre: size >= 0
    private static void ensureCapacity(ArrayQueueADT q) {
        if ((q.elements.length <= q.size) || (q.size * 4 <= q.elements.length)) {
            Object[] temp = new Object[q.size * 2];
            q.elements = toArray(q);
            System.arraycopy(q.elements, 0, temp, 0, q.elements.length);
            q.head = 0;
            q.tail = q.realSize;
            q.elements = temp;
        }
    }
	// Post: (size < elem'.length < size * 4) && (size' == size) && (a'[i] == a[i] for i = 0...size - 1)

	// Pre: true
    public static int size(ArrayQueueADT q) {
        return q.size;
    }
	// Post: (size' == size) && (a'[i] == a[i] for i = 0...size - 1) && (Result == size)

	// Pre: true
    public static boolean isEmpty(ArrayQueueADT q) {
        return q.size == 0;
    }
	// Post: (size' == size) && (a'[i] == a[i] for i = 0...size - 1) && (Result == (size == 0))

	// Pre: true
    public static void clear(ArrayQueueADT q) {
        q.elements = new Object[4];
        q.head = q.tail = q.size = 0;
    }
	// Post: size == 0

	// Pre: size > 0
    public static Object element(ArrayQueueADT q) {
        assert q.size > 0;

        return q.elements[q.head];
    }
	// Post: (size' == size) && (a'[i] == a[i] for i = 0...size - 1) && (Result == a[0])

	// Pre: size > 0
    public static Object dequeue(ArrayQueueADT q) {
        assert q.size > 0;

        Object ans = q.elements[q.head];
        q.head = nextIndex(q, q.head);
        q.size--;
        ensureCapacity(q);
        return ans;
    }
	// Post: (size' == size - 1) && (a'[i - 1] == a[i] for i = 1...size - 1) && (Result == a[0])

	// Pre: (elem != null)
    public static void push(ArrayQueueADT q, Object x) {
        assert x != null;

        q.size++;
        ensureCapacity(q);
        q.head = prevIndex(q, q.head);
        q.elements[q.head] = x;
    }
	// (size' == size + 1) && (a'[i + 1] == a[i] for i = 0..size - 1) && (a'[0] == elem)

	// Pre: size > 0
    public static Object peek(ArrayQueueADT q) {
        assert q.size > 0;

        return q.elements[prevIndex(q, q.tail)];
    }
	// Post: (size' == size) && (a'[i] == a[i] for i = 0...size - 1) && (Result == a[size - 1])

	// Pre: size > 0
    public static Object remove(ArrayQueueADT q) {
        assert q.size > 0;

        q.tail = prevIndex(q, q.tail);
        Object ans = q.elements[q.tail];
        q.size--;
        ensureCapacity(q);
        return ans;
    }
	// Post: (size' == size - 1) && (a'[i] == a[i] for i = 0...size - 2) && (Result == a[size - 1])

	// Pre: (elem != null)
    public static void enqueue(ArrayQueueADT q, Object x) {
        assert x != null;

        q.size++;
        ensureCapacity(q);
        q.elements[q.tail] = x;
        q.tail = nextIndex(q, q.tail);
    }
	// (size' == size + 1) && (a'[i] == a[i] for i = 0..size - 1) && (a'[size] == elem)
}
