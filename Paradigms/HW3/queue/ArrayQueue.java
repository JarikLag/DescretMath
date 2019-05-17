package queue;

//Invariant: size != null && array != null && head != null
//			0 <= size <= array.length && 0 <= head < array.length
public class ArrayQueue {
    private int size, head;
    private Object[] array = new Object[4];

    private Object[] getQueue(int sz) {
        Object[] tmp = new Object[sz];
        if (head + size <= array.length) {
            System.arraycopy(array, head, tmp, 0, size);
        } else {
            System.arraycopy(array, head, tmp, 0, array.length - head);
            System.arraycopy(array, 0, tmp, array.length - head, size - array.length + head);
        }
        return tmp;
    }.

    private void ensureCapacity() {
        if (array.length == size) {
            array = getQueue(size * 2);
            head = 0;
        }
    }

    // Pre: invariant
    public Object[] toArray() {
        return getQueue(size);
    }
    // Result: a'[i] = a[i] for i = 0...size - 1

    //Pre: obj != null && invariant
    public void enqueue(Object obj) {
        assert obj != null;

        ensureCapacity();
        array[(head + size) % array.length] = obj;
        size++;
    }
    //Post: invariant && size == size' + 1 && array == array', without array[(head' + size') % array'.length] == obj && head' == head

    //Pre: size > 0 && invariant
    public Object element() {
        assert size > 0;

        return array[head];
    }
    //Post size' == size && array' == array && head' == head && Result == array[head] && invariant

    //Pre: invariant
    public int size() {
        return size;
    }
    //Post: size == size' && array == array' && head == head' && Result == size && invariant

    //Pre:size > 0 && invariant
    public Object dequeue() {
        assert size > 0;

        Object obj = array[head];
        head = (head + 1) % array.length;
        size--;
        return obj;
    }
    //Post: size == size' - 1 && head == (head' + 1) % array'.length && R == array[head'] && array = array' && invariant

    //Pre: invariant
    public boolean isEmpty() {
        return (size == 0);
    }
    //Post: size == size' && array == array' && head == head' && Result == (size == 0) && invariant

    //Pre: invariant
    public void clear() {
        array = new Object[4];
        size = 0;
        head = 0;
    }
    //Post: size == 0 && head == 0 && array' is empty sequence && invariant
}