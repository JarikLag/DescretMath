package queue;

//Invariant: size != null && array != null && head != null
//			0 <= size <= array.length && 0 <= head < array.length
public class ArrayQueueADT {
    private int size, head;
    private Object[] array = new Object[4];

    private static Object[] getQueue(ArrayQueueADT q, int sz) {
        Object[] tmp = new Object[sz];
        if (q.head + q.size <= q.array.length) {
            System.arraycopy(q.array, q.head, tmp, 0, q.size);
        } else {
            System.arraycopy(q.array, q.head, tmp, 0, q.array.length - q.head);
            System.arraycopy(q.array, 0, tmp, q.array.length - q.head, q.size - q.array.length + q.head);
        }
        return tmp;
    }

    private static void ensureCapacity(ArrayQueueADT q) {
        if (q.array.length == q.size) {
            q.array = getQueue(q, q.size * 2);
            q.head = 0;
        }
    }

    // Pre: invariant
    public static Object[] toArray(ArrayQueueADT q) {
        return getQueue(q, q.size);
    }
    // Result: a'[i] = a[i] for i = 0...size - 1

    //Pre: obj != null && invariant
    public static void enqueue(ArrayQueueADT q, Object obj) {
        assert obj != null;

        ensureCapacity(q);
        q.array[(q.head + q.size) % q.array.length] = obj;
        q.size++;
    }
    //Post: invariant && size == size' + 1 && array == array', without array[(head' + size') % array'.length] == obj && head' == head

    //Pre: size > 0 && invariant
    public static Object element(ArrayQueueADT q) {
        assert q.size > 0;

        return q.array[q.head];
    }
    //Post size' == size && array' == array && head' == head && Result == array[head] && invariant

    //Pre: invariant
    public static int size(ArrayQueueADT q) {
        return q.size;
    }
    //Post: size == size' && array == array' && head == head' && Result == size && invariant

    //Pre:size > 0 && invariant
    public static Object dequeue(ArrayQueueADT q) {
        assert q.size > 0;

        Object obj = q.array[q.head];
        q.head = (q.head + 1) % q.array.length;
        q.size--;
        return obj;
    }
    //Post: size == size' - 1 && head == (head' + 1) % array'.length && R == array[head'] && array = array' && invariant

    //Pre: invariant
    public static boolean isEmpty(ArrayQueueADT q) {
        return (q.size == 0);
    }
    //Post: size == size' && array == array' && head == head' && Result == (size == 0) && invariant

    //Pre: invariant
    public static void clear(ArrayQueueADT q) {
        q.array = new Object[4];
        q.size = 0;
        q.head = 0;
    }
    //Post: size == 0 && head == 0 && array' is empty sequence && invariant
}