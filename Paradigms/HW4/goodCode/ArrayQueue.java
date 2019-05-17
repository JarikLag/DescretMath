package queue;

public class ArrayQueue extends AbstractQueue {
    private int head;
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
    }

    private void ensureCapacity() {
        if (array.length == size) {
            array = getQueue(size * 2);
            head = 0;
        }
    }

    public Object[] toArrayImpl() {
        return getQueue(size);
    }

    public void enqueueImpl(Object obj) {
        ensureCapacity();
        array[(head + size) % array.length] = obj;
    }

    public Object elementImpl() {
        return array[head];
    }

    public void remove() {
        head = (head + 1) % array.length;
    }

    public void clearImpl() {
        array = new Object[4];
        head = 0;
    }
}